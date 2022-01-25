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

int subtract(int x, int y) {
  int64_t x64 = x;
  int64_t y64 = y;
  int64_t o64 = x - y;
  if (o64 <= INT_MAX && o64 >= -INT_MAX) {
    return o64;
  } else {
    return NA_INTEGER;
  }
}


SEXP C_minus(SEXP x, SEXP y) {
  if (xlength(x) != xlength(y) && xlength(y) != 1) {
    error("Bad lengths.");
  }
  if (!isInteger(x) && !isReal(x)) {
    error("x must be numeric.");
  }
  if (!isInteger(y) && !isReal(y)) {
    error("y must be numeric.");
  }

  if (!isInteger(x) || !isInteger(y)) {
    return R_NilValue;
  }
  const int * xp = INTEGER(x);
  const int * yp = INTEGER(y);

  R_xlen_t N = xlength(x);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * ansp = INTEGER(ans);
  if (xlength(x) == xlength(y)) {
    for (R_xlen_t i = 0; i < N; ++i) {
      if (xp[i] == NA_INTEGER || yp[i] == NA_INTEGER) {
        ansp[i] = NA_INTEGER;
        continue;
      }
      ansp[i] = subtract(xp[i], yp[i]);
    }
  } else {
    // xlength(y) == 1
    for (R_xlen_t i = 0; i < N; ++i) {
      if (xp[i] == NA_INTEGER || yp[0] == NA_INTEGER) {
        ansp[i] = NA_INTEGER;
        continue;
      }
      ansp[i] = subtract(xp[i], yp[0]);
    }
  }

  UNPROTECT(1);
  return ans;
}
