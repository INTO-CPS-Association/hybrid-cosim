/* Internal header file for Jacobian computations. */

#ifndef jac_h
#define jac_h

#include "types.h"

/* ----------------- function delcarations ----------------- */

/* Setup */
DYMOLA_STATIC void jac_setup(size_t ngroups);

/* computes function f(t,y) */
DYMOLA_STATIC int jac_f(realtype t, N_Vector y, N_Vector ydot, void *user_data);

/* Jacobian routine, computes J(t,y) = df/dy numerically */
DYMOLA_STATIC int jac_Jacobian(long N, realtype t,
							   N_Vector y, N_Vector fy, DlsMat J, void *user_data,
							   N_Vector tmp1, N_Vector tmp2, N_Vector tmp3);

#endif /* jac_h */
