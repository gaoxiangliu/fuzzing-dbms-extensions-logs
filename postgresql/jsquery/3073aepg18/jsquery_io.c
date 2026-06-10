#include "postgres.h"
#include "miscadmin.h"
#include "utils/builtins.h"
#include "utils/json.h"
#include "jsquery.h"
extern __attribute__((visibility("default"))) const Pg_magic_struct *
Pg_magic_func(void);
const Pg_magic_struct *Pg_magic_func(void) {
  static const Pg_magic_struct Pg_magic_data = {.len = sizeof(Pg_magic_struct),
                                                .abi_fields =
                                                    {
                                                        180000 / 100,
                                                        100,
                                                        32,
                                                        64,
                                                        1,
                                                        "PostgreSQL",
                                                    },
                                                .name = ((void *)0)};
  return &Pg_magic_data;
}
extern int no_such_variable;
static int flattenJsQueryParseItem(StringInfo buf, JsQueryParseItem *item,
                                   _Bool onlyCurrentInPath) {
  int32 pos = buf->len - ((int32)sizeof(int32));
  int32 chld, next;
  check_stack_depth();
  do {
    if (!((item->type & item->hint) == 0))
      ExceptionalCondition("(item->type & item->hint) == 0", "jsquery_io.c",
                           34);
  } while (0);
  do {
    if (!((item->type & (jsqIndexDefault | jsqForceIndex | jsqNoIndex)) == 0))
      ExceptionalCondition("(item->type & JSQ_HINT_MASK) == 0", "jsquery_io.c",
                           35);
  } while (0);
  appendStringInfoChar(buf, (char)(item->type | item->hint));
  alignStringInfoInt(buf);
  next = (item->next) ? buf->len : 0;
  appendBinaryStringInfo(buf, (char *)&next, sizeof(next));
  switch (item->type) {
  case jqiKey:
    if (onlyCurrentInPath)
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          errmsg_internal("Array length should be last in path"),
              errfinish("jsquery_io.c", 47, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
  case jqiString:
    appendBinaryStringInfo(buf, (char *)&item->string.len,
                           sizeof(item->string.len));
    appendBinaryStringInfo(buf, item->string.val, item->string.len);
    appendStringInfoChar(buf, '\0');
    break;
  case jqiNumeric:
    appendBinaryStringInfo(
        buf, (char *)item->numeric,
        ((((varattrib_4b *)(item->numeric))->va_4byte.va_header >> 2) &
         0x3FFFFFFF));
    break;
  case jqiBool:
    appendBinaryStringInfo(buf, (char *)&item->boolean, sizeof(item->boolean));
    break;
  case jqiIs:
    appendBinaryStringInfo(buf, (char *)&item->isType, sizeof(item->isType));
    break;
  case jqiArray: {
    int32 i, arrayStart;
    appendBinaryStringInfo(buf, (char *)&item->array.nelems,
                           sizeof(item->array.nelems));
    arrayStart = buf->len;
    for (i = 0; i < item->array.nelems; i++)
      appendBinaryStringInfo(buf, (char *)&i, sizeof(i));
    for (i = 0; i < item->array.nelems; i++) {
      chld =
          flattenJsQueryParseItem(buf, item->array.elems[i], onlyCurrentInPath);
      *(int32 *)(buf->data + arrayStart + i * sizeof(i)) = chld;
    }
  } break;
  case jqiAnd:
  case jqiOr: {
    int32 left, right;
    left = buf->len;
    appendBinaryStringInfo(buf, (char *)&left, sizeof(left));
    right = buf->len;
    appendBinaryStringInfo(buf, (char *)&right, sizeof(right));
    chld = flattenJsQueryParseItem(buf, item->args.left, onlyCurrentInPath);
    *(int32 *)(buf->data + left) = chld;
    chld = flattenJsQueryParseItem(buf, item->args.right, onlyCurrentInPath);
    *(int32 *)(buf->data + right) = chld;
  } break;
  case jqiEqual:
  case jqiIn:
  case jqiLess:
  case jqiGreater:
  case jqiLessOrEqual:
  case jqiGreaterOrEqual:
  case jqiContains:
  case jqiContained:
  case jqiOverlap:
  case jqiNot:
  case jqiFilter: {
    int32 arg;
    arg = buf->len;
    appendBinaryStringInfo(buf, (char *)&arg, sizeof(arg));
    chld = flattenJsQueryParseItem(buf, item->arg, onlyCurrentInPath);
    *(int32 *)(buf->data + arg) = chld;
  } break;
  case jqiIndexArray:
    appendBinaryStringInfo(buf, (char *)&item->arrayIndex,
                           sizeof(item->arrayIndex));
  case jqiAny:
  case jqiAnyArray:
  case jqiAnyKey:
  case jqiAll:
  case jqiAllArray:
  case jqiAllKey:
    if (onlyCurrentInPath)
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          errmsg_internal("Array length should be last in path"),
              errfinish("jsquery_io.c", 130, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
  case jqiCurrent:
  case jqiNull:
    break;
  case jqiLength:
    onlyCurrentInPath = 1;
    break;
  default:
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("Unknown type: %d", item->type),
            errfinish("jsquery_io.c", 138, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
  }
  if (item->next) {
    chld = flattenJsQueryParseItem(buf, item->next, onlyCurrentInPath);
    *(int32 *)(buf->data + next) = chld;
  }
  return pos;
}
extern __attribute__((visibility("default"))) Datum
jsquery_in(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_jsquery_in(void);
const Pg_finfo_record *pg_finfo_jsquery_in(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum jsquery_in(FunctionCallInfo fcinfo) {
  char *in = DatumGetCString((fcinfo->args[0].value));
  int32 len = strlen(in);
  JsQueryParseItem *jsquery = parsejsquery(in, len);
  JsQuery *res;
  StringInfoData buf;
  initStringInfo(&buf);
  enlargeStringInfo(&buf, 4 * len);
  appendStringInfoSpaces(&buf, ((int32)sizeof(int32)));
  flattenJsQueryParseItem(&buf, jsquery, 0);
  res = (JsQuery *)buf.data;
  (((varattrib_4b *)(res))->va_4byte.va_header = (((uint32)(buf.len)) << 2));
  return PointerGetDatum(res);
}
static void printHint(StringInfo buf, JsQueryHint hint) {
  switch (hint) {
  case jsqForceIndex:
    appendStringInfoString(buf, " /*-- index */ ");
    break;
  case jsqNoIndex:
    appendStringInfoString(buf, " /*-- noindex */ ");
    break;
  case jsqIndexDefault:
    break;
  default:
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("Unknown hint: %d", hint),
            errfinish("jsquery_io.c", 187, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
  }
}
static void printOperation(StringInfo buf, JsQueryItemType type) {
  switch (type) {
  case jqiAnd:
    appendBinaryStringInfo(buf, " AND ", 5);
    break;
  case jqiOr:
    appendBinaryStringInfo(buf, " OR ", 4);
    break;
  case jqiEqual:
    appendBinaryStringInfo(buf, " = ", 3);
    break;
  case jqiLess:
    appendBinaryStringInfo(buf, " < ", 3);
    break;
  case jqiGreater:
    appendBinaryStringInfo(buf, " > ", 3);
    break;
  case jqiLessOrEqual:
    appendBinaryStringInfo(buf, " <= ", 4);
    break;
  case jqiGreaterOrEqual:
    appendBinaryStringInfo(buf, " >= ", 4);
    break;
  case jqiContains:
    appendBinaryStringInfo(buf, " @> ", 4);
    break;
  case jqiContained:
    appendBinaryStringInfo(buf, " <@ ", 4);
    break;
  case jqiOverlap:
    appendBinaryStringInfo(buf, " && ", 4);
    break;
  default:
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("Unknown type: %d", type),
            errfinish("jsquery_io.c", 217, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
  }
}
static void printJsQueryItem(StringInfo buf, JsQueryItem *v, _Bool inKey,
                             _Bool printBracketes) {
  JsQueryItem elem;
  _Bool first = 1;
  check_stack_depth();
  printHint(buf, v->hint);
  switch (v->type) {
  case jqiNull:
    appendStringInfoString(buf, "null");
    break;
  case jqiKey:
    if (inKey)
      appendStringInfoChar(buf, '.');
  case jqiString:
    escape_json(buf, jsqGetString(v, ((void *)0)));
    break;
  case jqiNumeric:
    appendStringInfoString(
        buf, DatumGetCString(DirectFunctionCall1Coll(
                 numeric_out, ((Oid)0), PointerGetDatum(jsqGetNumeric(v)))));
    break;
  case jqiBool:
    if (jsqGetBool(v))
      appendBinaryStringInfo(buf, "true", 4);
    else
      appendBinaryStringInfo(buf, "false", 5);
    break;
  case jqiIs:
    appendBinaryStringInfo(buf, " IS ", 4);
    switch (jsqGetIsType(v)) {
    case jbvString:
      appendBinaryStringInfo(buf, "STRING", 6);
      break;
    case jbvNumeric:
      appendBinaryStringInfo(buf, "NUMERIC", 7);
      break;
    case jbvBool:
      appendBinaryStringInfo(buf, "BOOLEAN", 7);
      break;
    case jbvArray:
      appendBinaryStringInfo(buf, "ARRAY", 5);
      break;
    case jbvObject:
      appendBinaryStringInfo(buf, "OBJECT", 6);
      break;
    default:
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          errmsg_internal("Unknown type for IS: %d", jsqGetIsType(v)),
              errfinish("jsquery_io.c", 275, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
      break;
    }
    break;
  case jqiArray:
    if (printBracketes)
      appendStringInfoChar(buf, '[');
    while (jsqIterateArray(v, &elem)) {
      if (first == 0)
        appendBinaryStringInfo(buf, ", ", 2);
      else
        first = 0;
      printJsQueryItem(buf, &elem, 0, 1);
    }
    if (printBracketes)
      appendStringInfoChar(buf, ']');
    break;
  case jqiAnd:
  case jqiOr:
    appendStringInfoChar(buf, '(');
    jsqGetLeftArg(v, &elem);
    printJsQueryItem(buf, &elem, 0, 1);
    printOperation(buf, v->type);
    jsqGetRightArg(v, &elem);
    printJsQueryItem(buf, &elem, 0, 1);
    appendStringInfoChar(buf, ')');
    break;
  case jqiEqual:
  case jqiLess:
  case jqiGreater:
  case jqiLessOrEqual:
  case jqiGreaterOrEqual:
  case jqiContains:
  case jqiContained:
  case jqiOverlap:
    printOperation(buf, v->type);
    jsqGetArg(v, &elem);
    printJsQueryItem(buf, &elem, 0, 1);
    break;
  case jqiIn:
    appendBinaryStringInfo(buf, " IN (", 5);
    jsqGetArg(v, &elem);
    printJsQueryItem(buf, &elem, 0, 0);
    appendStringInfoChar(buf, ')');
    break;
  case jqiNot:
    appendStringInfoChar(buf, '(');
    appendBinaryStringInfo(buf, "NOT ", 4);
    jsqGetArg(v, &elem);
    printJsQueryItem(buf, &elem, 0, 1);
    appendStringInfoChar(buf, ')');
    break;
  case jqiCurrent:
    if (inKey)
      appendStringInfoChar(buf, '.');
    appendStringInfoChar(buf, '$');
    break;
  case jqiLength:
    if (inKey)
      appendStringInfoChar(buf, '.');
    appendStringInfoChar(buf, '@');
    appendStringInfoChar(buf, '#');
    break;
  case jqiAny:
    if (inKey)
      appendStringInfoChar(buf, '.');
    appendStringInfoChar(buf, '*');
    break;
  case jqiAnyArray:
    if (inKey)
      appendStringInfoChar(buf, '.');
    appendStringInfoChar(buf, '#');
    break;
  case jqiAnyKey:
    if (inKey)
      appendStringInfoChar(buf, '.');
    appendStringInfoChar(buf, '%');
    break;
  case jqiAll:
    if (inKey)
      appendStringInfoChar(buf, '.');
    appendStringInfoChar(buf, '*');
    appendStringInfoChar(buf, ':');
    break;
  case jqiAllArray:
    if (inKey)
      appendStringInfoChar(buf, '.');
    appendStringInfoChar(buf, '#');
    appendStringInfoChar(buf, ':');
    break;
  case jqiAllKey:
    if (inKey)
      appendStringInfoChar(buf, '.');
    appendStringInfoChar(buf, '%');
    appendStringInfoChar(buf, ':');
    break;
  case jqiIndexArray:
    if (inKey)
      appendStringInfoChar(buf, '.');
    appendStringInfo(buf, "#%u", v->arrayIndex);
    break;
  case jqiFilter:
    if (inKey)
      appendStringInfoChar(buf, '.');
    appendBinaryStringInfo(buf, " ?(", 3);
    jsqGetArg(v, &elem);
    printJsQueryItem(buf, &elem, 0, 0);
    appendBinaryStringInfo(buf, ") ", 2);
    break;
  default:
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("Unknown JsQueryItem type: %d", v->type),
            errfinish("jsquery_io.c", 388, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
  }
  if (jsqGetNext(v, &elem))
    printJsQueryItem(buf, &elem, 1, 1);
}
extern __attribute__((visibility("default"))) Datum
jsquery_out(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_jsquery_out(void);
const Pg_finfo_record *pg_finfo_jsquery_out(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum jsquery_out(FunctionCallInfo fcinfo) {
  JsQuery *in = ((JsQuery *)pg_detoast_datum(
      (struct varlena *)DatumGetPointer((fcinfo->args[0].value))));
  StringInfoData buf;
  JsQueryItem v;
  initStringInfo(&buf);
  enlargeStringInfo(
      &buf, ((((varattrib_4b *)(in))->va_4byte.va_header >> 2) & 0x3FFFFFFF));
  jsqInit(&v, in);
  printJsQueryItem(&buf, &v, 0, 1);
  return CStringGetDatum(buf.data);
}
