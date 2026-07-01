#include "plproxy.h"
static MemoryContext cluster_mem;
static struct AATree cluster_tree;
static struct AATree fake_cluster_tree;
static void *version_plan;
static void *partlist_plan;
static void *config_plan;
static const char version_sql[] =
    "select * from plproxy.get_cluster_version($1)";
static const char part_sql[] =
    "select * from plproxy.get_cluster_partitions($1)";
static const char config_sql[] = "select * from plproxy.get_cluster_config($1)";
static const char *cluster_config_options[] = {
    "statement_timeout",  "connection_lifetime", "query_timeout",
    "disable_binary",     "modular_mapping",     "keepalive_idle",
    "keepalive_interval", "keepalive_count",     ((void *)0)};
extern Datum plproxy_fdw_validator(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) Datum
plproxy_fdw_validator(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_plproxy_fdw_validator(void);
const Pg_finfo_record *pg_finfo_plproxy_fdw_validator(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
static _Bool check_valid_partcount(int n, int modular_mapping) {
  if (modular_mapping)
    return n > 0;
  return (n > 0) && !(n & (n - 1));
}
static int cluster_name_cmp(uintptr_t val, struct AANode *node) {
  const char *name = (const char *)val;
  const ProxyCluster *cluster = ((
      ProxyCluster *)((char *)(node) - __builtin_offsetof(ProxyCluster, node)));
  return strcmp(name, cluster->name);
}
static int conn_cstr_cmp(uintptr_t val, struct AANode *node) {
  const char *name = (const char *)val;
  const ProxyConnection *conn =
      ((ProxyConnection *)((char *)(node) -
                           __builtin_offsetof(ProxyConnection, node)));
  return strcmp(name, conn->connstr);
}
static void conn_free(struct AANode *node, void *arg) {
  ProxyConnection *conn =
      ((ProxyConnection *)((char *)(node) -
                           __builtin_offsetof(ProxyConnection, node)));
  aatree_destroy(&conn->userstate_tree);
  if (conn->res)
    PQclear(conn->res);
  pfree(conn);
}
static int state_user_cmp(uintptr_t val, struct AANode *node) {
  const char *name = (const char *)val;
  const ProxyConnectionState *state = ((
      ProxyConnectionState *)((char *)(node) -
                              __builtin_offsetof(ProxyConnectionState, node)));
  return strcmp(name, state->userinfo->username);
}
static void state_free(struct AANode *node, void *arg) {
  ProxyConnectionState *state = ((
      ProxyConnectionState *)((char *)(node) -
                              __builtin_offsetof(ProxyConnectionState, node)));
  plproxy_disconnect(state);
  memset(state, 0, sizeof(*state));
  pfree(state);
}
static int userinfo_cmp(uintptr_t val, struct AANode *node) {
  const char *name = (const char *)val;
  const ConnUserInfo *info = ((
      ConnUserInfo *)((char *)(node) - __builtin_offsetof(ConnUserInfo, node)));
  return strcmp(name, info->username);
}
static void userinfo_free(struct AANode *node, void *arg) {
  ConnUserInfo *info = ((
      ConnUserInfo *)((char *)(node) - __builtin_offsetof(ConnUserInfo, node)));
  pfree(info->username);
  if (info->extra_connstr) {
    memset(info->extra_connstr, 0, strlen(info->extra_connstr));
    pfree(info->extra_connstr);
  }
  memset(info, 0, sizeof(*info));
  pfree(info);
}
void plproxy_cluster_cache_init(void) {
  cluster_mem =
      (((void)({
         do {
           _Static_assert(__builtin_constant_p("PL/Proxy cluster context"),
                          "memory context names must be constant strings");
         } while (0);
         1;
       })),
       AllocSetContextCreateInternal(TopMemoryContext,
                                     "PL/Proxy cluster context", 0, (1 * 1024),
                                     (8 * 1024)));
  aatree_init(&cluster_tree, cluster_name_cmp, ((void *)0));
  aatree_init(&fake_cluster_tree, cluster_name_cmp, ((void *)0));
}
static void plproxy_cluster_plan_init(void) {
  void *tmp_ver_plan, *tmp_part_plan, *tmp_conf_plan;
  Oid types[] = {25};
  static int init_done = 0;
  if (init_done)
    return;
  tmp_ver_plan = SPI_prepare(version_sql, 1, types);
  if (tmp_ver_plan == ((void *)0))
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("PL/Proxy: plproxy.get_cluster_version() SQL fails: %s",
                        SPI_result_code_string(SPI_result)),
            errfinish("src/cluster.c", 194, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
  tmp_part_plan = SPI_prepare(part_sql, 1, types);
  if (tmp_part_plan == ((void *)0))
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal(
            "PL/Proxy: plproxy.get_cluster_partitions() SQL fails: %s",
            SPI_result_code_string(SPI_result)),
            errfinish("src/cluster.c", 199, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
  tmp_conf_plan = SPI_prepare(config_sql, 1, types);
  if (tmp_conf_plan == ((void *)0))
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("PL/Proxy: plproxy.get_cluster_config() SQL fails: %s",
                        SPI_result_code_string(SPI_result)),
            errfinish("src/cluster.c", 204, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
  version_plan = SPI_saveplan(tmp_ver_plan);
  partlist_plan = SPI_saveplan(tmp_part_plan);
  config_plan = SPI_saveplan(tmp_conf_plan);
  init_done = 1;
}
static void free_connlist(ProxyCluster *cluster) {
  aatree_destroy(&cluster->conn_tree);
  pfree(cluster->part_map);
  pfree(cluster->active_list);
  cluster->part_map = ((void *)0);
  cluster->part_count = 0;
  cluster->part_mask = 0;
  cluster->active_count = 0;
}
static void add_connection(ProxyCluster *cluster, const char *connstr,
                           int part_num) {
  struct AANode *node;
  ProxyConnection *conn = ((void *)0);
  node = aatree_search(&cluster->conn_tree, (uintptr_t)connstr);
  if (node)
    conn = ((ProxyConnection *)((char *)(node) -
                                __builtin_offsetof(ProxyConnection, node)));
  if (!conn) {
    conn = MemoryContextAllocZero(cluster_mem, sizeof(ProxyConnection));
    conn->connstr = MemoryContextStrdup(cluster_mem, connstr);
    conn->cluster = cluster;
    aatree_init(&conn->userstate_tree, state_user_cmp, state_free);
    aatree_insert(&cluster->conn_tree, (uintptr_t)connstr, &conn->node);
  }
  if (cluster->part_map[part_num])
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        (errcode((((('4') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                  (((('6') - '0') & 0x3F) << 12) +
                  (((('0') - '0') & 0x3F) << 18) +
                  (((('1') - '0') & 0x3F) << 24))),
         errmsg("Pl/Proxy: duplicate partition in config: %d", part_num),
         errhint("already got number %d", part_num)),
            errfinish("src/cluster.c", 263, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
  cluster->part_map[part_num] = conn;
}
static int get_version(ProxyFunction *func, Datum dname) {
  Datum bin_val;
  _Bool isnull;
  char nulls[1];
  int err;
  nulls[0] = (dname == (Datum)((void *)0)) ? 'n' : ' ';
  err = SPI_execute_plan(version_plan, &dname, nulls, 0, 0);
  if (err != 5)
    plproxy_error_with_state(
        (func),
        (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
         (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
         (((('0') - '0') & 0x3F) << 24)),
        "get_version: spi error: %s", SPI_result_code_string(err));
  if (SPI_processed != 1)
    plproxy_error_with_state(
        (func),
        (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
         (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
         (((('0') - '0') & 0x3F) << 24)),
        "get_version: got %d rows", (int)SPI_processed);
  bin_val =
      SPI_getbinval(SPI_tuptable->vals[0], SPI_tuptable->tupdesc, 1, &isnull);
  if (isnull)
    plproxy_error_with_state(
        (func),
        (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
         (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
         (((('0') - '0') & 0x3F) << 24)),
        "get_version: got NULL?");
  return DatumGetInt32(bin_val);
}
static void clear_config(ProxyConfig *cf) { memset(cf, 0, sizeof(*cf)); }
static void set_config_key(ProxyFunction *func, ProxyConfig *cf,
                           const char *key, const char *val) {
  static int did_warn = 0;
  if (pg_strcasecmp(key, "statement_timeout") == 0)
    ;
  else if (pg_strcasecmp("connection_lifetime", key) == 0)
    cf->connection_lifetime = atoi(val);
  else if (pg_strcasecmp("query_timeout", key) == 0)
    cf->query_timeout = atoi(val);
  else if (pg_strcasecmp("disable_binary", key) == 0)
    cf->disable_binary = atoi(val);
  else if (pg_strcasecmp("modular_mapping", key) == 0)
    cf->modular_mapping = atoi(val);
  else if (pg_strcasecmp("keepalive_idle", key) == 0 ||
           pg_strcasecmp("keepalive_interval", key) == 0 ||
           pg_strcasecmp("keepalive_count", key) == 0) {
    if (atoi(val) > 0 && !did_warn) {
      did_warn = 1;
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(19) && (19) >= 21
                ? errstart_cold(19, ((void *)0))
                : errstart(19, ((void *)0)))
          errmsg_internal("Use libpq keepalive options, PL/Proxy keepalive "
                          "options not supported"),
              errfinish("src/cluster.c", 326, __func__);
        if (__builtin_constant_p(19) && (19) >= 21)
          abort();
      } while (0);
    }
  } else if (pg_strcasecmp("default_user", key) == 0)
    pg_snprintf(cf->default_user, sizeof(cf->default_user), "%s", val);
  else
    plproxy_error_with_state(
        (func),
        (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
         (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
         (((('0') - '0') & 0x3F) << 24)),
        "Unknown config param: %s", key);
}
static int get_config(ProxyCluster *cluster, Datum dname, ProxyFunction *func) {
  int err, i;
  TupleDesc desc;
  const char *key, *val;
  err = SPI_execute_plan(config_plan, &dname, ((void *)0), 0, 0);
  if (err != 5)
    plproxy_error_with_state(
        (func),
        (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
         (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
         (((('0') - '0') & 0x3F) << 24)),
        "fetch_config: spi error");
  desc = SPI_tuptable->tupdesc;
  if (desc->natts != 2)
    plproxy_error_with_state(
        (func),
        (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
         (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
         (((('0') - '0') & 0x3F) << 24)),
        "Cluster config must have 2 columns");
  if (SPI_gettypeid(desc, 1) != 25)
    plproxy_error_with_state(
        (func),
        (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
         (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
         (((('0') - '0') & 0x3F) << 24)),
        "Config column 1 must be text");
  if (SPI_gettypeid(desc, 2) != 25)
    plproxy_error_with_state(
        (func),
        (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
         (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
         (((('0') - '0') & 0x3F) << 24)),
        "Config column 2 must be text");
  clear_config(&cluster->config);
  for (i = 0; i < SPI_processed; i++) {
    HeapTuple row = SPI_tuptable->vals[i];
    key = SPI_getvalue(row, desc, 1);
    if (key == ((void *)0))
      plproxy_error_with_state(
          (func),
          (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
           (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
           (((('0') - '0') & 0x3F) << 24)),
          "key must not be NULL");
    val = SPI_getvalue(row, desc, 2);
    if (val == ((void *)0))
      plproxy_error_with_state(
          (func),
          (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
           (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
           (((('0') - '0') & 0x3F) << 24)),
          "val must not be NULL");
    set_config_key(func, &cluster->config, key, val);
  }
  return 0;
}
static void allocate_cluster_partitions(ProxyCluster *cluster, int nparts) {
  MemoryContext old_ctx;
  if (cluster->part_map)
    free_connlist(cluster);
  cluster->part_count = nparts;
  cluster->part_mask = cluster->part_count - 1;
  old_ctx = MemoryContextSwitchTo(cluster_mem);
  cluster->part_map = palloc0(nparts * sizeof(ProxyConnection *));
  cluster->active_list = palloc0(nparts * sizeof(ProxyConnection *));
  MemoryContextSwitchTo(old_ctx);
}
static int reload_parts(ProxyCluster *cluster, Datum dname,
                        ProxyFunction *func) {
  int err, i;
  char *connstr;
  TupleDesc desc;
  HeapTuple row;
  err = SPI_execute_plan(partlist_plan, &dname, ((void *)0), 0, 0);
  if (err != 5)
    plproxy_error_with_state(
        (func),
        (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
         (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
         (((('0') - '0') & 0x3F) << 24)),
        "get_partlist: spi error");
  if (!check_valid_partcount(SPI_processed, cluster->config.modular_mapping))
    plproxy_error_with_state(
        (func),
        (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
         (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
         (((('0') - '0') & 0x3F) << 24)),
        "get_partlist: invalid part count");
  desc = SPI_tuptable->tupdesc;
  if (desc->natts < 1)
    plproxy_error_with_state(
        (func),
        (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
         (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
         (((('0') - '0') & 0x3F) << 24)),
        "Partition config must have at least 1 columns");
  if (SPI_gettypeid(desc, 1) != 25)
    plproxy_error_with_state(
        (func),
        (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
         (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
         (((('0') - '0') & 0x3F) << 24)),
        "partition column 1 must be text");
  allocate_cluster_partitions(cluster, SPI_processed);
  for (i = 0; i < SPI_processed; i++) {
    row = SPI_tuptable->vals[i];
    connstr = SPI_getvalue(row, desc, 1);
    if (connstr == ((void *)0))
      plproxy_error_with_state(
          (func),
          (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
           (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
           (((('0') - '0') & 0x3F) << 24)),
          "connstr must not be NULL");
    add_connection(cluster, connstr, i);
  }
  return 0;
}
static _Bool extract_part_num(const char *partname, int *part_num) {
  char *partition_tags[] = {"p", "partition_", ((void *)0)};
  char **part_tag;
  char *errptr;
  for (part_tag = partition_tags; *part_tag; part_tag++) {
    if (strstr(partname, *part_tag) == partname) {
      *part_num = (int)strtoul(partname + strlen(*part_tag), &errptr, 10);
      if (*errptr == '\0')
        return 1;
    }
  }
  return 0;
}
static void validate_cluster_option(const char *name, const char *arg) {
  const char **opt;
  for (opt = cluster_config_options; *opt; opt++) {
    if (pg_strcasecmp(*opt, name) == 0)
      break;
  }
  if (*opt == ((void *)0))
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("Pl/Proxy: invalid server option: %s", name),
            errfinish("src/cluster.c", 480, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
  else if (strspn(arg, "0123456789") != strlen(arg))
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("Pl/Proxy: only integer options are allowed: %s=%s",
                        name, arg),
            errfinish("src/cluster.c", 483, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
}
Datum plproxy_fdw_validator(FunctionCallInfo fcinfo) {
  List *options_list = untransformRelOptions((fcinfo->args[0].value));
  Oid catalog = DatumGetObjectId((fcinfo->args[1].value));
  ListCell *cell;
  int part_count = 0, part_num;
  unsigned char *part_set = ((void *)0);
  int modular_mapping = 0;
  if (catalog == ((Oid)0)) {
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(18) && (18) >= 21
              ? errstart_cold(18, ((void *)0))
              : errstart(18, ((void *)0)))
        (errcode((((('0') - '0') & 0x3F) + (((('1') - '0') & 0x3F) << 6) +
                  (((('0') - '0') & 0x3F) << 12) +
                  (((('0') - '0') & 0x3F) << 18) +
                  (((('0') - '0') & 0x3F) << 24))),
         errmsg("Pl/Proxy: foreign data wrapper validator disabled"),
         errhint("validator is usable starting from PostgreSQL version 8.4.3")),
            errfinish("src/cluster.c", 507, __func__);
      if (__builtin_constant_p(18) && (18) >= 21)
        abort();
    } while (0);
    return BoolGetDatum(0);
  }
  for (ForEachState cell__state = {(options_list), 0};
       (cell__state.l != ((List *)((void *)0)) &&
        cell__state.i < cell__state.l->length)
           ? (cell = &cell__state.l->elements[cell__state.i], 1)
           : (cell = ((void *)0), 0);
       cell__state.i++) {
    DefElem *def = ((cell)->ptr_value);
    char *arg = (((String *)castNodeImpl(T_String, def->arg))->sval);
    if (catalog == 1417) {
      if (extract_part_num(def->defname, &part_num)) {
        if (part_set == ((void *)0))
          part_set = palloc0(options_list->length + 1);
        if (part_num < 0 || part_num >= options_list->length)
          do {
            int __errno_location __attribute__((unused));
            if (__builtin_constant_p(21) && (21) >= 21
                    ? errstart_cold(21, ((void *)0))
                    : errstart(21, ((void *)0)))
              (errcode((((('4') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                        (((('6') - '0') & 0x3F) << 12) +
                        (((('0') - '0') & 0x3F) << 18) +
                        (((('1') - '0') & 0x3F) << 24))),
               errmsg("Pl/Proxy: partition numbers must start from 0 and be "
                      "numbered consecutively"),
               errhint("number of options is %d, got %d", options_list->length,
                       part_num)),
                  errfinish("src/cluster.c", 529, __func__);
            if (__builtin_constant_p(21) && (21) >= 21)
              abort();
          } while (0);
        if (part_set[part_num])
          do {
            int __errno_location __attribute__((unused));
            if (__builtin_constant_p(21) && (21) >= 21
                    ? errstart_cold(21, ((void *)0))
                    : errstart(21, ((void *)0)))
              (errcode((((('4') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                        (((('6') - '0') & 0x3F) << 12) +
                        (((('0') - '0') & 0x3F) << 18) +
                        (((('1') - '0') & 0x3F) << 24))),
               errmsg("Pl/Proxy: duplicate partition number: %d", part_num),
               errhint("got %d twice", part_num)),
                  errfinish("src/cluster.c", 534, __func__);
            if (__builtin_constant_p(21) && (21) >= 21)
              abort();
          } while (0);
        part_set[part_num] = 1;
        ++part_count;
      } else {
        validate_cluster_option(def->defname, arg);
        if (pg_strcasecmp(def->defname, "modular_mapping") == 0)
          modular_mapping = atoi(arg);
      }
    } else if (catalog == 1418) {
      if (pg_strcasecmp(def->defname, "user") != 0 &&
          pg_strcasecmp(def->defname, "password") != 0) {
        do {
          int __errno_location __attribute__((unused));
          if (__builtin_constant_p(21) && (21) >= 21
                  ? errstart_cold(21, ((void *)0))
                  : errstart(21, ((void *)0)))
            (errcode((((('4') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                      (((('6') - '0') & 0x3F) << 12) +
                      (((('0') - '0') & 0x3F) << 18) +
                      (((('1') - '0') & 0x3F) << 24))),
             errmsg("Pl/Proxy: invalid option to user mapping"),
             errhint("valid options are \"user\" and \"password\"")),
                errfinish("src/cluster.c", 554, __func__);
          if (__builtin_constant_p(21) && (21) >= 21)
            abort();
        } while (0);
      }
    } else if (catalog == 2328) {
      validate_cluster_option(def->defname, arg);
    }
  }
  if (catalog == 1417) {
    for (part_num = 0; part_num < part_count; part_num++) {
      if (!part_set[part_num])
        do {
          int __errno_location __attribute__((unused));
          if (__builtin_constant_p(21) && (21) >= 21
                  ? errstart_cold(21, ((void *)0))
                  : errstart(21, ((void *)0)))
            (errcode((((('4') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                      (((('6') - '0') & 0x3F) << 12) +
                      (((('0') - '0') & 0x3F) << 18) +
                      (((('1') - '0') & 0x3F) << 24))),
             errmsg("Pl/Proxy: missing partition"),
             errhint("missing number: %d", part_num)),
                errfinish("src/cluster.c", 570, __func__);
          if (__builtin_constant_p(21) && (21) >= 21)
            abort();
        } while (0);
    }
    if (!check_valid_partcount(part_count, modular_mapping))
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('4') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('6') - '0') & 0x3F) << 12) +
                    (((('0') - '0') & 0x3F) << 18) +
                    (((('1') - '0') & 0x3F) << 24))),
           errmsg("Pl/Proxy: invalid number of partitions"),
           errhint("the number of partitions in a cluster must be power of 2 "
                   "(attempted %d)",
                   part_count)),
              errfinish("src/cluster.c", 576, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    for (ForEachState cell__state = {(options_list), 0};
         (cell__state.l != ((List *)((void *)0)) &&
          cell__state.i < cell__state.l->length)
             ? (cell = &cell__state.l->elements[cell__state.i], 1)
             : (cell = ((void *)0), 0);
         cell__state.i++) {
      DefElem *def = ((cell)->ptr_value);
      if (!extract_part_num(def->defname, &part_num))
        continue;
      if (part_num < 0 || part_num >= part_count)
        do {
          int __errno_location __attribute__((unused));
          if (__builtin_constant_p(21) && (21) >= 21
                  ? errstart_cold(21, ((void *)0))
                  : errstart(21, ((void *)0)))
            (errcode((((('4') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                      (((('6') - '0') & 0x3F) << 12) +
                      (((('0') - '0') & 0x3F) << 18) +
                      (((('1') - '0') & 0x3F) << 24))),
             errmsg("Pl/Proxy: wrong partitions number - %d", part_num),
             errhint("the partitions number in a cluster must be >= 0 and < %d "
                     "(attempted %d)",
                     part_count, part_num)),
                errfinish("src/cluster.c", 589, __func__);
          if (__builtin_constant_p(21) && (21) >= 21)
            abort();
        } while (0);
    }
  }
  if (part_set)
    pfree(part_set);
  return BoolGetDatum(1);
}
void plproxy_append_cstr_option(StringInfo cstr, const char *name,
                                const char *val) {
  appendStringInfo(cstr, " %s='", name);
  for (; *val; val++) {
    if (*val == '\'' || *val == '\\')
      appendStringInfoChar(cstr, '\\');
    appendStringInfoChar(cstr, *val);
  }
  appendStringInfoChar(cstr, '\'');
}
static void reload_sqlmed_user(ProxyFunction *func, ProxyCluster *cluster) {
  ConnUserInfo *userinfo = cluster->cur_userinfo;
  UserMapping *um;
  HeapTuple tup;
  StringInfoData cstr;
  ListCell *cell;
  AclResult aclresult;
  _Bool got_user;
  Oid umid;
  um = GetUserMapping(userinfo->user_oid, cluster->sqlmed_server_oid);
  tup = SearchSysCache(USERMAPPINGUSERSERVER, ObjectIdGetDatum(um->userid),
                       ObjectIdGetDatum(um->serverid), 0, 0);
  if (!((const void *)(tup) != ((void *)0))) {
    tup = SearchSysCache(USERMAPPINGUSERSERVER, ObjectIdGetDatum(((Oid)0)),
                         ObjectIdGetDatum(um->serverid), 0, 0);
    if (!((const void *)(tup) != ((void *)0)))
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          errmsg_internal("cache lookup failed for user mapping (%u,%u)",
                          um->userid, um->serverid),
              errfinish("src/cluster.c", 642, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
  }
  umid = um->umid;
  scstamp_set(USERMAPPINGOID, &userinfo->umStamp, umid);
  ReleaseSysCache(tup);
  aclresult = object_aclcheck(1417, um->serverid, um->userid, (1 << 8));
  if (aclresult != ACLCHECK_OK)
    aclcheck_error(aclresult, OBJECT_FOREIGN_SERVER, cluster->name);
  got_user = 0;
  initStringInfo(&cstr);
  for (ForEachState cell__state = {(um->options), 0};
       (cell__state.l != ((List *)((void *)0)) &&
        cell__state.i < cell__state.l->length)
           ? (cell = &cell__state.l->elements[cell__state.i], 1)
           : (cell = ((void *)0), 0);
       cell__state.i++) {
    DefElem *def = ((cell)->ptr_value);
    if (strcmp(def->defname, "user") == 0)
      got_user = 1;
    plproxy_append_cstr_option(
        &cstr, def->defname,
        (((String *)castNodeImpl(T_String, def->arg))->sval));
  }
  if (!got_user)
    plproxy_append_cstr_option(&cstr, "user", userinfo->username);
  if (userinfo->extra_connstr) {
    memset(userinfo->extra_connstr, 0, strlen(userinfo->extra_connstr));
    pfree(userinfo->extra_connstr);
    userinfo->extra_connstr = ((void *)0);
  }
  userinfo->extra_connstr = MemoryContextStrdup(cluster_mem, cstr.data);
  memset(cstr.data, 0, cstr.len);
  pfree(cstr.data);
}
static void reload_sqlmed_cluster(ProxyFunction *func, ProxyCluster *cluster,
                                  ForeignServer *foreign_server) {
  ConnUserInfo *info = cluster->cur_userinfo;
  ForeignDataWrapper *fdw;
  HeapTuple tup;
  AclResult aclresult;
  ListCell *cell;
  int part_count = 0;
  int part_num;
  int i;
  char **part_ordered;
  fdw = GetForeignDataWrapper(foreign_server->fdwid);
  tup = SearchSysCache(FOREIGNSERVEROID,
                       ObjectIdGetDatum(foreign_server->serverid), 0, 0, 0);
  if (!((const void *)(tup) != ((void *)0)))
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("cache lookup failed for foreign server %u",
                        foreign_server->serverid),
            errfinish("src/cluster.c", 719, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
  scstamp_set(FOREIGNSERVEROID, &cluster->clusterStamp,
              foreign_server->serverid);
  ReleaseSysCache(tup);
  aclresult =
      object_aclcheck(1417, foreign_server->serverid, info->user_oid, (1 << 8));
  if (aclresult != ACLCHECK_OK)
    aclcheck_error(aclresult, OBJECT_FOREIGN_SERVER,
                   foreign_server->servername);
  clear_config(&cluster->config);
  for (ForEachState cell__state = {(fdw->options), 0};
       (cell__state.l != ((List *)((void *)0)) &&
        cell__state.i < cell__state.l->length)
           ? (cell = &cell__state.l->elements[cell__state.i], 1)
           : (cell = ((void *)0), 0);
       cell__state.i++) {
    DefElem *def = ((cell)->ptr_value);
    set_config_key(func, &cluster->config, def->defname,
                   (((String *)castNodeImpl(T_String, def->arg))->sval));
  }
  for (ForEachState cell__state = {(foreign_server->options), 0};
       (cell__state.l != ((List *)((void *)0)) &&
        cell__state.i < cell__state.l->length)
           ? (cell = &cell__state.l->elements[cell__state.i], 1)
           : (cell = ((void *)0), 0);
       cell__state.i++) {
    DefElem *def = ((cell)->ptr_value);
    if (extract_part_num(def->defname, &part_num)) {
      part_count++;
    } else
      set_config_key(func, &cluster->config, def->defname,
                     (((String *)castNodeImpl(T_String, def->arg))->sval));
  }
  if (!check_valid_partcount(part_count, cluster->config.modular_mapping))
    plproxy_error_with_state(
        (func),
        (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
         (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
         (((('0') - '0') & 0x3F) << 24)),
        "invalid partition count");
  allocate_cluster_partitions(cluster, part_count);
  part_ordered = palloc0(part_count * sizeof(char *));
  for (ForEachState cell__state = {(foreign_server->options), 0};
       (cell__state.l != ((List *)((void *)0)) &&
        cell__state.i < cell__state.l->length)
           ? (cell = &cell__state.l->elements[cell__state.i], 1)
           : (cell = ((void *)0), 0);
       cell__state.i++) {
    DefElem *def = ((cell)->ptr_value);
    char *arg = (((String *)castNodeImpl(T_String, def->arg))->sval);
    if (!extract_part_num(def->defname, &part_num))
      continue;
    if (part_num < 0 || part_num >= part_count)
      plproxy_error_with_state(
          (func),
          (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
           (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
           (((('0') - '0') & 0x3F) << 24)),
          "wrong partitions number, must be >= 0 and < %d", part_count);
    if (part_ordered[part_num])
      plproxy_error_with_state(
          (func),
          (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
           (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
           (((('0') - '0') & 0x3F) << 24)),
          "duplicate partition number: %d", part_num);
    part_ordered[part_num] = arg;
  }
  for (i = 0; i < part_count; i++) {
    add_connection(cluster, part_ordered[i], i);
  }
  pfree(part_ordered);
}
static void determine_compat_mode(ProxyCluster *cluster) {
  _Bool have_compat = 0;
  HeapTuple tup;
  tup = SearchSysCache(NAMESPACENAME, PointerGetDatum("plproxy"), 0, 0, 0);
  if (((const void *)(tup) != ((void *)0))) {
    Oid namespaceId = XNamespaceTupleGetOid(tup);
    Oid paramOids[] = {25};
    oidvector *parameterTypes = buildoidvector(paramOids, 1);
    const char **funcname;
    static const char *compat_functions[] = {
        "get_cluster_version", "get_cluster_config", "get_cluster_partitions",
        ((void *)0)};
    for (funcname = compat_functions; *funcname; funcname++) {
      if (!SearchSysCacheExists(PROCNAMEARGSNSP, PointerGetDatum(*funcname),
                                PointerGetDatum(parameterTypes),
                                ObjectIdGetDatum(namespaceId), 0))
        break;
    }
    if (!*funcname)
      have_compat = 1;
    ReleaseSysCache(tup);
  }
  if (!have_compat)
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("Pl/Proxy: cluster not found: %s", cluster->name),
            errfinish("src/cluster.c", 846, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
}
static void inval_one_umap(struct AANode *n, void *arg) {
  ConnUserInfo *info =
      ((ConnUserInfo *)((char *)(n) - __builtin_offsetof(ConnUserInfo, node)));
  SCInvalArg newStamp;
  if (info->needs_reload)
    return;
  if (arg == ((void *)0)) {
    info->needs_reload = 1;
    return;
  }
  newStamp = *(SCInvalArg *)arg;
  if (scstamp_check(USERMAPPINGOID, &info->umStamp, newStamp))
    info->needs_reload = 1;
}
static void inval_umapping(struct AANode *n, void *arg) {
  ProxyCluster *cluster =
      ((ProxyCluster *)((char *)(n) - __builtin_offsetof(ProxyCluster, node)));
  aatree_walk(&cluster->userinfo_tree, AA_WALK_IN_ORDER, inval_one_umap, arg);
}
static void inval_fserver(struct AANode *n, void *arg) {
  ProxyCluster *cluster =
      ((ProxyCluster *)((char *)(n) - __builtin_offsetof(ProxyCluster, node)));
  SCInvalArg newStamp = *(SCInvalArg *)arg;
  if (cluster->needs_reload)
    return;
  else if (!cluster->sqlmed_cluster)
    cluster->needs_reload = 1;
  else if (scstamp_check(FOREIGNSERVEROID, &cluster->clusterStamp, newStamp))
    cluster->needs_reload = 1;
  if (cluster->needs_reload)
    inval_umapping(&cluster->node, ((void *)0));
}
static void ClusterSyscacheCallback(Datum arg, int cacheid,
                                    SCInvalArg newStamp) {
  if (cacheid == FOREIGNSERVEROID)
    aatree_walk(&cluster_tree, AA_WALK_IN_ORDER, inval_fserver, &newStamp);
  else if (cacheid == USERMAPPINGOID)
    aatree_walk(&cluster_tree, AA_WALK_IN_ORDER, inval_umapping, &newStamp);
}
void plproxy_syscache_callback_init(void) {
  CacheRegisterSyscacheCallback(FOREIGNSERVEROID, ClusterSyscacheCallback,
                                (Datum)0);
  CacheRegisterSyscacheCallback(USERMAPPINGOID, ClusterSyscacheCallback,
                                (Datum)0);
}
static void reload_plproxy_cluster(ProxyFunction *func, ProxyCluster *cluster) {
  Datum dname =
      DirectFunctionCall1Coll(textin, ((Oid)0), CStringGetDatum(cluster->name));
  int cur_version;
  plproxy_cluster_plan_init();
  cur_version = get_version(func, dname);
  if (cur_version != cluster->version || cluster->needs_reload) {
    get_config(cluster, dname, func);
    reload_parts(cluster, dname, func);
    cluster->version = cur_version;
  }
}
static ProxyCluster *new_cluster(const char *name) {
  ProxyCluster *cluster;
  MemoryContext old_ctx;
  old_ctx = MemoryContextSwitchTo(cluster_mem);
  cluster = palloc0(sizeof(*cluster));
  cluster->name = pstrdup(name);
  aatree_init(&cluster->conn_tree, conn_cstr_cmp, conn_free);
  aatree_init(&cluster->userinfo_tree, userinfo_cmp, userinfo_free);
  MemoryContextSwitchTo(old_ctx);
  return cluster;
}
static void inval_userinfo_state(struct AANode *node, void *arg) {
  ProxyConnectionState *cur = ((
      ProxyConnectionState *)((char *)(node) -
                              __builtin_offsetof(ProxyConnectionState, node)));
  ConnUserInfo *userinfo = arg;
  if (cur->userinfo == userinfo && cur->db)
    plproxy_disconnect(cur);
}
static void inval_userinfo_conn(struct AANode *node, void *arg) {
  ProxyConnection *conn =
      ((ProxyConnection *)((char *)(node) -
                           __builtin_offsetof(ProxyConnection, node)));
  ConnUserInfo *userinfo = arg;
  aatree_walk(&conn->userstate_tree, AA_WALK_IN_ORDER, inval_userinfo_state,
              userinfo);
}
static void inval_user_connections(ProxyCluster *cluster,
                                   ConnUserInfo *userinfo) {
  aatree_walk(&cluster->conn_tree, AA_WALK_IN_ORDER, inval_userinfo_conn,
              userinfo);
  userinfo->needs_reload = 0;
}
static ConnUserInfo *get_userinfo(ProxyCluster *cluster, Oid user_oid) {
  ConnUserInfo *userinfo;
  struct AANode *node;
  const char *username;
  username = GetUserNameFromId(user_oid, 0);
  node = aatree_search(&cluster->userinfo_tree, (uintptr_t)username);
  if (node) {
    userinfo = ((ConnUserInfo *)((char *)(node) -
                                 __builtin_offsetof(ConnUserInfo, node)));
  } else {
    userinfo = MemoryContextAllocZero(cluster_mem, sizeof(*userinfo));
    userinfo->username = MemoryContextStrdup(cluster_mem, username);
    aatree_insert(&cluster->userinfo_tree, (uintptr_t)username,
                  &userinfo->node);
  }
  if (userinfo->user_oid != user_oid) {
    userinfo->user_oid = user_oid;
    userinfo->needs_reload = 1;
  }
  return userinfo;
}
static void refresh_cluster(ProxyFunction *func, ProxyCluster *cluster) {
  ConnUserInfo *uinfo;
  ProxyConfig *cf = &cluster->config;
  Oid user_oid = ((Oid)0);
  if (cf->default_user[0]) {
    if (strcmp(cf->default_user, "session_user") == 0)
      user_oid = GetSessionUserId();
    else if (strcmp(cf->default_user, "current_user") == 0)
      user_oid = GetUserId();
    else if (1)
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          errmsg_internal(
              "default_user: Expect 'current_user' or 'session_user', got '%s'",
              cf->default_user),
              errfinish("src/cluster.c", 1060, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    else
      user_oid = get_role_oid(cf->default_user, 0);
  } else {
    user_oid = GetUserId();
  }
  uinfo = get_userinfo(cluster, user_oid);
  cluster->cur_userinfo = uinfo;
  if (cluster->needs_reload) {
    ForeignServer *server;
    server = GetForeignServerByName(cluster->name, 1);
    cluster->sqlmed_cluster = (server != ((void *)0));
    if (!cluster->sqlmed_cluster)
      determine_compat_mode(cluster);
    else {
      cluster->sqlmed_server_oid = server->serverid;
      reload_sqlmed_cluster(func, cluster, server);
    }
  }
  if (uinfo->needs_reload) {
    if (cluster->sqlmed_cluster) {
      inval_user_connections(cluster, uinfo);
      reload_sqlmed_user(func, cluster);
    } else
      uinfo->needs_reload = 0;
  }
  if (!cluster->sqlmed_cluster && !cluster->fake_cluster)
    reload_plproxy_cluster(func, cluster);
  cluster->needs_reload = 0;
}
static ProxyCluster *fake_cluster(ProxyFunction *func,
                                  const char *connect_str) {
  ProxyCluster *cluster;
  MemoryContext old_ctx;
  struct AANode *n;
  n = aatree_search(&fake_cluster_tree, (uintptr_t)connect_str);
  if (n) {
    cluster = ((ProxyCluster *)((char *)(n) -
                                __builtin_offsetof(ProxyCluster, node)));
    goto done;
  }
  cluster = new_cluster(connect_str);
  old_ctx = MemoryContextSwitchTo(cluster_mem);
  cluster->fake_cluster = 1;
  cluster->version = 1;
  cluster->part_count = 1;
  cluster->part_mask = 0;
  cluster->part_map = palloc0(cluster->part_count * sizeof(ProxyConnection *));
  cluster->active_list =
      palloc0(cluster->part_count * sizeof(ProxyConnection *));
  MemoryContextSwitchTo(old_ctx);
  add_connection(cluster, connect_str, 0);
  aatree_insert(&fake_cluster_tree, (uintptr_t)connect_str, &cluster->node);
done:
  refresh_cluster(func, cluster);
  return cluster;
}
static const char *resolve_query(ProxyFunction *func, FunctionCallInfo fcinfo,
                                 ProxyQuery *query) {
  const char *name;
  HeapTuple row;
  TupleDesc desc;
  plproxy_query_exec(func, fcinfo, query, ((void *)0), 0);
  if (SPI_processed != 1)
    plproxy_error_with_state(
        (func),
        (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
         (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
         (((('0') - '0') & 0x3F) << 24)),
        "'%s' returned %d rows, expected 1", query->sql, (int)SPI_processed);
  desc = SPI_tuptable->tupdesc;
  if (SPI_gettypeid(desc, 1) != 25)
    plproxy_error_with_state(
        (func),
        (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
         (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
         (((('0') - '0') & 0x3F) << 24)),
        "expected text");
  row = SPI_tuptable->vals[0];
  name = SPI_getvalue(row, desc, 1);
  if (name == ((void *)0))
    plproxy_error_with_state(
        (func),
        (((('X') - '0') & 0x3F) + (((('X') - '0') & 0x3F) << 6) +
         (((('0') - '0') & 0x3F) << 12) + (((('0') - '0') & 0x3F) << 18) +
         (((('0') - '0') & 0x3F) << 24)),
        "Cluster/connect name map func returned NULL");
  return name;
}
ProxyCluster *plproxy_find_cluster(ProxyFunction *func,
                                   FunctionCallInfo fcinfo) {
  ProxyCluster *cluster = ((void *)0);
  const char *name;
  struct AANode *node;
  if (func->connect_sql) {
    const char *cstr;
    cstr = resolve_query(func, fcinfo, func->connect_sql);
    return fake_cluster(func, cstr);
  }
  if (func->connect_str)
    return fake_cluster(func, func->connect_str);
  if (func->cluster_sql)
    name = resolve_query(func, fcinfo, func->cluster_sql);
  else
    name = func->cluster_name;
  node = aatree_search(&cluster_tree, (uintptr_t)name);
  if (node)
    cluster = ((ProxyCluster *)((char *)(node) -
                                __builtin_offsetof(ProxyCluster, node)));
  if (!cluster) {
    cluster = new_cluster(name);
    cluster->needs_reload = 1;
    aatree_insert(&cluster_tree, (uintptr_t)name, &cluster->node);
  }
  refresh_cluster(func, cluster);
  return cluster;
}
void plproxy_activate_connection(struct ProxyConnection *conn) {
  ProxyCluster *cluster = conn->cluster;
  ConnUserInfo *userinfo = cluster->cur_userinfo;
  const char *username = userinfo->username;
  struct AANode *node;
  ProxyConnectionState *cur;
  cluster->active_list[cluster->active_count] = conn;
  cluster->active_count++;
  node = aatree_search(&conn->userstate_tree, (uintptr_t)username);
  if (node) {
    cur = ((ProxyConnectionState *)((char *)(node) -
                                    __builtin_offsetof(ProxyConnectionState,
                                                       node)));
  } else {
    cur = MemoryContextAllocZero(cluster_mem, sizeof(*cur));
    cur->userinfo = userinfo;
    aatree_insert(&conn->userstate_tree, (uintptr_t)username, &cur->node);
  }
  conn->cur = cur;
}
struct MaintInfo {
  struct ProxyConfig *cf;
  struct timeval *now;
};
static void clean_state(struct AANode *node, void *arg) {
  ProxyConnectionState *cur = ((
      ProxyConnectionState *)((char *)(node) -
                              __builtin_offsetof(ProxyConnectionState, node)));
  ConnUserInfo *uinfo = cur->userinfo;
  struct MaintInfo *maint = arg;
  ProxyConfig *cf = maint->cf;
  struct timeval *now = maint->now;
  time_t age;
  _Bool drop;
  if (!cur->db)
    return;
  drop = 0;
  if (PQstatus(cur->db) != CONNECTION_OK) {
    drop = 1;
  } else if (uinfo->needs_reload) {
    drop = 1;
  } else if (cf->connection_lifetime <= 0) {
  } else {
    age = now->tv_sec - cur->connect_time;
    if (age >= cf->connection_lifetime)
      drop = 1;
  }
  if (drop)
    plproxy_disconnect(cur);
}
static void clean_conn(struct AANode *node, void *arg) {
  ProxyConnection *conn =
      ((ProxyConnection *)((char *)(node) -
                           __builtin_offsetof(ProxyConnection, node)));
  struct MaintInfo *maint = arg;
  if (conn->res) {
    PQclear(conn->res);
    conn->res = ((void *)0);
  }
  aatree_walk(&conn->userstate_tree, AA_WALK_IN_ORDER, clean_state, maint);
}
static void clean_cluster(struct AANode *n, void *arg) {
  ProxyCluster *cluster =
      ((ProxyCluster *)((char *)(n) - __builtin_offsetof(ProxyCluster, node)));
  struct MaintInfo maint;
  maint.cf = &cluster->config;
  maint.now = arg;
  aatree_walk(&cluster->conn_tree, AA_WALK_IN_ORDER, clean_conn, &maint);
}
void plproxy_cluster_maint(struct timeval *now) {
  aatree_walk(&cluster_tree, AA_WALK_IN_ORDER, clean_cluster, now);
  aatree_walk(&fake_cluster_tree, AA_WALK_IN_ORDER, clean_cluster, now);
}
