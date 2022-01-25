#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP Add2(SEXP, SEXP);
extern SEXP Add3(SEXP, SEXP);
extern SEXP any_more_than_2(SEXP, SEXP);
extern SEXP C_minus(SEXP, SEXP);
extern SEXP print_foo(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"Add2",            (DL_FUNC) &Add2,            2},
    {"Add3",            (DL_FUNC) &Add3,            2},
    {"any_more_than_2", (DL_FUNC) &any_more_than_2, 2},
    {"C_minus",         (DL_FUNC) &C_minus,         2},
    {"print_foo",       (DL_FUNC) &print_foo,       1},
    {NULL, NULL, 0}
};

void R_init_camateurclass21(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
