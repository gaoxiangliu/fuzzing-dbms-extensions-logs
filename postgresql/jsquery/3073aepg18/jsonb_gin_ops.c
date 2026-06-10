#include "postgres.h"
#include "access/hash.h"
#include "catalog/pg_collation.h"
#include "catalog/pg_type.h"
#include "miscadmin.h"
#include "utils/builtins.h"
#include "utils/jsonb.h"
#include "jsquery.h"
typedef struct PathHashStack {
  uint32 hash;
  struct PathHashStack *parent;
} PathHashStack;
typedef struct {
  int32 vl_len_;
  uint32 hash;
  uint8 type;
  char data[1];
} GINKey;
typedef struct {
  Datum *entries;
  Pointer *extra_data;
  _Bool *partial_match;
  int *map;
  int count, total;
} Entries;
typedef struct {
  ExtractedNode *root;
  ExtractedNode *node;
  uint32 hash;
  _Bool lossyHash;
  GINKey *rightBound;
} KeyExtra;
static uint32 get_bloom_value(uint32 hash);
static uint32 get_path_bloom(PathHashStack *stack);
static GINKey *make_gin_key(JsonbValue *v, uint32 hash);
static GINKey *make_gin_key_string(uint32 hash);
static GINKey *make_gin_query_value_key(JsQueryItem *value, uint32 hash);
static GINKey *make_gin_query_key(ExtractedNode *node, _Bool *partialMatch,
                                  uint32 hash, KeyExtra *keyExtra);
