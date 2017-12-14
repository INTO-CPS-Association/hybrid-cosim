/*
 * dse_macros.h
 *
 * Macro definitions to use with embedded code generation
 *
 */

#ifndef _dse_macros_h_
#define _dse_macros_h_

#define ModelFunctionEnd() \
	   return 0

#define IF   (
#define THEN ) ? (
#define ELSE ) :
#define AND &&
#define OR ||
#define NOT !
#define true 1
#define false 0

static
#if defined(_MSC_VER) && _MSC_VER>=1200
__inline
#elif __GNUC__
__inline
#endif
double sqr(double x) {
	return x*x;
}

#define divmacro(x,sx,y,sy) (((double)(x))/(y))

double RealBmax(double x,double y) {return ((x) > (y) ? (x) : (y) );}

/* Backup solution to scalar system Ax=b, if A=0 */
#define RememberSimple_(x, nr) \
	  0.0

#define SolveScalarLinear(A, As, b, bs, x, xs)\
{double Aval_=A;double bval_=b;if (Aval_!=0) x=bval_/Aval_;}

#define SolveScalarLinearParametric(A, As, b, bs, x, xs)\
{double Aval_=A;double bval_=b;if (Aval_!=0) x=bval_/Aval_;}

/* External LU-solver interface for linear systems of equations */

#ifndef external_lu_solver
#define external_lu_solver 1
#define NWLINEARSOLVER(n) \
	(n)
#define LinFactorize(n, A, length_work_vector, work_vector, pivot_vector) \
	(-1) /* No external LU-solver defined */
#define LinSolve(n, A, pivot_vector, b, length_work_vector, work_vector) \
	(-1) /* No external LU-solver defined */
#endif

/* Currently a fixed limit on number of helpvar */
#define NGlobalHelp_ 100
static double helpvar[NGlobalHelp_] = {0};

#if _MSC_VER>=1700
 #define DYNX(s,i) (*(s+i))
#else
 #define DYNX(s,i) s[i]
#endif
#define DYNhelp (helpvar)

/* Activation conditions not considered, subClocks with ticks > 1 not supported */
#define beginwhenBlock
#define whenModelicaS(cond)
#define endwhenModelica()
#define endwhenBlock

#define Assert(b,x)
#define AssertModelica(b,bs,x)
#define AssertModelica3(b,bs,x,l)
#define AssertModelica4(b,bs,x,l,hi)

#define PRE(x, nr) x

#define sampleNew3(start, interval, phase, maxVal, SampleCounter) \
	false

/* To avoid compilation error from subClock.lastTime, time in model equations currently not supported */
#define Time 0.0   

#endif
