#include "pmpz.h"
#include "pgmp-impl.h"
#include "fmgr.h"
#include "funcapi.h"
#include "access/hash.h"      /* for hash_any */
#include <utils/fmgrprotos.h> /* for hashint8 */
extern __attribute__((visibility("default"))) Datum
pmpz_uplus(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_uplus(void);
const Pg_finfo_record *pg_finfo_pmpz_uplus(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_uplus(FunctionCallInfo fcinfo);
Datum pmpz_uplus(FunctionCallInfo fcinfo) {
  const pmpz *pz1;
  pmpz *res;
  pz1 = ((pmpz *)(pg_detoast_datum(
      (struct varlena *)DatumGetPointer((fcinfo->args[0].value)))));
  res = (pmpz *)palloc(
      ((((varattrib_4b *)(pz1))->va_4byte.va_header >> 2) & 0x3FFFFFFF));
  memcpy(res, pz1,
         ((((varattrib_4b *)(pz1))->va_4byte.va_header >> 2) & 0x3FFFFFFF));
  return PointerGetDatum(res);
}
extern __attribute__((visibility("default"))) Datum
pmpz_neg(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_neg(void);
const Pg_finfo_record *pg_finfo_pmpz_neg(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_neg(FunctionCallInfo fcinfo);
Datum pmpz_neg(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  ;
  __gmpz_init(zf);
  __gmpz_neg(zf, z1);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_abs(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_abs(void);
const Pg_finfo_record *pg_finfo_pmpz_abs(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_abs(FunctionCallInfo fcinfo);
Datum pmpz_abs(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  ;
  __gmpz_init(zf);
  __gmpz_abs(zf, z1);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_sqrt(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_sqrt(void);
const Pg_finfo_record *pg_finfo_pmpz_sqrt(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_sqrt(FunctionCallInfo fcinfo);
Datum pmpz_sqrt(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  do {
    if (__builtin_expect((((z1)->_mp_size) < 0) != 0, 0)) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument can't be negative")),
              errfinish("src/pmpz_arith.c", 72, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  } while (0);
  __gmpz_init(zf);
  __gmpz_sqrt(zf, z1);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_com(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_com(void);
const Pg_finfo_record *pg_finfo_pmpz_com(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_com(FunctionCallInfo fcinfo);
Datum pmpz_com(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  ;
  __gmpz_init(zf);
  __gmpz_com(zf, z1);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_add(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_add(void);
const Pg_finfo_record *pg_finfo_pmpz_add(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_add(FunctionCallInfo fcinfo);
Datum pmpz_add(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  ;
  __gmpz_init(zf);
  __gmpz_add(zf, z1, z2);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_sub(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_sub(void);
const Pg_finfo_record *pg_finfo_pmpz_sub(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_sub(FunctionCallInfo fcinfo);
Datum pmpz_sub(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  ;
  __gmpz_init(zf);
  __gmpz_sub(zf, z1, z2);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_mul(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_mul(void);
const Pg_finfo_record *pg_finfo_pmpz_mul(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_mul(FunctionCallInfo fcinfo);
Datum pmpz_mul(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  ;
  __gmpz_init(zf);
  __gmpz_mul(zf, z1, z2);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_tdiv_q(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_tdiv_q(void);
const Pg_finfo_record *pg_finfo_pmpz_tdiv_q(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_tdiv_q(FunctionCallInfo fcinfo);
Datum pmpz_tdiv_q(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  do {
    if (__builtin_expect(((((z2)->_mp_size) == 0)) != 0, 0)) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('1') - '0') & 0x3F) << 18) +
                    (((('2') - '0') & 0x3F) << 24))),
           errmsg("division by zero")),
              errfinish("src/pmpz_arith.c", 106, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  } while (0);
  __gmpz_init(zf);
  __gmpz_tdiv_q(zf, z1, z2);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_tdiv_r(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_tdiv_r(void);
const Pg_finfo_record *pg_finfo_pmpz_tdiv_r(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_tdiv_r(FunctionCallInfo fcinfo);
Datum pmpz_tdiv_r(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  do {
    if (__builtin_expect(((((z2)->_mp_size) == 0)) != 0, 0)) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('1') - '0') & 0x3F) << 18) +
                    (((('2') - '0') & 0x3F) << 24))),
           errmsg("division by zero")),
              errfinish("src/pmpz_arith.c", 107, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  } while (0);
  __gmpz_init(zf);
  __gmpz_tdiv_r(zf, z1, z2);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_cdiv_q(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_cdiv_q(void);
const Pg_finfo_record *pg_finfo_pmpz_cdiv_q(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_cdiv_q(FunctionCallInfo fcinfo);
Datum pmpz_cdiv_q(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  do {
    if (__builtin_expect(((((z2)->_mp_size) == 0)) != 0, 0)) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('1') - '0') & 0x3F) << 18) +
                    (((('2') - '0') & 0x3F) << 24))),
           errmsg("division by zero")),
              errfinish("src/pmpz_arith.c", 108, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  } while (0);
  __gmpz_init(zf);
  __gmpz_cdiv_q(zf, z1, z2);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_cdiv_r(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_cdiv_r(void);
const Pg_finfo_record *pg_finfo_pmpz_cdiv_r(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_cdiv_r(FunctionCallInfo fcinfo);
Datum pmpz_cdiv_r(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  do {
    if (__builtin_expect(((((z2)->_mp_size) == 0)) != 0, 0)) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('1') - '0') & 0x3F) << 18) +
                    (((('2') - '0') & 0x3F) << 24))),
           errmsg("division by zero")),
              errfinish("src/pmpz_arith.c", 109, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  } while (0);
  __gmpz_init(zf);
  __gmpz_cdiv_r(zf, z1, z2);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_fdiv_q(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_fdiv_q(void);
const Pg_finfo_record *pg_finfo_pmpz_fdiv_q(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_fdiv_q(FunctionCallInfo fcinfo);
Datum pmpz_fdiv_q(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  do {
    if (__builtin_expect(((((z2)->_mp_size) == 0)) != 0, 0)) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('1') - '0') & 0x3F) << 18) +
                    (((('2') - '0') & 0x3F) << 24))),
           errmsg("division by zero")),
              errfinish("src/pmpz_arith.c", 110, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  } while (0);
  __gmpz_init(zf);
  __gmpz_fdiv_q(zf, z1, z2);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_fdiv_r(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_fdiv_r(void);
const Pg_finfo_record *pg_finfo_pmpz_fdiv_r(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_fdiv_r(FunctionCallInfo fcinfo);
Datum pmpz_fdiv_r(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  do {
    if (__builtin_expect(((((z2)->_mp_size) == 0)) != 0, 0)) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('1') - '0') & 0x3F) << 18) +
                    (((('2') - '0') & 0x3F) << 24))),
           errmsg("division by zero")),
              errfinish("src/pmpz_arith.c", 111, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  } while (0);
  __gmpz_init(zf);
  __gmpz_fdiv_r(zf, z1, z2);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_divexact(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_divexact(void);
const Pg_finfo_record *pg_finfo_pmpz_divexact(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_divexact(FunctionCallInfo fcinfo);
Datum pmpz_divexact(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  do {
    if (__builtin_expect(((((z2)->_mp_size) == 0)) != 0, 0)) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('1') - '0') & 0x3F) << 18) +
                    (((('2') - '0') & 0x3F) << 24))),
           errmsg("division by zero")),
              errfinish("src/pmpz_arith.c", 112, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  } while (0);
  __gmpz_init(zf);
  __gmpz_divexact(zf, z1, z2);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_and(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_and(void);
const Pg_finfo_record *pg_finfo_pmpz_and(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_and(FunctionCallInfo fcinfo);
Datum pmpz_and(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  ;
  __gmpz_init(zf);
  __gmpz_and(zf, z1, z2);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_ior(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_ior(void);
const Pg_finfo_record *pg_finfo_pmpz_ior(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_ior(FunctionCallInfo fcinfo);
Datum pmpz_ior(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  ;
  __gmpz_init(zf);
  __gmpz_ior(zf, z1, z2);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_xor(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_xor(void);
const Pg_finfo_record *pg_finfo_pmpz_xor(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_xor(FunctionCallInfo fcinfo);
Datum pmpz_xor(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  ;
  __gmpz_init(zf);
  __gmpz_xor(zf, z1, z2);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_gcd(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_gcd(void);
const Pg_finfo_record *pg_finfo_pmpz_gcd(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_gcd(FunctionCallInfo fcinfo);
Datum pmpz_gcd(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  ;
  __gmpz_init(zf);
  __gmpz_gcd(zf, z1, z2);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_lcm(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_lcm(void);
const Pg_finfo_record *pg_finfo_pmpz_lcm(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_lcm(FunctionCallInfo fcinfo);
Datum pmpz_lcm(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  ;
  __gmpz_init(zf);
  __gmpz_lcm(zf, z1, z2);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_remove(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_remove(void);
const Pg_finfo_record *pg_finfo_pmpz_remove(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_remove(FunctionCallInfo fcinfo);
Datum pmpz_remove(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  ;
  __gmpz_init(zf);
  __gmpz_remove(zf, z1, z2);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_tdiv_qr(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_tdiv_qr(void);
const Pg_finfo_record *pg_finfo_pmpz_tdiv_qr(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_tdiv_qr(FunctionCallInfo fcinfo);
Datum pmpz_tdiv_qr(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf1;
  mpz_t zf2;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  do {
    if (__builtin_expect(((((z2)->_mp_size) == 0)) != 0, 0)) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('1') - '0') & 0x3F) << 18) +
                    (((('2') - '0') & 0x3F) << 24))),
           errmsg("division by zero")),
              errfinish("src/pmpz_arith.c", 143, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  } while (0);
  __gmpz_init(zf1);
  __gmpz_init(zf2);
  __gmpz_tdiv_qr(zf1, zf2, z1, z2);
  do {
    TupleDesc _tupdesc;
    Datum _result[2];
    _Bool _isnull[2] = {0, 0};
    if (get_call_result_type(fcinfo, ((void *)0), &_tupdesc) !=
        TYPEFUNC_COMPOSITE)
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('0') - '0') & 0x3F) + (((('A') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('0') - '0') & 0x3F) << 18) +
                    (((('0') - '0') & 0x3F) << 24))),
           errmsg("function returning composite called in context "
                  "that cannot accept type composite")),
              errfinish("src/pmpz_arith.c", 143, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    _tupdesc = BlessTupleDesc(_tupdesc);
    _result[0] = (Datum)pmpz_from_mpz(zf1);
    _result[1] = (Datum)pmpz_from_mpz(zf2);
    return HeapTupleGetDatum(heap_form_tuple(_tupdesc, _result, _isnull));
  } while (0);
}
extern __attribute__((visibility("default"))) Datum
pmpz_cdiv_qr(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_cdiv_qr(void);
const Pg_finfo_record *pg_finfo_pmpz_cdiv_qr(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_cdiv_qr(FunctionCallInfo fcinfo);
Datum pmpz_cdiv_qr(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf1;
  mpz_t zf2;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  do {
    if (__builtin_expect(((((z2)->_mp_size) == 0)) != 0, 0)) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('1') - '0') & 0x3F) << 18) +
                    (((('2') - '0') & 0x3F) << 24))),
           errmsg("division by zero")),
              errfinish("src/pmpz_arith.c", 144, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  } while (0);
  __gmpz_init(zf1);
  __gmpz_init(zf2);
  __gmpz_cdiv_qr(zf1, zf2, z1, z2);
  do {
    TupleDesc _tupdesc;
    Datum _result[2];
    _Bool _isnull[2] = {0, 0};
    if (get_call_result_type(fcinfo, ((void *)0), &_tupdesc) !=
        TYPEFUNC_COMPOSITE)
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('0') - '0') & 0x3F) + (((('A') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('0') - '0') & 0x3F) << 18) +
                    (((('0') - '0') & 0x3F) << 24))),
           errmsg("function returning composite called in context "
                  "that cannot accept type composite")),
              errfinish("src/pmpz_arith.c", 144, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    _tupdesc = BlessTupleDesc(_tupdesc);
    _result[0] = (Datum)pmpz_from_mpz(zf1);
    _result[1] = (Datum)pmpz_from_mpz(zf2);
    return HeapTupleGetDatum(heap_form_tuple(_tupdesc, _result, _isnull));
  } while (0);
}
extern __attribute__((visibility("default"))) Datum
pmpz_fdiv_qr(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_fdiv_qr(void);
const Pg_finfo_record *pg_finfo_pmpz_fdiv_qr(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_fdiv_qr(FunctionCallInfo fcinfo);
Datum pmpz_fdiv_qr(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_t zf1;
  mpz_t zf2;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  do {
    if (__builtin_expect(((((z2)->_mp_size) == 0)) != 0, 0)) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('1') - '0') & 0x3F) << 18) +
                    (((('2') - '0') & 0x3F) << 24))),
           errmsg("division by zero")),
              errfinish("src/pmpz_arith.c", 145, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  } while (0);
  __gmpz_init(zf1);
  __gmpz_init(zf2);
  __gmpz_fdiv_qr(zf1, zf2, z1, z2);
  do {
    TupleDesc _tupdesc;
    Datum _result[2];
    _Bool _isnull[2] = {0, 0};
    if (get_call_result_type(fcinfo, ((void *)0), &_tupdesc) !=
        TYPEFUNC_COMPOSITE)
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('0') - '0') & 0x3F) + (((('A') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('0') - '0') & 0x3F) << 18) +
                    (((('0') - '0') & 0x3F) << 24))),
           errmsg("function returning composite called in context "
                  "that cannot accept type composite")),
              errfinish("src/pmpz_arith.c", 145, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    _tupdesc = BlessTupleDesc(_tupdesc);
    _result[0] = (Datum)pmpz_from_mpz(zf1);
    _result[1] = (Datum)pmpz_from_mpz(zf2);
    return HeapTupleGetDatum(heap_form_tuple(_tupdesc, _result, _isnull));
  } while (0);
}
extern __attribute__((visibility("default"))) Datum
pmpz_pow_ui(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_pow_ui(void);
const Pg_finfo_record *pg_finfo_pmpz_pow_ui(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_pow_ui(FunctionCallInfo fcinfo);
Datum pmpz_pow_ui(FunctionCallInfo fcinfo) {
  const mpz_t z;
  unsigned long b;
  mpz_t zf;
  mpz_from_pmpz(z, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[0].value))))));
  ;
  ;
  do {
    int64 _tmp = DatumGetInt64((fcinfo->args[1].value));
    if (_tmp < 0) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument can't be negative")),
              errfinish("src/pmpz_arith.c", 170, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
    b = (unsigned long)_tmp;
  } while (0);
  ;
  __gmpz_init(zf);
  __gmpz_pow_ui(zf, z, b);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_root(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_root(void);
const Pg_finfo_record *pg_finfo_pmpz_root(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_root(FunctionCallInfo fcinfo);
Datum pmpz_root(FunctionCallInfo fcinfo) {
  const mpz_t z;
  unsigned long b;
  mpz_t zf;
  mpz_from_pmpz(z, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[0].value))))));
  ;
  do {
    if (__builtin_expect((((z)->_mp_size) < 0) != 0, 0)) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument can't be negative")),
              errfinish("src/pmpz_arith.c", 171, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  } while (0);
  do {
    int64 _tmp = DatumGetInt64((fcinfo->args[1].value));
    if (_tmp < 0) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument can't be negative")),
              errfinish("src/pmpz_arith.c", 171, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
    b = (unsigned long)_tmp;
  } while (0);
  do {
    if (__builtin_expect(((b) <= 0) != 0, 0)) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument must be positive")),
              errfinish("src/pmpz_arith.c", 171, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  } while (0);
  __gmpz_init(zf);
  __gmpz_root(zf, z, b);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_bin_ui(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_bin_ui(void);
const Pg_finfo_record *pg_finfo_pmpz_bin_ui(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_bin_ui(FunctionCallInfo fcinfo);
Datum pmpz_bin_ui(FunctionCallInfo fcinfo) {
  const mpz_t z;
  unsigned long b;
  mpz_t zf;
  mpz_from_pmpz(z, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[0].value))))));
  ;
  ;
  do {
    int64 _tmp = DatumGetInt64((fcinfo->args[1].value));
    if (_tmp < 0) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument can't be negative")),
              errfinish("src/pmpz_arith.c", 172, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
    b = (unsigned long)_tmp;
  } while (0);
  do {
    if (__builtin_expect(((b) < 0) != 0, 0)) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument can't be negative")),
              errfinish("src/pmpz_arith.c", 172, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  } while (0);
  __gmpz_init(zf);
  __gmpz_bin_ui(zf, z, b);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_mul_2exp(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_mul_2exp(void);
const Pg_finfo_record *pg_finfo_pmpz_mul_2exp(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_mul_2exp(FunctionCallInfo fcinfo);
Datum pmpz_mul_2exp(FunctionCallInfo fcinfo) {
  const mpz_t z;
  unsigned long b;
  mpz_t zf;
  mpz_from_pmpz(z, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[0].value))))));
  ;
  ;
  do {
    int64 _tmp = DatumGetInt64((fcinfo->args[1].value));
    if (_tmp < 0) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument can't be negative")),
              errfinish("src/pmpz_arith.c", 182, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
    b = (unsigned long)_tmp;
  } while (0);
  ;
  __gmpz_init(zf);
  __gmpz_mul_2exp(zf, z, b);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_tdiv_q_2exp(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_tdiv_q_2exp(void);
const Pg_finfo_record *pg_finfo_pmpz_tdiv_q_2exp(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_tdiv_q_2exp(FunctionCallInfo fcinfo);
Datum pmpz_tdiv_q_2exp(FunctionCallInfo fcinfo) {
  const mpz_t z;
  unsigned long b;
  mpz_t zf;
  mpz_from_pmpz(z, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[0].value))))));
  ;
  ;
  do {
    int64 _tmp = DatumGetInt64((fcinfo->args[1].value));
    if (_tmp < 0) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument can't be negative")),
              errfinish("src/pmpz_arith.c", 183, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
    b = (unsigned long)_tmp;
  } while (0);
  ;
  __gmpz_init(zf);
  __gmpz_tdiv_q_2exp(zf, z, b);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_tdiv_r_2exp(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_tdiv_r_2exp(void);
const Pg_finfo_record *pg_finfo_pmpz_tdiv_r_2exp(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_tdiv_r_2exp(FunctionCallInfo fcinfo);
Datum pmpz_tdiv_r_2exp(FunctionCallInfo fcinfo) {
  const mpz_t z;
  unsigned long b;
  mpz_t zf;
  mpz_from_pmpz(z, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[0].value))))));
  ;
  ;
  do {
    int64 _tmp = DatumGetInt64((fcinfo->args[1].value));
    if (_tmp < 0) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument can't be negative")),
              errfinish("src/pmpz_arith.c", 184, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
    b = (unsigned long)_tmp;
  } while (0);
  ;
  __gmpz_init(zf);
  __gmpz_tdiv_r_2exp(zf, z, b);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_cdiv_q_2exp(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_cdiv_q_2exp(void);
const Pg_finfo_record *pg_finfo_pmpz_cdiv_q_2exp(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_cdiv_q_2exp(FunctionCallInfo fcinfo);
Datum pmpz_cdiv_q_2exp(FunctionCallInfo fcinfo) {
  const mpz_t z;
  unsigned long b;
  mpz_t zf;
  mpz_from_pmpz(z, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[0].value))))));
  ;
  ;
  do {
    int64 _tmp = DatumGetInt64((fcinfo->args[1].value));
    if (_tmp < 0) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument can't be negative")),
              errfinish("src/pmpz_arith.c", 185, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
    b = (unsigned long)_tmp;
  } while (0);
  ;
  __gmpz_init(zf);
  __gmpz_cdiv_q_2exp(zf, z, b);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_cdiv_r_2exp(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_cdiv_r_2exp(void);
const Pg_finfo_record *pg_finfo_pmpz_cdiv_r_2exp(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_cdiv_r_2exp(FunctionCallInfo fcinfo);
Datum pmpz_cdiv_r_2exp(FunctionCallInfo fcinfo) {
  const mpz_t z;
  unsigned long b;
  mpz_t zf;
  mpz_from_pmpz(z, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[0].value))))));
  ;
  ;
  do {
    int64 _tmp = DatumGetInt64((fcinfo->args[1].value));
    if (_tmp < 0) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument can't be negative")),
              errfinish("src/pmpz_arith.c", 186, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
    b = (unsigned long)_tmp;
  } while (0);
  ;
  __gmpz_init(zf);
  __gmpz_cdiv_r_2exp(zf, z, b);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_fdiv_q_2exp(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_fdiv_q_2exp(void);
const Pg_finfo_record *pg_finfo_pmpz_fdiv_q_2exp(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_fdiv_q_2exp(FunctionCallInfo fcinfo);
Datum pmpz_fdiv_q_2exp(FunctionCallInfo fcinfo) {
  const mpz_t z;
  unsigned long b;
  mpz_t zf;
  mpz_from_pmpz(z, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[0].value))))));
  ;
  ;
  do {
    int64 _tmp = DatumGetInt64((fcinfo->args[1].value));
    if (_tmp < 0) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument can't be negative")),
              errfinish("src/pmpz_arith.c", 187, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
    b = (unsigned long)_tmp;
  } while (0);
  ;
  __gmpz_init(zf);
  __gmpz_fdiv_q_2exp(zf, z, b);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_fdiv_r_2exp(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_fdiv_r_2exp(void);
const Pg_finfo_record *pg_finfo_pmpz_fdiv_r_2exp(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_fdiv_r_2exp(FunctionCallInfo fcinfo);
Datum pmpz_fdiv_r_2exp(FunctionCallInfo fcinfo) {
  const mpz_t z;
  unsigned long b;
  mpz_t zf;
  mpz_from_pmpz(z, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[0].value))))));
  ;
  ;
  do {
    int64 _tmp = DatumGetInt64((fcinfo->args[1].value));
    if (_tmp < 0) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument can't be negative")),
              errfinish("src/pmpz_arith.c", 188, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
    b = (unsigned long)_tmp;
  } while (0);
  ;
  __gmpz_init(zf);
  __gmpz_fdiv_r_2exp(zf, z, b);
  return PointerGetDatum(pmpz_from_mpz(zf));
}
extern __attribute__((visibility("default"))) Datum
pmpz_even(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_even(void);
const Pg_finfo_record *pg_finfo_pmpz_even(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_even(FunctionCallInfo fcinfo);
Datum pmpz_even(FunctionCallInfo fcinfo) {
  const mpz_t op;
  mpz_from_pmpz(
      op, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  return BoolGetDatum((!(((op)->_mp_size != 0) & ((int)((op)->_mp_d[0])))));
}
extern __attribute__((visibility("default"))) Datum
pmpz_odd(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_odd(void);
const Pg_finfo_record *pg_finfo_pmpz_odd(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_odd(FunctionCallInfo fcinfo);
Datum pmpz_odd(FunctionCallInfo fcinfo) {
  const mpz_t op;
  mpz_from_pmpz(
      op, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  return BoolGetDatum((((op)->_mp_size != 0) & ((int)((op)->_mp_d[0]))));
}
extern __attribute__((visibility("default"))) Datum
pmpz_perfect_power(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_perfect_power(void);
const Pg_finfo_record *pg_finfo_pmpz_perfect_power(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_perfect_power(FunctionCallInfo fcinfo);
Datum pmpz_perfect_power(FunctionCallInfo fcinfo) {
  const mpz_t op;
  mpz_from_pmpz(
      op, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  return BoolGetDatum(__gmpz_perfect_power_p(op));
}
extern __attribute__((visibility("default"))) Datum
pmpz_perfect_square(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_perfect_square(void);
const Pg_finfo_record *pg_finfo_pmpz_perfect_square(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_perfect_square(FunctionCallInfo fcinfo);
Datum pmpz_perfect_square(FunctionCallInfo fcinfo) {
  const mpz_t op;
  mpz_from_pmpz(
      op, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  return BoolGetDatum(__gmpz_perfect_square_p(op));
}
extern __attribute__((visibility("default"))) Datum
pmpz_cmp(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_cmp(void);
const Pg_finfo_record *pg_finfo_pmpz_cmp(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_cmp(FunctionCallInfo fcinfo);
Datum pmpz_cmp(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  return Int32GetDatum(__gmpz_cmp(z1, z2));
}
extern __attribute__((visibility("default"))) Datum
pmpz_eq(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_eq(void);
const Pg_finfo_record *pg_finfo_pmpz_eq(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_eq(FunctionCallInfo fcinfo);
Datum pmpz_eq(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  return BoolGetDatum(__gmpz_cmp(z1, z2) == 0);
}
extern __attribute__((visibility("default"))) Datum
pmpz_ne(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_ne(void);
const Pg_finfo_record *pg_finfo_pmpz_ne(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_ne(FunctionCallInfo fcinfo);
Datum pmpz_ne(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  return BoolGetDatum(__gmpz_cmp(z1, z2) != 0);
}
extern __attribute__((visibility("default"))) Datum
pmpz_gt(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_gt(void);
const Pg_finfo_record *pg_finfo_pmpz_gt(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_gt(FunctionCallInfo fcinfo);
Datum pmpz_gt(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  return BoolGetDatum(__gmpz_cmp(z1, z2) > 0);
}
extern __attribute__((visibility("default"))) Datum
pmpz_ge(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_ge(void);
const Pg_finfo_record *pg_finfo_pmpz_ge(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_ge(FunctionCallInfo fcinfo);
Datum pmpz_ge(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  return BoolGetDatum(__gmpz_cmp(z1, z2) >= 0);
}
extern __attribute__((visibility("default"))) Datum
pmpz_lt(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_lt(void);
const Pg_finfo_record *pg_finfo_pmpz_lt(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_lt(FunctionCallInfo fcinfo);
Datum pmpz_lt(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  return BoolGetDatum(__gmpz_cmp(z1, z2) < 0);
}
extern __attribute__((visibility("default"))) Datum
pmpz_le(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_le(void);
const Pg_finfo_record *pg_finfo_pmpz_le(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_le(FunctionCallInfo fcinfo);
Datum pmpz_le(FunctionCallInfo fcinfo) {
  const mpz_t z1;
  const mpz_t z2;
  mpz_from_pmpz(
      z1, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      z2, ((pmpz *)(pg_detoast_datum(
              (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  return BoolGetDatum(__gmpz_cmp(z1, z2) <= 0);
}
extern __attribute__((visibility("default"))) Datum
pmpz_hash(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_hash(void);
const Pg_finfo_record *pg_finfo_pmpz_hash(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_hash(FunctionCallInfo fcinfo);
Datum pmpz_hash(FunctionCallInfo fcinfo) {
  const mpz_t z;
  mpz_from_pmpz(z, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[0].value))))));
  ;
  return pmpz_get_hash(z);
}
Datum pmpz_get_hash(mpz_srcptr z) {
  int64 z64;
  if (0 == pmpz_get_int64(z, &z64)) {
    return DirectFunctionCall1Coll(
        hashint8, ((Oid)0),
        ((((void)({
           do {
             _Static_assert(
                 __builtin_types_compatible_p(__typeof__(z64), int64),
                 "z64"
                 " does not have type "
                 "int64");
           } while (0);
           1;
         }))),
         Int64GetDatum(z64)));
  }
  return Int32GetDatum(
      hash_any((unsigned char *)((z)->_mp_d),
               (((z)->_mp_size) >= 0 ? ((z)->_mp_size) : -((z)->_mp_size)) *
                   sizeof(mp_limb_t)));
}
extern __attribute__((visibility("default"))) Datum
pmpz_sgn(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_sgn(void);
const Pg_finfo_record *pg_finfo_pmpz_sgn(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_sgn(FunctionCallInfo fcinfo);
Datum pmpz_sgn(FunctionCallInfo fcinfo) {
  const mpz_t n;
  mpz_from_pmpz(n, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[0].value))))));
  ;
  return Int32GetDatum(((n)->_mp_size < 0 ? -1 : (n)->_mp_size > 0));
}
extern __attribute__((visibility("default"))) Datum
pmpz_divisible(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_divisible(void);
const Pg_finfo_record *pg_finfo_pmpz_divisible(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_divisible(FunctionCallInfo fcinfo);
Datum pmpz_divisible(FunctionCallInfo fcinfo) {
  const mpz_t n;
  const mpz_t d;
  mpz_from_pmpz(n, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(d, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[1].value))))));
  ;
  return BoolGetDatum(__gmpz_divisible_p(n, d));
}
extern __attribute__((visibility("default"))) Datum
pmpz_divisible_2exp(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_divisible_2exp(void);
const Pg_finfo_record *pg_finfo_pmpz_divisible_2exp(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_divisible_2exp(FunctionCallInfo fcinfo);
Datum pmpz_divisible_2exp(FunctionCallInfo fcinfo) {
  const mpz_t n;
  mp_bitcnt_t b;
  mpz_from_pmpz(n, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[0].value))))));
  ;
  do {
    int64 _tmp = DatumGetInt64((fcinfo->args[1].value));
    if (_tmp < 0) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument can't be negative")),
              errfinish("src/pmpz_arith.c", 310, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
    b = (unsigned long)_tmp;
  } while (0);
  return BoolGetDatum(__gmpz_divisible_2exp_p(n, b));
}
extern __attribute__((visibility("default"))) Datum
pmpz_congruent(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_congruent(void);
const Pg_finfo_record *pg_finfo_pmpz_congruent(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_congruent(FunctionCallInfo fcinfo);
Datum pmpz_congruent(FunctionCallInfo fcinfo) {
  const mpz_t n;
  const mpz_t c;
  const mpz_t d;
  mpz_from_pmpz(n, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(c, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[1].value))))));
  ;
  mpz_from_pmpz(d, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[2].value))))));
  ;
  return BoolGetDatum(__gmpz_congruent_p(n, c, d));
}
extern __attribute__((visibility("default"))) Datum
pmpz_congruent_2exp(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_congruent_2exp(void);
const Pg_finfo_record *pg_finfo_pmpz_congruent_2exp(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_congruent_2exp(FunctionCallInfo fcinfo);
Datum pmpz_congruent_2exp(FunctionCallInfo fcinfo) {
  const mpz_t n;
  const mpz_t c;
  mp_bitcnt_t b;
  mpz_from_pmpz(n, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(c, ((pmpz *)(pg_detoast_datum((struct varlena *)DatumGetPointer(
                       (fcinfo->args[1].value))))));
  ;
  do {
    int64 _tmp = DatumGetInt64((fcinfo->args[2].value));
    if (_tmp < 0) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument can't be negative")),
              errfinish("src/pmpz_arith.c", 344, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
    b = (unsigned long)_tmp;
  } while (0);
  return BoolGetDatum(__gmpz_congruent_2exp_p(n, c, b));
}
extern __attribute__((visibility("default"))) Datum
pmpz_powm(FunctionCallInfo fcinfo);
extern __attribute__((visibility("default"))) const Pg_finfo_record *
pg_finfo_pmpz_powm(void);
const Pg_finfo_record *pg_finfo_pmpz_powm(void) {
  static const Pg_finfo_record my_finfo = {1};
  return &my_finfo;
}
extern int no_such_variable;
Datum pmpz_powm(FunctionCallInfo fcinfo);
Datum pmpz_powm(FunctionCallInfo fcinfo) {
  const mpz_t base;
  const mpz_t exp;
  const mpz_t mod;
  mpz_t zf;
  mpz_from_pmpz(
      base, ((pmpz *)(pg_detoast_datum(
                (struct varlena *)DatumGetPointer((fcinfo->args[0].value))))));
  ;
  mpz_from_pmpz(
      exp, ((pmpz *)(pg_detoast_datum(
               (struct varlena *)DatumGetPointer((fcinfo->args[1].value))))));
  ;
  do {
    if (__builtin_expect((((exp)->_mp_size) < 0) != 0, 0)) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('2') - '0') & 0x3F) << 18) +
                    (((('3') - '0') & 0x3F) << 24))),
           errmsg("argument can't be negative")),
              errfinish("src/pmpz_arith.c", 359, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  } while (0);
  mpz_from_pmpz(
      mod, ((pmpz *)(pg_detoast_datum(
               (struct varlena *)DatumGetPointer((fcinfo->args[2].value))))));
  ;
  do {
    if (__builtin_expect(((((mod)->_mp_size) == 0)) != 0, 0)) {
      do {
        int __errno_location __attribute__((unused));
        if (__builtin_constant_p(21) && (21) >= 21
                ? errstart_cold(21, ((void *)0))
                : errstart(21, ((void *)0)))
          (errcode((((('2') - '0') & 0x3F) + (((('2') - '0') & 0x3F) << 6) +
                    (((('0') - '0') & 0x3F) << 12) +
                    (((('1') - '0') & 0x3F) << 18) +
                    (((('2') - '0') & 0x3F) << 24))),
           errmsg("division by zero")),
              errfinish("src/pmpz_arith.c", 361, __func__);
        if (__builtin_constant_p(21) && (21) >= 21)
          abort();
      } while (0);
    }
  } while (0);
  __gmpz_init(zf);
  __gmpz_powm(zf, base, exp, mod);
  return PointerGetDatum(pmpz_from_mpz(zf));
}