static GINKey *make_gin_query_key_minus_inf(uint32 hash);
static int32 compare_gin_key_value(GINKey *arg1, GINKey *arg2);
static int add_entry(Entries *e, Datum key, Pointer extra, _Bool pmatch);
extern __attribute__((visibility("default"))) Datum
gin_compare_jsonb_value_path(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_gin_compare_jsonb_value_path(void);
const Pg_finfo_record *pg_finfo_gin_compare_jsonb_value_path(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
extern __attribute__((visibility("default"))) Datum
gin_compare_partial_jsonb_value_path(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_gin_compare_partial_jsonb_value_path(void);
const Pg_finfo_record *pg_finfo_gin_compare_partial_jsonb_value_path(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
extern __attribute__((visibility("default"))) Datum
gin_extract_jsonb_value_path(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_gin_extract_jsonb_value_path(void);
const Pg_finfo_record *pg_finfo_gin_extract_jsonb_value_path(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
extern __attribute__((visibility("default"))) Datum
gin_extract_jsonb_query_value_path(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_gin_extract_jsonb_query_value_path(void);
const Pg_finfo_record *pg_finfo_gin_extract_jsonb_query_value_path(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
extern __attribute__((visibility("default"))) Datum
gin_consistent_jsonb_value_path(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_gin_consistent_jsonb_value_path(void);
const Pg_finfo_record *pg_finfo_gin_consistent_jsonb_value_path(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
extern __attribute__((visibility("default"))) Datum
gin_triconsistent_jsonb_value_path(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_gin_triconsistent_jsonb_value_path(void);
const Pg_finfo_record *pg_finfo_gin_triconsistent_jsonb_value_path(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
extern __attribute__((visibility("default"))) Datum
gin_debug_query_value_path(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_gin_debug_query_value_path(void);
const Pg_finfo_record *pg_finfo_gin_debug_query_value_path(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum gin_compare_jsonb_value_path(FunctionCallInfo fcinfo);
Datum gin_compare_partial_jsonb_value_path(FunctionCallInfo fcinfo);
Datum gin_extract_jsonb_value_path(FunctionCallInfo fcinfo);
Datum gin_extract_jsonb_query_value_path(FunctionCallInfo fcinfo);
Datum gin_consistent_jsonb_value_path(FunctionCallInfo fcinfo);
Datum gin_triconsistent_jsonb_value_path(FunctionCallInfo fcinfo);
Datum gin_debug_query_value_path(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) Datum
gin_compare_jsonb_path_value(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_gin_compare_jsonb_path_value(void);
const Pg_finfo_record *pg_finfo_gin_compare_jsonb_path_value(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
extern __attribute__((visibility("default"))) Datum
gin_compare_partial_jsonb_path_value(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_gin_compare_partial_jsonb_path_value(void);
const Pg_finfo_record *pg_finfo_gin_compare_partial_jsonb_path_value(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
extern __attribute__((visibility("default"))) Datum
gin_extract_jsonb_path_value(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_gin_extract_jsonb_path_value(void);
const Pg_finfo_record *pg_finfo_gin_extract_jsonb_path_value(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
extern __attribute__((visibility("default"))) Datum
gin_extract_jsonb_query_path_value(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_gin_extract_jsonb_query_path_value(void);
const Pg_finfo_record *pg_finfo_gin_extract_jsonb_query_path_value(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
extern __attribute__((visibility("default"))) Datum
gin_consistent_jsonb_path_value(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_gin_consistent_jsonb_path_value(void);
const Pg_finfo_record *pg_finfo_gin_consistent_jsonb_path_value(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
extern __attribute__((visibility("default"))) Datum
gin_triconsistent_jsonb_path_value(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_gin_triconsistent_jsonb_path_value(void);
const Pg_finfo_record *pg_finfo_gin_triconsistent_jsonb_path_value(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
extern __attribute__((visibility("default"))) Datum
gin_debug_query_path_value(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_gin_debug_query_path_value(void);
const Pg_finfo_record *pg_finfo_gin_debug_query_path_value(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum gin_compare_jsonb_path_value(FunctionCallInfo fcinfo);
Datum gin_compare_partial_jsonb_path_value(FunctionCallInfo fcinfo);
Datum gin_extract_jsonb_path_value(FunctionCallInfo fcinfo);
Datum gin_extract_jsonb_query_path_value(FunctionCallInfo fcinfo);
Datum gin_consistent_jsonb_path_value(FunctionCallInfo fcinfo);
Datum gin_triconsistent_jsonb_path_value(FunctionCallInfo fcinfo);
Datum gin_debug_query_path_value(FunctionCallInfo fcinfo);
static int add_entry(Entries *e, Datum key, Pointer extra, _Bool pmatch) {
  int entryNum;
  if (!e->entries) {
    e->total = 16;
    e->entries = (Datum *)palloc(e->total * sizeof(Datum));
    e->extra_data = (Pointer *)palloc(e->total * sizeof(Pointer));
    e->partial_match = (_Bool *)palloc(e->total * sizeof(_Bool));
  }
  if (e->count + 1 > e->total) {
    e->total *= 2;
    e->entries = (Datum *)repalloc(e->entries, e->total * sizeof(Datum));
    e->extra_data =
        (Pointer *)repalloc(e->extra_data, e->total * sizeof(Pointer));
    e->partial_match =
        (_Bool *)repalloc(e->partial_match, e->total * sizeof(_Bool));
  }
  entryNum = e->count;
  e->count++;
  e->entries[entryNum] = key;
  e->extra_data[entryNum] = extra;
  e->partial_match[entryNum] = pmatch;
  return entryNum;
}
static uint32 get_bloom_value(uint32 hash) {
  int i, j, vals[2], val, tmp;
  uint32 res = 0;
  for (i = 0; i < 2; i++) {
    val = hash % (32 - i) + i;
    hash /= (32 - i);
    vals[i] = val;
    j = i;
    while (j > 0 && vals[j] <= vals[j - 1]) {
      tmp = vals[j] - 1;
      vals[j] = vals[j - 1];
      vals[j - 1] = tmp;
      j--;
    }
  }
  for (i = 0; i < 2; i++) {
    res |= (1 << vals[i]);
  }
  return res;
}
static uint32 get_path_bloom(PathHashStack *stack) {
  uint32 res = 0, val;
  while (stack) {
    uint32 hash = stack->hash;
    val = get_bloom_value(hash);
    res |= val;
    stack = stack->parent;
  }
  return res;
}
static uint32 get_query_path_bloom(PathItem *pathItem, _Bool *lossy) {
  uint32 res = 0, val;
  *lossy = 0;
  while (pathItem) {
    uint32 hash;
    if (pathItem->type == iKey) {
      hash = hash_any((unsigned char *)pathItem->s, pathItem->len);
      val = get_bloom_value(hash);
      res |= val;
    } else if (pathItem->type == iAny || pathItem->type == iAnyKey) {
      *lossy = 1;
    }
    pathItem = pathItem->parent;
  }
  return res;
}
static GINKey *make_gin_key(JsonbValue *v, uint32 hash) {
  GINKey *key;
  switch (v->type) {
  case jbvNull:
  case jbvObject: {
    key = (GINKey *)palloc(__builtin_offsetof(GINKey, data));
    key->type = v->type;
    (((varattrib_4b *)(key))->va_4byte.va_header =
         (((uint32)(__builtin_offsetof(GINKey, data))) << 2));
    break;
  }
  case jbvBool: {
    key = (GINKey *)palloc(__builtin_offsetof(GINKey, data));
    key->type = v->type | (v->val.boolean ? 0x80 : 0);
    (((varattrib_4b *)(key))->va_4byte.va_header =
         (((uint32)(__builtin_offsetof(GINKey, data))) << 2));
    break;
  }
  case jbvArray: {
    key = (GINKey *)palloc(__builtin_offsetof(GINKey, data));
    key->type = v->type;
    if (v->val.array.nElems == 0)
      key->type |= 0x80;
    (((varattrib_4b *)(key))->va_4byte.va_header =
         (((uint32)(__builtin_offsetof(GINKey, data))) << 2));
    break;
  }
  case jbvNumeric: {
    key = (GINKey *)palloc0((
        (((uintptr_t)((__builtin_offsetof(GINKey, data))) + ((4) - 1)) &
         ~((uintptr_t)((4) - 1))) +
        (((((varattrib_1b *)(v->val.numeric))->va_header) == 0x01)
             ? (__builtin_offsetof(varattrib_1b_e, va_data) +
                (((((varattrib_1b_e *)(v->val.numeric))->va_tag)) ==
                         VARTAG_INDIRECT
                     ? sizeof(varatt_indirect)
                 : ((((((varattrib_1b_e *)(v->val.numeric))->va_tag)) & ~1) ==
                    VARTAG_EXPANDED_RO)
                     ? sizeof(varatt_expanded)
                 : ((((varattrib_1b_e *)(v->val.numeric))->va_tag)) ==
                         VARTAG_ONDISK
                     ? sizeof(varatt_external)
                     : (((void)((0) || (ExceptionalCondition(
                                            "false", "jsonb_gin_ops.c", 289),
                                        0))),
                        0)))
             : (((((varattrib_1b *)(v->val.numeric))->va_header & 0x01) == 0x01)
                    ? ((((varattrib_1b *)(v->val.numeric))->va_header >> 1) &
                       0x7F)
                    : ((((varattrib_4b *)(v->val.numeric))
                            ->va_4byte.va_header >>
                        2) &
                       0x3FFFFFFF)))));
    key->type = v->type;
    memcpy(
        ((Pointer)key +
         (((uintptr_t)((__builtin_offsetof(GINKey, data))) + ((4) - 1)) &
          ~((uintptr_t)((4) - 1)))),
        v->val.numeric,
        (((((varattrib_1b *)(v->val.numeric))->va_header) == 0x01)
             ? (__builtin_offsetof(varattrib_1b_e, va_data) +
                (((((varattrib_1b_e *)(v->val.numeric))->va_tag)) ==
                         VARTAG_INDIRECT
                     ? sizeof(varatt_indirect)
                 : ((((((varattrib_1b_e *)(v->val.numeric))->va_tag)) & ~1) ==
                    VARTAG_EXPANDED_RO)
                     ? sizeof(varatt_expanded)
                 : ((((varattrib_1b_e *)(v->val.numeric))->va_tag)) ==
                         VARTAG_ONDISK
                     ? sizeof(varatt_external)
                     : (((void)((0) || (ExceptionalCondition(
                                            "false", "jsonb_gin_ops.c", 291),
                                        0))),
                        0)))
             : (((((varattrib_1b *)(v->val.numeric))->va_header & 0x01) == 0x01)
                    ? ((((varattrib_1b *)(v->val.numeric))->va_header >> 1) &
                       0x7F)
                    : ((((varattrib_4b *)(v->val.numeric))
                            ->va_4byte.va_header >>
                        2) &
                       0x3FFFFFFF))));
    (((varattrib_4b *)(key))->va_4byte.va_header =
         (((uint32)((
              (((uintptr_t)((__builtin_offsetof(GINKey, data))) + ((4) - 1)) &
               ~((uintptr_t)((4) - 1))) +
              (((((varattrib_1b *)(v->val.numeric))->va_header) == 0x01)
                   ? (__builtin_offsetof(varattrib_1b_e, va_data) +
                      (((((varattrib_1b_e *)(v->val.numeric))->va_tag)) ==
                               VARTAG_INDIRECT
                           ? sizeof(varatt_indirect)
                       : ((((((varattrib_1b_e *)(v->val.numeric))->va_tag)) &
                           ~1) == VARTAG_EXPANDED_RO)
                           ? sizeof(varatt_expanded)
                       : ((((varattrib_1b_e *)(v->val.numeric))->va_tag)) ==
                               VARTAG_ONDISK
                           ? sizeof(varatt_external)
                           : (((void)((0) ||
                                      (ExceptionalCondition(
                                           "false", "jsonb_gin_ops.c", 292),
                                       0))),
                              0)))
                   : (((((varattrib_1b *)(v->val.numeric))->va_header & 0x01) ==
                       0x01)
                          ? ((((varattrib_1b *)(v->val.numeric))->va_header >>
                              1) &
                             0x7F)
                          : ((((varattrib_4b *)(v->val.numeric))
                                  ->va_4byte.va_header >>
                              2) &
                             0x3FFFFFFF))))))
          << 2));
    break;
  }
  case jbvString: {
    key = (GINKey *)palloc0(
        ((((uintptr_t)((__builtin_offsetof(GINKey, data))) + ((4) - 1)) &
          ~((uintptr_t)((4) - 1))) +
         sizeof(uint32)));
    key->type = v->type;
    (*(uint32 *)((Pointer)key +
                 (((uintptr_t)((__builtin_offsetof(GINKey, data))) +
                   ((4) - 1)) &
                  ~((uintptr_t)((4) - 1))))) =
        hash_any((unsigned char *)v->val.string.val, v->val.string.len);
    (((varattrib_4b *)(key))->va_4byte.va_header =
         (((uint32)((
              (((uintptr_t)((__builtin_offsetof(GINKey, data))) + ((4) - 1)) &
               ~((uintptr_t)((4) - 1))) +
              sizeof(uint32))))
          << 2));
    break;
  }
  default:
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("GINKey must be scalar"),
            errfinish("jsonb_gin_ops.c", 305, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
  }
  key->hash = hash;
  return key;
}
static GINKey *make_gin_key_string(uint32 hash) {
  GINKey *key;
  key = (GINKey *)palloc(
      ((((uintptr_t)((__builtin_offsetof(GINKey, data))) + ((4) - 1)) &
        ~((uintptr_t)((4) - 1))) +
       sizeof(uint32)));
  key->type = jbvString;
  (*(uint32 *)((Pointer)key +
               (((uintptr_t)((__builtin_offsetof(GINKey, data))) + ((4) - 1)) &
                ~((uintptr_t)((4) - 1))))) = 0;
  (((varattrib_4b *)(key))->va_4byte.va_header =
       (((uint32)((
            (((uintptr_t)((__builtin_offsetof(GINKey, data))) + ((4) - 1)) &
             ~((uintptr_t)((4) - 1))) +
            sizeof(uint32))))
        << 2));
  key->hash = hash;
  return key;
}
static GINKey *make_gin_query_value_key(JsQueryItem *value, uint32 hash) {
  GINKey *key;
  int32 len;
  char *s;
  Numeric numeric;
  switch (value->type) {
  case jqiNull:
    key = (GINKey *)palloc(__builtin_offsetof(GINKey, data));
    key->type = jbvNull;
    (((varattrib_4b *)(key))->va_4byte.va_header =
         (((uint32)(__builtin_offsetof(GINKey, data))) << 2));
    break;
  case jqiString:
    key = (GINKey *)palloc(
        ((((uintptr_t)((__builtin_offsetof(GINKey, data))) + ((4) - 1)) &
          ~((uintptr_t)((4) - 1))) +
         sizeof(uint32)));
    key->type = jbvString;
    s = jsqGetString(value, &len);
    (*(uint32 *)((Pointer)key +
                 (((uintptr_t)((__builtin_offsetof(GINKey, data))) +
                   ((4) - 1)) &
                  ~((uintptr_t)((4) - 1))))) =
        hash_any((unsigned char *)s, len);
    (((varattrib_4b *)(key))->va_4byte.va_header =
         (((uint32)((
              (((uintptr_t)((__builtin_offsetof(GINKey, data))) + ((4) - 1)) &
               ~((uintptr_t)((4) - 1))) +
              sizeof(uint32))))
          << 2));
    break;
  case jqiBool:
    key = (GINKey *)palloc(__builtin_offsetof(GINKey, data));
    key->type = jbvBool | (jsqGetBool(value) ? 0x80 : 0);
    (((varattrib_4b *)(key))->va_4byte.va_header =
         (((uint32)(__builtin_offsetof(GINKey, data))) << 2));
    break;
  case jqiNumeric:
    numeric = jsqGetNumeric(value);
    key = (GINKey *)palloc(
        ((((uintptr_t)((__builtin_offsetof(GINKey, data))) + ((4) - 1)) &
          ~((uintptr_t)((4) - 1))) +
         (((((varattrib_1b *)(numeric))->va_header) == 0x01)
              ? (__builtin_offsetof(varattrib_1b_e, va_data) +
                 (((((varattrib_1b_e *)(numeric))->va_tag)) == VARTAG_INDIRECT
                      ? sizeof(varatt_indirect)
                  : ((((((varattrib_1b_e *)(numeric))->va_tag)) & ~1) ==
                     VARTAG_EXPANDED_RO)
                      ? sizeof(varatt_expanded)
                  : ((((varattrib_1b_e *)(numeric))->va_tag)) == VARTAG_ONDISK
                      ? sizeof(varatt_external)
                      : (((void)((0) || (ExceptionalCondition(
                                             "false", "jsonb_gin_ops.c", 354),
                                         0))),
                         0)))
              : (((((varattrib_1b *)(numeric))->va_header & 0x01) == 0x01)
                     ? ((((varattrib_1b *)(numeric))->va_header >> 1) & 0x7F)
                     : ((((varattrib_4b *)(numeric))->va_4byte.va_header >> 2) &
                        0x3FFFFFFF)))));
    key->type = jbvNumeric;
    memcpy(
        ((Pointer)key +
         (((uintptr_t)((__builtin_offsetof(GINKey, data))) + ((4) - 1)) &
          ~((uintptr_t)((4) - 1)))),
        numeric,
        (((((varattrib_1b *)(numeric))->va_header) == 0x01)
             ? (__builtin_offsetof(varattrib_1b_e, va_data) +
                (((((varattrib_1b_e *)(numeric))->va_tag)) == VARTAG_INDIRECT
                     ? sizeof(varatt_indirect)
                 : ((((((varattrib_1b_e *)(numeric))->va_tag)) & ~1) ==
                    VARTAG_EXPANDED_RO)
                     ? sizeof(varatt_expanded)
                 : ((((varattrib_1b_e *)(numeric))->va_tag)) == VARTAG_ONDISK
                     ? sizeof(varatt_external)
                     : (((void)((0) || (ExceptionalCondition(
                                            "false", "jsonb_gin_ops.c", 356),
                                        0))),
                        0)))
             : (((((varattrib_1b *)(numeric))->va_header & 0x01) == 0x01)
                    ? ((((varattrib_1b *)(numeric))->va_header >> 1) & 0x7F)
                    : ((((varattrib_4b *)(numeric))->va_4byte.va_header >> 2) &
                       0x3FFFFFFF))));
    (((varattrib_4b *)(key))->va_4byte.va_header =
         (((uint32)((
              (((uintptr_t)((__builtin_offsetof(GINKey, data))) + ((4) - 1)) &
               ~((uintptr_t)((4) - 1))) +
              (((((varattrib_1b *)(numeric))->va_header) == 0x01)
                   ? (__builtin_offsetof(varattrib_1b_e, va_data) +
                      (((((varattrib_1b_e *)(numeric))->va_tag)) ==
                               VARTAG_INDIRECT
                           ? sizeof(varatt_indirect)
                       : ((((((varattrib_1b_e *)(numeric))->va_tag)) & ~1) ==
                          VARTAG_EXPANDED_RO)
                           ? sizeof(varatt_expanded)
                       : ((((varattrib_1b_e *)(numeric))->va_tag)) ==
                               VARTAG_ONDISK
                           ? sizeof(varatt_external)
                           : (((void)((0) ||
                                      (ExceptionalCondition(
                                           "false", "jsonb_gin_ops.c", 357),
                                       0))),
                              0)))
                   : (((((varattrib_1b *)(numeric))->va_header & 0x01) == 0x01)
                          ? ((((varattrib_1b *)(numeric))->va_header >> 1) &
                             0x7F)
                          : ((((varattrib_4b *)(numeric))->va_4byte.va_header >>
                              2) &
                             0x3FFFFFFF))))))
          << 2));
    break;
  default:
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("Wrong state"),
            errfinish("jsonb_gin_ops.c", 360, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
  }
  key->hash = hash;
  return key;
}
static GINKey *make_gin_query_key(ExtractedNode *node, _Bool *partialMatch,
                                  uint32 hash, KeyExtra *keyExtra) {
  JsonbValue v;
  GINKey *key;
  switch (node->type) {
  case eExactValue:
    key = make_gin_query_value_key(node->exactValue, hash);
    break;
  case eEmptyArray:
    v.type = jbvArray;
    v.val.array.nElems = 0;
    key = make_gin_key(&v, hash);
    break;
  case eInequality:
    *partialMatch = 1;
    if (node->bounds.leftBound)
      key = make_gin_query_value_key(node->bounds.leftBound, hash);
    else
      key = make_gin_query_key_minus_inf(hash);
    if (node->bounds.rightBound)
      keyExtra->rightBound =
          make_gin_query_value_key(node->bounds.rightBound, hash);
    else
      keyExtra->rightBound = ((void *)0);
    break;
  case eIs:
    switch (node->isType) {
    case jbvArray:
      *partialMatch = 1;
      v.type = jbvArray;
      v.val.array.nElems = 1;
      key = make_gin_key(&v, hash);
      break;
    case jbvObject:
      *partialMatch = 1;
      v.type = jbvObject;
      key = make_gin_key(&v, hash);
      break;
    case jbvString:
      *partialMatch = 1;
      key = make_gin_key_string(hash);
      break;
    case jbvNumeric:
      *partialMatch = 1;
      key = make_gin_query_key_minus_inf(hash);
      break;
    case jbvBool:
      *partialMatch = 1;
      v.type = jbvBool;
      v.val.boolean = 0;
      key = make_gin_key(&v, hash);
      break;
    case jbvNull:
      v.type = jbvNull;
      key = make_gin_key(&v, hash);
      break;
    default:
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          errmsg_internal("Wrong type"),
              errfinish("jsonb_gin_ops.c", 427, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
      return ((void *)0);
    }
    break;
  case eAny:
    v.type = jbvNull;
    key = make_gin_key(&v, hash);
    *partialMatch = 1;
    break;
  default:
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("Wrong type"),
            errfinish("jsonb_gin_ops.c", 437, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
    break;
  }
  return key;
}
static GINKey *make_gin_query_key_minus_inf(uint32 hash) {
  GINKey *key;
  key = (GINKey *)palloc(__builtin_offsetof(GINKey, data));
  key->type = jbvNumeric | 0x80;
  key->hash = hash;
  (((varattrib_4b *)(key))->va_4byte.va_header =
       (((uint32)(__builtin_offsetof(GINKey, data))) << 2));
  return key;
}
static _Bool check_value_path_entry_handler(ExtractedNode *node,
                                            Pointer extra) {
  return 1;
}
static int make_value_path_entry_handler(ExtractedNode *node, Pointer extra) {
  Entries *e = (Entries *)extra;
  uint32 hash;
  _Bool lossy, partialMatch = 0;
  GINKey *key;
  KeyExtra *keyExtra;
  int result;
  do {
    if (!(!isLogicalNodeType(node->type)))
      ExceptionalCondition("!isLogicalNodeType(node->type)", "jsonb_gin_ops.c",
                           472);
  } while (0);
  hash = get_query_path_bloom(node->path, &lossy);
  keyExtra = (KeyExtra *)palloc(sizeof(KeyExtra));
  keyExtra->hash = hash;
  keyExtra->node = node;
  keyExtra->lossyHash = lossy;
  key = make_gin_query_key(node, &partialMatch, hash, keyExtra);
  result = add_entry(e, PointerGetDatum(key), (Pointer)keyExtra,
                     lossy | partialMatch);
  return result;
}
static int32 compare_gin_key_value(GINKey *arg1, GINKey *arg2) {
  if (((arg1)->type & 0x7F) != ((arg2)->type & 0x7F)) {
    return (((arg1)->type & 0x7F) > ((arg2)->type & 0x7F)) ? 1 : -1;
  } else {
    switch (((arg1)->type & 0x7F)) {
    case jbvNull:
    case jbvArray:
      if (((arg1)->type & 0x80) == ((arg2)->type & 0x80))
        return 0;
      else if (((arg1)->type & 0x80) > ((arg2)->type & 0x80))
        return 1;
      else
        return -1;
    case jbvObject:
      return 0;
    case jbvBool:
      if (((arg1)->type & 0x80) == ((arg2)->type & 0x80))
        return 0;
      else if (((arg1)->type & 0x80) > ((arg2)->type & 0x80))
        return 1;
      else
        return -1;
    case jbvNumeric:
      if (((arg1)->type & 0x80)) {
        if (((arg2)->type & 0x80))
          return 0;
        else
          return -1;
      } else {
        if (((arg2)->type & 0x80))
          return 1;
      }
      return DatumGetInt32(DirectFunctionCall2Coll(
          numeric_cmp, ((Oid)0),
          PointerGetDatum(
              ((Pointer)arg1 +
               (((uintptr_t)((__builtin_offsetof(GINKey, data))) + ((4) - 1)) &
                ~((uintptr_t)((4) - 1))))),
          PointerGetDatum(
              ((Pointer)arg2 +
               (((uintptr_t)((__builtin_offsetof(GINKey, data))) + ((4) - 1)) &
                ~((uintptr_t)((4) - 1)))))));
    case jbvString:
      if ((*(uint32 *)((Pointer)arg1 +
                       (((uintptr_t)((__builtin_offsetof(GINKey, data))) +
                         ((4) - 1)) &
                        ~((uintptr_t)((4) - 1))))) <
          (*(uint32 *)((Pointer)arg2 +
                       (((uintptr_t)((__builtin_offsetof(GINKey, data))) +
                         ((4) - 1)) &
                        ~((uintptr_t)((4) - 1))))))
        return -1;
      else if ((*(uint32 *)((Pointer)arg1 +
                            (((uintptr_t)((__builtin_offsetof(GINKey, data))) +
                              ((4) - 1)) &
                             ~((uintptr_t)((4) - 1))))) ==
               (*(uint32 *)((Pointer)arg2 +
                            (((uintptr_t)((__builtin_offsetof(GINKey, data))) +
                              ((4) - 1)) &
                             ~((uintptr_t)((4) - 1))))))
        return 0;
      else
        return 1;
    default:
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          errmsg_internal("GINKey must be scalar"),
              errfinish("jsonb_gin_ops.c", 539, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
      return 0;
    }
  }
}
Datum gin_compare_jsonb_value_path(FunctionCallInfo fcinfo) {
  GINKey *arg1 = (GINKey *)pg_detoast_datum(
      (struct varlena *)DatumGetPointer((fcinfo->args[0].value)));
  GINKey *arg2 = (GINKey *)pg_detoast_datum(
      (struct varlena *)DatumGetPointer((fcinfo->args[1].value)));
  int32 result = 0;
  result = compare_gin_key_value(arg1, arg2);
  if (result == 0 && arg1->hash != arg2->hash) {
    result = (arg1->hash > arg2->hash) ? 1 : -1;
  }
  do {
    if ((Pointer)(arg1) != DatumGetPointer((fcinfo->args[0].value)))
      pfree(arg1);
  } while (0);
  do {
    if ((Pointer)(arg2) != DatumGetPointer((fcinfo->args[1].value)))
      pfree(arg2);
  } while (0);
  return Int32GetDatum(result);
}
Datum gin_compare_partial_jsonb_value_path(FunctionCallInfo fcinfo) {
  GINKey *partial_key = (GINKey *)pg_detoast_datum(
      (struct varlena *)DatumGetPointer((fcinfo->args[0].value)));
  GINKey *key = (GINKey *)pg_detoast_datum(
      (struct varlena *)DatumGetPointer((fcinfo->args[1].value)));
  StrategyNumber strategy = DatumGetUInt16((fcinfo->args[2].value));
  int32 result;
  if (strategy == 14) {
    KeyExtra *extra = (KeyExtra *)DatumGetPointer((fcinfo->args[3].value));
    ExtractedNode *node = extra->node;
    switch (node->type) {
    case eExactValue:
    case eEmptyArray:
      result = compare_gin_key_value(key, partial_key);
      break;
    case eInequality:
      result = 0;
      if (!node->bounds.leftInclusive &&
          compare_gin_key_value(key, partial_key) <= 0) {
        result = -1;
      }
      if (result == 0 && extra->rightBound) {
        result = compare_gin_key_value(key, extra->rightBound);
        if ((node->bounds.rightInclusive && result <= 0) || result < 0)
          result = 0;
        else
          result = 1;
      }
      break;
    case eIs:
      if (node->isType == ((key)->type & 0x7F))
        result = 0;
      else
        result = (((key)->type & 0x7F) > node->isType) ? 1 : -1;
      break;
    case eAny:
      result = 0;
      break;
    default:
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          errmsg_internal("Wrong type"),
              errfinish("jsonb_gin_ops.c", 608, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
      break;
    }
    if (result == 0) {
      if (extra->lossyHash) {
        if ((key->hash & extra->hash) != extra->hash)
          result = -1;
      } else {
        if (key->hash != extra->hash)
          result = -1;
      }
    }
  } else {
    uint32 *extra_data = (uint32 *)DatumGetPointer((fcinfo->args[3].value));
    uint32 bloom = *extra_data;
    result = compare_gin_key_value(key, partial_key);
    if (result == 0) {
      if ((key->hash & bloom) != bloom)
        result = -1;
    }
  }
  do {
    if ((Pointer)(partial_key) != DatumGetPointer((fcinfo->args[0].value)))
      pfree(partial_key);
  } while (0);
  do {
    if ((Pointer)(key) != DatumGetPointer((fcinfo->args[1].value)))
      pfree(key);
  } while (0);
  return Int32GetDatum(result);
}
static Datum *gin_extract_jsonb_value_path_internal(Jsonb *jb, int32 *nentries,
                                                    uint32 **bloom) {
  int total =
      2 * (*(uint32 *)(((varattrib_4b *)(jb))->va_4byte.va_data) & 0x0FFFFFFF);
  JsonbIterator *it;
  JsonbValue v;
  PathHashStack *stack;
  int i = 0, r;
  Datum *entries = ((void *)0);
  uint32 hash;
  if (total == 0) {
    *nentries = 0;
    return ((void *)0);
  }
  entries = (Datum *)palloc(sizeof(Datum) * total);
  if (bloom)
    (*bloom) = (uint32 *)palloc(sizeof(uint32) * total);
  it = JsonbIteratorInit(&jb->root);
  stack = ((void *)0);
  while ((r = JsonbIteratorNext(&it, &v, 0)) != WJB_DONE) {
    PathHashStack *tmp;
    if (i >= total) {
      total *= 2;
      entries = (Datum *)repalloc(entries, sizeof(Datum) * total);
      if (bloom)
        (*bloom) = (uint32 *)repalloc(*bloom, sizeof(uint32) * total);
    }
    switch (r) {
    case WJB_BEGIN_ARRAY:
      if (!v.val.array.rawScalar)
        entries[i++] = PointerGetDatum(make_gin_key(&v, get_path_bloom(stack)));
      break;
    case WJB_BEGIN_OBJECT:
      entries[i++] = PointerGetDatum(make_gin_key(&v, get_path_bloom(stack)));
      tmp = stack;
      stack = (PathHashStack *)palloc(sizeof(PathHashStack));
      stack->parent = tmp;
      break;
    case WJB_KEY:
      if (!stack)
        do {
          int __errno_location __attribute__((unused));
          if (__builtin_constant_p(21) && (21) >= 21
                  ? errstart_cold(21, ((void *)0))
                  : errstart(21, ((void *)0)))
            errmsg_internal("error jsonb iteration"),
                errfinish("jsonb_gin_ops.c", 697, __func__);
          if (__builtin_constant_p(21) && (21) >= 21)
            abort();
        } while (0);
      stack->hash = 0;
      JsonbHashScalarValue(&v, &stack->hash);
      break;
    case WJB_ELEM:
    case WJB_VALUE:
      if (bloom) {
        (*bloom)[i] = get_path_bloom(stack);
        hash = 0;
      } else {
        hash = get_path_bloom(stack);
      }
      entries[i++] = PointerGetDatum(make_gin_key(&v, hash));
      break;
    case WJB_END_OBJECT:
      if (!stack)
        do {
          int __errno_location __attribute__((unused));
          if (__builtin_constant_p(21) && (21) >= 21
                  ? errstart_cold(21, ((void *)0))
                  : errstart(21, ((void *)0)))
            errmsg_internal("error jsonb iteration"),
                errfinish("jsonb_gin_ops.c", 717, __func__);
          if (__builtin_constant_p(21) && (21) >= 21)
            abort();
        } while (0);
      tmp = stack->parent;
      pfree(stack);
      stack = tmp;
      break;
    case WJB_END_ARRAY:
      break;
    default:
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          errmsg_internal("invalid JsonbIteratorNext rc: %d", r),
              errfinish("jsonb_gin_ops.c", 725, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  }
  *nentries = i;
  return entries;
}
Datum gin_extract_jsonb_value_path(FunctionCallInfo fcinfo) {
  Jsonb *jb = DatumGetJsonbP((fcinfo->args[0].value));
  int32 *nentries = (int32 *)DatumGetPointer((fcinfo->args[1].value));
  return PointerGetDatum(
      gin_extract_jsonb_value_path_internal(jb, nentries, ((void *)0)));
}
Datum gin_debug_query_value_path(FunctionCallInfo fcinfo) {
  JsQuery *jq;
  Entries e = {0};
  char *s;
  jq = ((JsQuery *)pg_detoast_datum(
      (struct varlena *)DatumGetPointer((fcinfo->args[0].value))));
  s = debugJsQuery(jq, make_value_path_entry_handler,
                   check_value_path_entry_handler, (Pointer)&e);
  return PointerGetDatum(cstring_to_text(s));
}
Datum gin_extract_jsonb_query_value_path(FunctionCallInfo fcinfo) {
  Jsonb *jb;
  int32 *nentries = (int32 *)DatumGetPointer((fcinfo->args[1].value));
  StrategyNumber strategy = DatumGetUInt16((fcinfo->args[2].value));
  _Bool **pmatch = (_Bool **)DatumGetPointer((fcinfo->args[3].value));
  Pointer **extra_data = (Pointer **)DatumGetPointer((fcinfo->args[4].value));
  int32 *searchMode = (int32 *)DatumGetPointer((fcinfo->args[6].value));
  Datum *entries = ((void *)0);
  int i, n;
  uint32 *bloom;
  Entries e = {0};
  JsQuery *jq;
  ExtractedNode *root;
  switch (strategy) {
  case 7:
    jb = DatumGetJsonbP((fcinfo->args[0].value));
    entries = gin_extract_jsonb_value_path_internal(jb, nentries, ((void *)0));
    break;
  case 13:
    jb = DatumGetJsonbP((fcinfo->args[0].value));
    entries = gin_extract_jsonb_value_path_internal(jb, nentries, &bloom);
    n = *nentries;
    *pmatch = (_Bool *)palloc(sizeof(_Bool) * n);
    for (i = 0; i < n; i++)
      (*pmatch)[i] = 1;
    *extra_data = (Pointer *)palloc(sizeof(Pointer) * n);
    for (i = 0; i < n; i++)
      (*extra_data)[i] = (Pointer)&bloom[i];
    break;
  case 14:
    jq = ((JsQuery *)pg_detoast_datum(
        (struct varlena *)DatumGetPointer((fcinfo->args[0].value))));
    root = extractJsQuery(jq, make_value_path_entry_handler,
                          check_value_path_entry_handler, (Pointer)&e);
    if (root) {
      *nentries = e.count;
      entries = e.entries;
      *pmatch = e.partial_match;
      *extra_data = e.extra_data;
      for (i = 0; i < e.count; i++)
        ((KeyExtra *)e.extra_data[i])->root = root;
    } else {
      entries = ((void *)0);
      *nentries = 0;
    }
    break;
  default:
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("unrecognized strategy number: %d", strategy),
            errfinish("jsonb_gin_ops.c", 814, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
    break;
  }
  if (entries == ((void *)0))
    *searchMode = 2;
  return PointerGetDatum(entries);
}
Datum gin_consistent_jsonb_value_path(FunctionCallInfo fcinfo) {
  _Bool *check = (_Bool *)DatumGetPointer((fcinfo->args[0].value));
  StrategyNumber strategy = DatumGetUInt16((fcinfo->args[1].value));
  int32 nkeys = DatumGetInt32((fcinfo->args[3].value));
  Pointer *extra_data = (Pointer *)DatumGetPointer((fcinfo->args[4].value));
  _Bool *recheck = (_Bool *)DatumGetPointer((fcinfo->args[5].value));
  _Bool res = 1;
  int32 i;
  *recheck = 1;
  switch (strategy) {
  case 7:
  case 13:
    for (i = 0; i < nkeys; i++) {
      if (!check[i]) {
        res = 0;
        break;
      }
    }
    break;
  case 14:
    if (nkeys == 0)
      res = 1;
    else
      res = execRecursive(((KeyExtra *)extra_data[0])->root, check);
    break;
  default:
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("unrecognized strategy number: %d", strategy),
            errfinish("jsonb_gin_ops.c", 860, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
    break;
  }
  return BoolGetDatum(res);
}
Datum gin_triconsistent_jsonb_value_path(FunctionCallInfo fcinfo) {
  GinTernaryValue *check =
      (GinTernaryValue *)DatumGetPointer((fcinfo->args[0].value));
  StrategyNumber strategy = DatumGetUInt16((fcinfo->args[1].value));
  int32 nkeys = DatumGetInt32((fcinfo->args[3].value));
  Pointer *extra_data = (Pointer *)DatumGetPointer((fcinfo->args[4].value));
  GinTernaryValue res = 1;
  int32 i;
  _Bool has_maybe = 0;
  switch (strategy) {
  case 7:
  case 13:
    for (i = 0; i < nkeys; i++) {
      if (check[i] == 0) {
        res = 0;
        break;
      }
      if (check[i] == 2) {
        res = 2;
        has_maybe = 1;
      }
    }
    if (!has_maybe && res == 1)
      res = 2;
    break;
  case 14:
    if (nkeys == 0)
      res = 2;
    else
      res = execRecursiveTristate(((KeyExtra *)extra_data[0])->root, check);
    if (res == 1)
      res = 2;
    break;
  default:
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("unrecognized strategy number: %d", strategy),
            errfinish("jsonb_gin_ops.c", 925, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
    break;
  }
  return GinTernaryValueGetDatum(res);
}
static _Bool get_query_path_hash(PathItem *pathItem, uint32 *hash) {
  check_stack_depth();
  if (!pathItem)
    return 1;
  if (!get_query_path_hash(pathItem->parent, hash)) {
    return 0;
  } else {
    if (pathItem->type == iAny || pathItem->type == iAnyKey) {
      return 0;
    } else {
      if (pathItem->type == iKey) {
        *hash = (*hash << 1) | (*hash >> 31);
        *hash ^= hash_any((unsigned char *)pathItem->s, pathItem->len);
      } else if (pathItem->type == iAnyArray || pathItem->type == iIndexArray) {
        *hash = (*hash << 1) | (*hash >> 31);
        *hash ^= 0x40000000;
      }
      return 1;
    }
  }
}
static _Bool check_path_value_entry_handler(ExtractedNode *node,
                                            Pointer extra) {
  uint32 hash;
  hash = 0;
  if (!get_query_path_hash(node->path, &hash))
    return 0;
  return 1;
}
static int make_path_value_entry_handler(ExtractedNode *node, Pointer extra) {
  Entries *e = (Entries *)extra;
  uint32 hash;
  GINKey *key;
  KeyExtra *keyExtra;
  int result;
  _Bool partialMatch = 0;
  do {
    if (!(!isLogicalNodeType(node->type)))
      ExceptionalCondition("!isLogicalNodeType(node->type)", "jsonb_gin_ops.c",
                           987);
  } while (0);
  hash = 0;
  if (!get_query_path_hash(node->path, &hash))
    return -1;
  keyExtra = (KeyExtra *)palloc(sizeof(KeyExtra));
  keyExtra->hash = hash;
  keyExtra->node = node;
  key = make_gin_query_key(node, &partialMatch, hash, keyExtra);
  result = add_entry(e, PointerGetDatum(key), (Pointer)keyExtra, partialMatch);
  return result;
}
Datum gin_compare_jsonb_path_value(FunctionCallInfo fcinfo) {
  GINKey *arg1 = (GINKey *)pg_detoast_datum(
      (struct varlena *)DatumGetPointer((fcinfo->args[0].value)));
  GINKey *arg2 = (GINKey *)pg_detoast_datum(
      (struct varlena *)DatumGetPointer((fcinfo->args[1].value)));
  int32 result = 0;
  if (arg1->hash != arg2->hash) {
    result = (arg1->hash > arg2->hash) ? 1 : -1;
  } else {
    result = compare_gin_key_value(arg1, arg2);
  }
  do {
    if ((Pointer)(arg1) != DatumGetPointer((fcinfo->args[0].value)))
      pfree(arg1);
  } while (0);
  do {
    if ((Pointer)(arg2) != DatumGetPointer((fcinfo->args[1].value)))
      pfree(arg2);
  } while (0);
  return Int32GetDatum(result);
}
Datum gin_compare_partial_jsonb_path_value(FunctionCallInfo fcinfo) {
  GINKey *partial_key = (GINKey *)pg_detoast_datum(
      (struct varlena *)DatumGetPointer((fcinfo->args[0].value)));
  GINKey *key = (GINKey *)pg_detoast_datum(
      (struct varlena *)DatumGetPointer((fcinfo->args[1].value)));
  StrategyNumber strategy = DatumGetUInt16((fcinfo->args[2].value));
  int32 result;
  if (key->hash != partial_key->hash) {
    result = (key->hash > partial_key->hash) ? 1 : -1;
  } else if (strategy == 14) {
    KeyExtra *extra = (KeyExtra *)DatumGetPointer((fcinfo->args[3].value));
    ExtractedNode *node = extra->node;
    switch (node->type) {
    case eInequality:
      result = 0;
      if (!node->bounds.leftInclusive &&
          compare_gin_key_value(key, partial_key) <= 0) {
        result = -1;
      }
      if (result == 0 && extra->rightBound) {
        result = compare_gin_key_value(key, extra->rightBound);
        if ((node->bounds.rightInclusive && result <= 0) || result < 0)
          result = 0;
        else
          result = 1;
      }
      break;
    case eIs:
      if (node->isType == ((key)->type & 0x7F))
        result = 0;
      else
        result = (((key)->type & 0x7F) > node->isType) ? 1 : -1;
      break;
    case eAny:
      result = 0;
      break;
    default:
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          errmsg_internal("Wrong type"),
              errfinish("jsonb_gin_ops.c", 1068, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
      break;
    }
  } else {
    result = compare_gin_key_value(key, partial_key);
  }
  do {
    if ((Pointer)(partial_key) != DatumGetPointer((fcinfo->args[0].value)))
      pfree(partial_key);
  } while (0);
  do {
    if ((Pointer)(key) != DatumGetPointer((fcinfo->args[1].value)))
      pfree(key);
  } while (0);
  return Int32GetDatum(result);
}
static Datum *gin_extract_jsonb_path_value_internal(Jsonb *jb,
                                                    int32 *nentries) {
  int total =
      2 * (*(uint32 *)(((varattrib_4b *)(jb))->va_4byte.va_data) & 0x0FFFFFFF);
  JsonbIterator *it;
  JsonbValue v;
  PathHashStack tail;
  PathHashStack *stack;
  int i = 0, r;
  Datum *entries = ((void *)0);
  if (total == 0) {
    *nentries = 0;
    return ((void *)0);
  }
  entries = (Datum *)palloc(sizeof(Datum) * total);
  it = JsonbIteratorInit(&jb->root);
  tail.parent = ((void *)0);
  tail.hash = 0;
  stack = &tail;
  while ((r = JsonbIteratorNext(&it, &v, 0)) != WJB_DONE) {
    PathHashStack *tmp;
    if (i >= total) {
      total *= 2;
      entries = (Datum *)repalloc(entries, sizeof(Datum) * total);
    }
    if (!stack)
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          errmsg_internal("error jsonb iteration"),
              errfinish("jsonb_gin_ops.c", 1119, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    switch (r) {
    case WJB_BEGIN_ARRAY:
      if (v.val.array.rawScalar)
        break;
      entries[i++] = PointerGetDatum(make_gin_key(&v, stack->hash));
      tmp = stack;
      stack = (PathHashStack *)palloc(sizeof(PathHashStack));
      stack->parent = tmp;
      stack->hash = stack->parent->hash;
      stack->hash = (stack->hash << 1) | (stack->hash >> 31);
      stack->hash ^= 0x40000000;
      break;
    case WJB_BEGIN_OBJECT:
      entries[i++] = PointerGetDatum(make_gin_key(&v, stack->hash));
      tmp = stack;
      stack = (PathHashStack *)palloc(sizeof(PathHashStack));
      stack->parent = tmp;
      stack->hash = stack->parent->hash;
      break;
    case WJB_KEY:
      if (!stack->parent)
        do {
          int __errno_location __attribute__((unused));
          if (__builtin_constant_p(21) && (21) >= 21
                  ? errstart_cold(21, ((void *)0))
                  : errstart(21, ((void *)0)))
            errmsg_internal("error jsonb iteration"),
                errfinish("jsonb_gin_ops.c", 1144, __func__);
          if (__builtin_constant_p(21) && (21) >= 21)
            abort();
        } while (0);
      stack->hash = stack->parent->hash;
      JsonbHashScalarValue(&v, &stack->hash);
      break;
    case WJB_ELEM:
    case WJB_VALUE:
      entries[i++] = PointerGetDatum(make_gin_key(&v, stack->hash));
      break;
    case WJB_END_ARRAY:
      if (!stack->parent)
        break;
    case WJB_END_OBJECT:
      tmp = stack->parent;
      pfree(stack);
      stack = tmp;
      break;
    default:
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          errmsg_internal("invalid JsonbIteratorNext rc: %d", r),
              errfinish("jsonb_gin_ops.c", 1164, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  }
  *nentries = i;
  return entries;
}
Datum gin_extract_jsonb_path_value(FunctionCallInfo fcinfo) {
  Jsonb *jb = DatumGetJsonbP((fcinfo->args[0].value));
  int32 *nentries = (int32 *)DatumGetPointer((fcinfo->args[1].value));
  return PointerGetDatum(gin_extract_jsonb_path_value_internal(jb, nentries));
}
Datum gin_debug_query_path_value(FunctionCallInfo fcinfo) {
  JsQuery *jq;
  Entries e = {0};
  char *s;
  jq = ((JsQuery *)pg_detoast_datum(
      (struct varlena *)DatumGetPointer((fcinfo->args[0].value))));
  s = debugJsQuery(jq, make_path_value_entry_handler,
                   check_path_value_entry_handler, (Pointer)&e);
  return PointerGetDatum(cstring_to_text(s));
}
Datum gin_extract_jsonb_query_path_value(FunctionCallInfo fcinfo) {
  Jsonb *jb;
  int32 *nentries = (int32 *)DatumGetPointer((fcinfo->args[1].value));
  StrategyNumber strategy = DatumGetUInt16((fcinfo->args[2].value));
  _Bool **pmatch = (_Bool **)DatumGetPointer((fcinfo->args[3].value));
  Pointer **extra_data = (Pointer **)DatumGetPointer((fcinfo->args[4].value));
  int32 *searchMode = (int32 *)DatumGetPointer((fcinfo->args[6].value));
  Datum *entries = ((void *)0);
  int i;
  Entries e = {0};
  JsQuery *jq;
  ExtractedNode *root;
  switch (strategy) {
  case 7:
    jb = DatumGetJsonbP((fcinfo->args[0].value));
    entries = gin_extract_jsonb_path_value_internal(jb, nentries);
    break;
  case 14:
    jq = ((JsQuery *)pg_detoast_datum(
        (struct varlena *)DatumGetPointer((fcinfo->args[0].value))));
    root = extractJsQuery(jq, make_path_value_entry_handler,
                          check_path_value_entry_handler, (Pointer)&e);
    if (root) {
      *nentries = e.count;
      entries = e.entries;
      *pmatch = e.partial_match;
      *extra_data = e.extra_data;
      for (i = 0; i < e.count; i++)
        ((KeyExtra *)e.extra_data[i])->root = root;
    } else {
      entries = ((void *)0);
      *nentries = 0;
    }
    break;
  default:
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("unrecognized strategy number: %d", strategy),
            errfinish("jsonb_gin_ops.c", 1239, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
    break;
  }
  if (entries == ((void *)0))
    *searchMode = 2;
  return PointerGetDatum(entries);
}
Datum gin_consistent_jsonb_path_value(FunctionCallInfo fcinfo) {
  _Bool *check = (_Bool *)DatumGetPointer((fcinfo->args[0].value));
  StrategyNumber strategy = DatumGetUInt16((fcinfo->args[1].value));
  int32 nkeys = DatumGetInt32((fcinfo->args[3].value));
  Pointer *extra_data = (Pointer *)DatumGetPointer((fcinfo->args[4].value));
  _Bool *recheck = (_Bool *)DatumGetPointer((fcinfo->args[5].value));
  _Bool res = 1;
  int32 i;
  *recheck = 1;
  switch (strategy) {
  case 7:
    for (i = 0; i < nkeys; i++) {
      if (!check[i]) {
        res = 0;
        break;
      }
    }
    break;
  case 14:
    if (nkeys == 0)
      res = 1;
    else
      res = execRecursive(((KeyExtra *)extra_data[0])->root, check);
    break;
  default:
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("unrecognized strategy number: %d", strategy),
            errfinish("jsonb_gin_ops.c", 1284, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
    break;
  }
  return BoolGetDatum(res);
}
Datum gin_triconsistent_jsonb_path_value(FunctionCallInfo fcinfo) {
  GinTernaryValue *check =
      (GinTernaryValue *)DatumGetPointer((fcinfo->args[0].value));
  StrategyNumber strategy = DatumGetUInt16((fcinfo->args[1].value));
  int32 nkeys = DatumGetInt32((fcinfo->args[3].value));
  Pointer *extra_data = (Pointer *)DatumGetPointer((fcinfo->args[4].value));
  GinTernaryValue res = 1;
  int32 i;
  _Bool has_maybe = 0;
  switch (strategy) {
  case 7:
    for (i = 0; i < nkeys; i++) {
      if (check[i] == 0) {
        res = 0;
        break;
      }
      if (check[i] == 2) {
        res = 2;
        has_maybe = 1;
      }
    }
    if (!has_maybe && res == 1)
      res = 2;
    break;
  case 14:
    if (nkeys == 0)
      res = 2;
    else
      res = execRecursiveTristate(((KeyExtra *)extra_data[0])->root, check);
    if (res == 1)
      res = 2;
    break;
  default:
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("unrecognized strategy number: %d", strategy),
            errfinish("jsonb_gin_ops.c", 1349, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
    break;
  }
  return GinTernaryValueGetDatum(res);
}
