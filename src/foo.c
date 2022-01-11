
#if _OPENMP
#include <omp.h>
#endif

#include <R.h>
#define USE_RINTERNALS
#include <Rinternals.h>
#include <Rversion.h>
#include <stdint.h> // for uint64_t rather than unsigned long long
#include <stdbool.h>
#include <math.h>
#include <ctype.h>


SEXP print_foo(SEXP x) {
  Rprintf("foo\n");
  Rprintf("foo\n");
  Rprintf("foo\n");
  return R_NilValue;
}

int adder(int x, int y) {
  return x + y;
}

SEXP Add2(SEXP x, SEXP y) {
  if (!isInteger(x)) {
    error("x was type '%s' but must be integer.", type2char(TYPEOF(x)));
  }
  int xi = asInteger(x);
  int yi = asInteger(y);
  int oi = adder(xi, yi);
  return ScalarInteger(oi);
}

SEXP Add3(SEXP x, SEXP y) {
  if (!isInteger(x) || !isInteger(y)) {
    error("x was type '%s' and y was type '%s' but must be integer.",
          type2char(TYPEOF(x)),
          type2char(TYPEOF(y)));
  }
  const int * xp = INTEGER(x);
  const int * yp = INTEGER(y);

  R_xlen_t N = xlength(x);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  for (R_xlen_t i = 0; i < N; ++i) {
    INTEGER(ans)[i] = xp[i] + yp[i];
  }
  UNPROTECT(1);
  return ans;
}

SEXP any_more_than_2(SEXP x, SEXP y) {
  if (!isInteger(x) || !isInteger(y)) {
    error("x was type '%s' and y was type '%s' but must be integer.",
          type2char(TYPEOF(x)),
          type2char(TYPEOF(y)));
  }
  const int * xp = INTEGER(x);
  const int * yp = INTEGER(y);

  R_xlen_t N = xlength(x);

  for (R_xlen_t i = 0; i < N; ++i) {
    if (xp[i] - yp[i] > 2) {
      return ScalarInteger(i + 1);
    }
  }
  return ScalarInteger(0);
}





