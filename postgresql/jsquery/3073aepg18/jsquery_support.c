#include "postgres.h"
#include "jsquery.h"
void alignStringInfoInt(StringInfo buf) {
  switch ((((uintptr_t)((buf->len)) + ((4) - 1)) & ~((uintptr_t)((4) - 1))) -
          buf->len) {
  case 3:
    (((buf)->len + 1 >= (buf)->maxlen)
         ? appendStringInfoChar(buf, 0)
         : (void)((buf)->data[(buf)->len] = (0),
                  (buf)->data[++(buf)->len] = '\0'));
  case 2:
    (((buf)->len + 1 >= (buf)->maxlen)
         ? appendStringInfoChar(buf, 0)
         : (void)((buf)->data[(buf)->len] = (0),
                  (buf)->data[++(buf)->len] = '\0'));
  case 1:
    (((buf)->len + 1 >= (buf)->maxlen)
         ? appendStringInfoChar(buf, 0)
         : (void)((buf)->data[(buf)->len] = (0),
                  (buf)->data[++(buf)->len] = '\0'));
  default:
    break;
  }
}
void jsqInit(JsQueryItem *v, JsQuery *js) {
  jsqInitByBuffer(v, (((varattrib_4b *)(js))->va_4byte.va_data), 0);
}
void jsqInitByBuffer(JsQueryItem *v, char *base, int32 pos) {
  v->base = base;
  do {
    (v->type) = *(uint8 *)((base) + (pos));
    (pos) += 1;
  } while (0);
  v->hint = v->type & (jsqIndexDefault | jsqForceIndex | jsqNoIndex);
  v->type &= ~(jsqIndexDefault | jsqForceIndex | jsqNoIndex);
  switch ((((uintptr_t)((pos)) + ((4) - 1)) & ~((uintptr_t)((4) - 1))) - pos) {
  case 3:
    pos++;
  case 2:
    pos++;
  case 1:
    pos++;
  default:
    break;
  }
  do {
    (v->nextPos) = *(uint32 *)((base) + (pos));
    (pos) += sizeof(int32);
  } while (0);
  switch (v->type) {
  case jqiNull:
  case jqiCurrent:
  case jqiLength:
  case jqiAny:
  case jqiAnyArray:
  case jqiAnyKey:
  case jqiAll:
  case jqiAllArray:
  case jqiAllKey:
    break;
  case jqiIndexArray:
    do {
      (v->arrayIndex) = *(uint32 *)((base) + (pos));
      (pos) += sizeof(int32);
    } while (0);
    break;
  case jqiKey:
  case jqiString:
    do {
      (v->value.datalen) = *(uint32 *)((base) + (pos));
      (pos) += sizeof(int32);
    } while (0);
  case jqiNumeric:
  case jqiBool:
  case jqiIs:
    v->value.data = base + pos;
    break;
  case jqiArray:
    do {
      (v->array.nelems) = *(uint32 *)((base) + (pos));
      (pos) += sizeof(int32);
    } while (0);
    v->array.current = 0;
    v->array.arrayPtr = (int32 *)(base + pos);
    break;
  case jqiAnd:
  case jqiOr:
    do {
      (v->args.left) = *(uint32 *)((base) + (pos));
      (pos) += sizeof(int32);
    } while (0);
    do {
      (v->args.right) = *(uint32 *)((base) + (pos));
      (pos) += sizeof(int32);
    } while (0);
    break;
  case jqiEqual:
  case jqiLess:
  case jqiGreater:
  case jqiLessOrEqual:
  case jqiGreaterOrEqual:
  case jqiContains:
  case jqiContained:
  case jqiOverlap:
  case jqiIn:
  case jqiNot:
  case jqiFilter:
    do {
      (v->arg) = *(uint32 *)((base) + (pos));
      (pos) += sizeof(int32);
    } while (0);
    break;
  default:
    abort();
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("Unknown type: %d", v->type),
            errfinish("jsquery_support.c", 125, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
  }
}
void jsqGetArg(JsQueryItem *v, JsQueryItem *a) {
  do {
    if (!(v->type == jqiEqual || v->type == jqiLess || v->type == jqiGreater ||
          v->type == jqiLessOrEqual || v->type == jqiGreaterOrEqual ||
          v->type == jqiContains || v->type == jqiContained ||
          v->type == jqiOverlap || v->type == jqiFilter || v->type == jqiIn ||
          v->type == jqiNot))
      ExceptionalCondition(
          "v->type == jqiEqual || v->type == jqiLess || v->type == jqiGreater "
          "|| v->type == jqiLessOrEqual || v->type == jqiGreaterOrEqual || "
          "v->type == jqiContains || v->type == jqiContained || v->type == "
          "jqiOverlap || v->type == jqiFilter || v->type == jqiIn || v->type "
          "== jqiNot",
          "jsquery_support.c", 144);
  } while (0);
  jsqInitByBuffer(a, v->base, v->arg);
}
_Bool jsqGetNext(JsQueryItem *v, JsQueryItem *a) {
  if (v->nextPos > 0) {
    do {
      if (!(v->type == jqiKey || v->type == jqiAny ||
            v->type == jqiIndexArray || v->type == jqiAnyArray ||
            v->type == jqiAnyKey || v->type == jqiAll ||
            v->type == jqiAllArray || v->type == jqiAllKey ||
            v->type == jqiCurrent || v->type == jqiFilter ||
            v->type == jqiLength))
        ExceptionalCondition(
            "v->type == jqiKey || v->type == jqiAny || v->type == "
            "jqiIndexArray || v->type == jqiAnyArray || v->type == jqiAnyKey "
            "|| v->type == jqiAll || v->type == jqiAllArray || v->type == "
            "jqiAllKey || v->type == jqiCurrent || v->type == jqiFilter || "
            "v->type == jqiLength",
            "jsquery_support.c", 166);
    } while (0);
    if (a)
      jsqInitByBuffer(a, v->base, v->nextPos);
    return 1;
  }
  return 0;
}
void jsqGetLeftArg(JsQueryItem *v, JsQueryItem *a) {
  do {
    if (!(v->type == jqiAnd || v->type == jqiOr))
      ExceptionalCondition("v->type == jqiAnd || v->type == jqiOr",
                           "jsquery_support.c", 182);
  } while (0);
  jsqInitByBuffer(a, v->base, v->args.left);
}
void jsqGetRightArg(JsQueryItem *v, JsQueryItem *a) {
  do {
    if (!(v->type == jqiAnd || v->type == jqiOr))
      ExceptionalCondition("v->type == jqiAnd || v->type == jqiOr",
                           "jsquery_support.c", 193);
  } while (0);
  jsqInitByBuffer(a, v->base, v->args.right);
}
_Bool jsqGetBool(JsQueryItem *v) {
  do {
    if (!(v->type == jqiBool))
      ExceptionalCondition("v->type == jqiBool", "jsquery_support.c", 201);
  } while (0);
  return (_Bool)*v->value.data;
}
Numeric jsqGetNumeric(JsQueryItem *v) {
  do {
    if (!(v->type == jqiNumeric))
      ExceptionalCondition("v->type == jqiNumeric", "jsquery_support.c", 209);
  } while (0);
  return (Numeric)v->value.data;
}
int32 jsqGetIsType(JsQueryItem *v) {
  do {
    if (!(v->type == jqiIs))
      ExceptionalCondition("v->type == jqiIs", "jsquery_support.c", 217);
  } while (0);
  return (int32)*v->value.data;
}
char *jsqGetString(JsQueryItem *v, int32 *len) {
  do {
    if (!(v->type == jqiKey || v->type == jqiString))
      ExceptionalCondition("v->type == jqiKey || v->type == jqiString",
                           "jsquery_support.c", 228);
  } while (0);
  if (len)
    *len = v->value.datalen;
  return v->value.data;
}
void jsqIterateInit(JsQueryItem *v) {
  do {
    if (!(v->type == jqiArray))
      ExceptionalCondition("v->type == jqiArray", "jsquery_support.c", 238);
  } while (0);
  v->array.current = 0;
}
_Bool jsqIterateArray(JsQueryItem *v, JsQueryItem *e) {
  do {
    if (!(v->type == jqiArray))
      ExceptionalCondition("v->type == jqiArray", "jsquery_support.c", 246);
  } while (0);
  if (v->array.current < v->array.nelems) {
    jsqInitByBuffer(e, v->base, v->array.arrayPtr[v->array.current]);
    v->array.current++;
    return 1;
  } else {
    return 0;
  }
}
void jsqIterateDestroy(JsQueryItem *v) {
  do {
    if (!(v->type == jqiArray))
      ExceptionalCondition("v->type == jqiArray", "jsquery_support.c", 263);
  } while (0);
  do {
    if (!(v->array.current <= v->array.nelems))
      ExceptionalCondition("v->array.current <= v->array.nelems",
                           "jsquery_support.c", 264);
  } while (0);
  v->array.current++;
}
