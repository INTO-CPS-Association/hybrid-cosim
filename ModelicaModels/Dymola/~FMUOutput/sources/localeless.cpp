#include "localeless.h"
#include <math.h>
#if _MSC_VER >= 1400	/* To avoid compilation error on dSPACE DS1006 (gcc) */
#include <locale.h>
#endif
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#if _MSC_VER >= 1400
#ifdef __cplusplus
class MyCLocal {
	MyCLocal(MyCLocal const&);
	void operator=(MyCLocal const&);
public:
	_locale_t cloc;
	MyCLocal() {cloc=_create_locale(LC_ALL, "C");}
	~MyCLocal() {_free_locale(cloc);}
};
static _locale_t *Clocale() {
	/* Avoiding memory leak at end */
	static MyCLocal myloc;
	return &myloc.cloc;
};
void freeClocale(){
	/*Emtpy in CPP only relevant for c code*/
};
#else
static _locale_t cloc = NULL;
static int firstTime = 1;
static _locale_t *Clocale() {
	/* The c-version has a memory leak; cannot avoid without using atexit and atexit for DLLs seems bad */
	if (firstTime) cloc=_create_locale(LC_ALL, "C");
	firstTime = 0;
	return &cloc;
}
void freeClocale(){
	_free_locale(cloc);
	cloc = NULL;
	firstTime = 1;
}
#endif
#endif

double atofC(const char *str) {
#if _MSC_VER >= 1400
	return _atof_l(str, *Clocale());
#else
	return atof(str);
#endif
}

int atoiC(const char *str) {
#if _MSC_VER >= 1400
	return _atoi_l(str, *Clocale());
#else
	return atoi(str);
#endif
}

int atolC(const char *str) {
#if _MSC_VER >= 1400
	return _atol_l(str, *Clocale());
#else
	return atol(str);
#endif
}

#if _MSC_VER
int _stricmpC(const char *string1,const char *string2) {
#if _MSC_VER >= 1400
	return _stricmp_l(string1, string2, *Clocale());
#else
	return _stricmp(string1, string2);
#endif
}
#endif

int isalnumC(int c) {
#if _MSC_VER >= 1400
	return _isalnum_l(c, *Clocale());
#else
	return isalnum(c);
#endif
}

int isalphaC(int c) {
#if _MSC_VER >= 1400
	return _isalpha_l(c, *Clocale());
#else
	return isalpha(c);
#endif
}

int isdigitC(int c) {
#if _MSC_VER >= 1400
	return _isdigit_l(c, *Clocale());
#else
	return isdigit(c);
#endif
}

int isupperC(int c) {
#if _MSC_VER >= 1400
	return _isupper_l(c, *Clocale());
#else
	return isupper(c);
#endif
}

int islowerC(int c) {
#if _MSC_VER >= 1400
	return _islower_l(c, *Clocale());
#else
	return islower(c);
#endif
}

int isspaceC(int c) {
#if _MSC_VER >= 1400
	return _isspace_l(c, *Clocale());
#else
	return isspace(c);
#endif
}

int toupperC(int c) {
#if _MSC_VER >= 1400
	return _toupper_l(c, *Clocale());
#else
 #if !defined(NO_FILE)
	return toupper(c);
 #else
	return c;
 #endif
#endif
}
int tolowerC(int c) {
#if _MSC_VER >= 1400
	return _tolower_l(c, *Clocale());
#else
	return tolower(c);
#endif
}



extern int fscanfC_Bracket_255s(FILE*f, char*s, char *s2) {
#if !defined(NO_FILE)
 #if _MSC_VER >= 1400
	_fscanf_l(f, "%[^\\[]255s", *Clocale(), s);
	return _fscanf_l(f, "%1s", *Clocale(), s2);
 #else
	fscanf(f, "%[^\\[]255s", s);
	return fscanf(f, "%1s", s2);
 #endif
#else
	return 0;
#endif
}

extern int fscanfC255s(FILE*f, char*s) {
#if !defined(NO_FILE)
 #if _MSC_VER >= 1400
	return _fscanf_l(f, "%255s", *Clocale(), s);
 #else
	return fscanf(f, "%255s", s);
 #endif
#else
	return 0;
#endif
}

extern int fscanfClf(FILE*f, double*x) {
#if !defined(NO_FILE)
 #if _MSC_VER >= 1400
	return _fscanf_l(f, " %lg", *Clocale(), x);
 #else
	return fscanf(f, " %lg", x);
 #endif
#else
	return 0;
#endif
}
extern int fscanfClf3(FILE*f, double*x, double*y, double*z) {
#if !defined(NO_FILE)
 #if _MSC_VER >= 1400
	return _fscanf_l(f, " %lg %lg %lg",  *Clocale(), x,y,z);
 #else
	return fscanf(f, " %lg %lg %lg", x,y,z);
 #endif
#else
	return 0;
#endif	
}
extern int fscanfCg(FILE*f, float*x) {
#if !defined(NO_FILE)
 #if _MSC_VER >= 1400
	return _fscanf_l(f,  " %g", *Clocale(), x);
 #else
	return fscanf(f, " %g", x);
 #endif
#else
	return 0;
#endif
}
extern int fscanfCd(FILE*f,  int*x) {
#if !defined(NO_FILE)
 #if _MSC_VER >= 1400
	return _fscanf_l(f, " %d", *Clocale(), x);
 #else
	return fscanf(f, " %d", x);
 #endif
#else
	return 0;
#endif
}
extern int fscanfCu3(FILE*f,  unsigned*r,unsigned*g,unsigned*b) {
#if !defined(NO_FILE)
 #if _MSC_VER >= 1400
	return _fscanf_l(f, " %u %u %u", *Clocale(), r,g,b);
 #else
	return fscanf(f, " %u %u %u", r,g,b);
 #endif
#else
	return 0;
#endif
}
extern int fscanfCd3(FILE*f,  int*r,int*g,int*b) {
#if !defined(NO_FILE)
 #if _MSC_VER >= 1400
	return _fscanf_l(f, " %d %d %d", *Clocale(), r,g,b);
 #else
	return fscanf(f, " %d %d %d", r,g,b);
 #endif
#else
	return 0;
#endif
}

extern int fscanfCcond_version_s(FILE*f, char*cond, char*vers,char*s) {
#if !defined(NO_FILE)
 #if _MSC_VER >= 1400
	return _fscanf_l(f," %[<>=] \"%[^\"]\" %s)",*Clocale(), cond,vers,s);
 #else
	return fscanf(f," %[<>=] \"%[^\"]\" %s)",cond,vers,s);
 #endif
#else
	return 0;
#endif
}

extern int sscanfCd(const char*line, int*x) {
#if _MSC_VER >= 1400
	return _sscanf_l(line, " %d", *Clocale(), x);
#else
#if !defined(NO_FILE)
	return sscanf(line, " %d", x);
#else
	return 0;
#endif
#endif
}
extern int sscanfCd5(const char*line, int*a, int*b,int*c,int*d,int*e) {
#if _MSC_VER >= 1400
	return _sscanf_l(line, " %d %d %d %d %d", *Clocale(), a,b,c,d,e);
#else
#if !defined(NO_FILE)
	return sscanf(line, " %d %d %d %d %d", a,b,c,d,e);
#else
	return 0;
#endif
#endif
}

extern int sscanfCd_minus3(const char*line, int*y,int*m,int*d) {
#if _MSC_VER >= 1400
	return _sscanf_l(line, "%d-%d-%d", *Clocale(), y, m, d);
#else
#if !defined(NO_FILE)
	return sscanf(line, "%d-%d-%d", y, m, d);
#else
	return 0;
#endif
#endif
}
extern int sscanfClg_49s(const char*line, double*x, char*s) {
#if _MSC_VER >= 1400
	return _sscanf_l(line, "%lg %49s", *Clocale(), x, s);
#else
#if !defined(NO_FILE)
	return sscanf(line, "%lg %49s", x, s);
#else
	return 0;
#endif
#endif
}

extern int sscanfCg(const char*line, float*x){
#if _MSC_VER >= 1400
	return _sscanf_l(line,  " %g", *Clocale(), x);
#else
#if !defined(NO_FILE)
	return sscanf(line, " %g", x);
#else
	return 0;
#endif
#endif
}
extern int sscanfCx2_underscore(const char*line,unsigned int*a,unsigned int*b) {
#if _MSC_VER >= 1400
	return _sscanf_l(line,  "%lx_%lx", *Clocale(), a,b);
#else
#if !defined(NO_FILE)
	return sscanf(line, "%lx_%lx", a,b);
#else
	return 0;
#endif
#endif
}
extern int sscanfClu(const char*line, unsigned int*a) {
#if _MSC_VER >= 1400
	return _sscanf_l(line,  "%lu", *Clocale(), a);
#else
#if !defined(NO_FILE)
	return sscanf(line, "%lu", a);
#else
	return 0;
#endif
#endif
}



extern int sscanfCg_comma(const char*line, float*x){
#if _MSC_VER >= 1400
	return _sscanf_l(line,  " %g,", *Clocale(),x);
#else
#if !defined(NO_FILE)
	return sscanf(line, " %g,", x);
#else
	return 0;
#endif
#endif
}

extern int sscanfClg(const char*line, double*x) {
#if _MSC_VER >= 1400
	return _sscanf_l(line, " %lg", *Clocale(), x);
#else
#if !defined(NO_FILE)
	return sscanf(line, " %lg", x);
#else
	return 0;
#endif
#endif
}
extern int sscanfCcomp_s_par(const char*line, char*cond, char*vers) {
#if _MSC_VER >= 1400
	return _sscanf_l(line,  " %[<>=] %s)",*Clocale(), cond, vers);
#else
#if !defined(NO_FILE)
	return sscanf(line, " %[<>=] %s)", cond, vers);
#else
	return 0;
#endif
#endif
}
extern int sscanfCu(const char*line, unsigned*x) {
#if _MSC_VER >= 1400
	return _sscanf_l(line,  " %u", *Clocale(),x);
#else
#if !defined(NO_FILE)
	return sscanf(line, " %u", x);
#else
	return 0;
#endif
#endif
}
extern int sscanfCg_comma4(const char*line, float*a,float*b,float*c,float*d) {
#if _MSC_VER >= 1400
	return _sscanf_l(line,  "%g,%g,%g,%g,",*Clocale(), a,b,c,d);
#else
#if !defined(NO_FILE)
	return sscanf(line, "%g,%g,%g,%g,", a,b,c,d);
#else
	return 0;
#endif
#endif
}
extern int sscanfCi_comma4(const char*line, int*a,int*b,int*c,int*d) {
#if _MSC_VER >= 1400
	return _sscanf_l(line, "%i,%i,%i,%i,", *Clocale(),  a,b,c,d);
#else
#if !defined(NO_FILE)
	return sscanf(line, "%i,%i,%i,%i,", a,b,c,d);
#else
	return 0;
#endif
#endif
}
extern int sscanfCi(const char*line, int*a) {
#if _MSC_VER >= 1400
	return _sscanf_l(line,  "%i",*Clocale(),a);
#else
#if !defined(NO_FILE)
	return sscanf(line, "%i",a);
#else
	return 0;
#endif
#endif
}
extern int sscanfClfc(const char*line, double*d, char*dummy) {
	#if _MSC_VER >= 1400
	return _sscanf_l(line,  "%lg %c",*Clocale(), d, dummy);
#else
#if !defined(NO_FILE)
	return sscanf(line, "%lg %c", d, dummy);
#else
	return 0;
#endif
#endif
}
extern int sscanfCtext_ssdd(const char*line, const char*fmt, char*a,char*b, int*c,int *d) {
#if _MSC_VER >= 1400
	return _sscanf_l(line,  fmt,*Clocale(), a,b,c,d);
#else
#if !defined(NO_FILE)
	return sscanf(line, fmt, a,b,c,d);
#else
	return 0;
#endif
#endif
}
extern int sscanfCincludename(const char*line, char*s) {
#if _MSC_VER >= 1400
	return _sscanf_l(line,  "#include \"%[^\"]\"",*Clocale(), s);
#else
#if !defined(NO_FILE) && !defined(LABCAR)
	return sscanf(line, "#include \"%[^\"]\"", s);
#else
	return 0;
#endif
#endif
}
extern int sscanfCversion(const char*line,char*vers) {
#if _MSC_VER >= 1400
	return _sscanf_l(line,  "( version = \"%[^\"]\" )",*Clocale(), vers);
#else
#if !defined(NO_FILE) && !defined(LABCAR)
	return sscanf(line,"( version = \"%[^\"]\" )",vers);
#else
	return 0;
#endif
#endif
}

extern int sscanfCtext_d(const char*line, const char*txtWithPercentD, int*x) {
	#if _MSC_VER >= 1400
	return _sscanf_l(line,  txtWithPercentD,*Clocale(), x);
#else
#if !defined(NO_FILE) && !defined(LABCAR)
	return sscanf(line, txtWithPercentD, x);
#else
	return 0;
#endif
#endif
}
extern int sscanfCtext_d3(const char*line, const char*txtWithPercentD, int*r,int*g,int*b) {
#if _MSC_VER >= 1400
	return _sscanf_l(line,  txtWithPercentD,*Clocale(), r,g,b);
#else
#if !defined(NO_FILE) && !defined(LABCAR)
	return sscanf(line, txtWithPercentD, r,g,b);
#else
	return 0;
#endif
#endif
}

extern int sscanfCtext_d4(const char*line, const char*txtWithPercentD, int*a,int*b,int*c,int*d) {
	#if _MSC_VER >= 1400
	return _sscanf_l(line,  txtWithPercentD,*Clocale(), a,b,c,d);
#else
#if !defined(NO_FILE) && !defined(LABCAR)
	return sscanf(line, txtWithPercentD, a,b,c,d);
#else
	return 0;
#endif
#endif
}
extern int sscanfCtext_d5(const char*line, const char*txtWithPercentD, int*a,int*b,int*c,int*d,int*e) {
	#if _MSC_VER >= 1400
	return _sscanf_l(line,  txtWithPercentD,*Clocale(), a,b,c,d,e);
#else
#if !defined(NO_FILE) && !defined(LABCAR)
	return sscanf(line, txtWithPercentD, a,b,c,d,e);
#else
	return 0;
#endif
#endif
}
extern int sscanfCi3_slash(const char*line,int*a,int*b,int*c) {
	#if _MSC_VER >= 1400
	return _sscanf_l(line,  "%i/%i/%i",*Clocale(), a,b,c);
#else
#if !defined(NO_FILE) && !defined(LABCAR)
	return sscanf(line, "%i/%i/%i", a,b,c);
#else
	return 0;
#endif
#endif
}
extern int sscanfCi2_slash(const char*line,int*a,int*b) {
	#if _MSC_VER >= 1400
	return _sscanf_l(line,  "%i/%i",*Clocale(), a,b);
#else
#if !defined(NO_FILE) && !defined(LABCAR)
	return sscanf(line, "%i/%i", a,b);
#else
	return 0;
#endif
#endif
}
extern int sscanfCi2_slashlash(const char*line,int*a,int*b) {
	#if _MSC_VER >= 1400
	return _sscanf_l(line,  "%i//%i",*Clocale(), a,b);
#else
#if !defined(NO_FILE) && !defined(LABCAR)
	return sscanf(line, "%i//%i", a,b);
#else
	return 0;
#endif
#endif
}
		
extern int sscanfC255s_n(const char*line, char*s,int*length) {
#if _MSC_VER >= 1400
	return _sscanf_l(line,  "%255s%n",*Clocale(), s, length);
#else
#if !defined(NO_FILE) && !defined(LABCAR)
	return sscanf(line, "%255s%n",  s, length);
#else
	return 0;
#endif
#endif
}
extern int sscanfC255s(const char*line, char*s) {
#if _MSC_VER >= 1400
	return _sscanf_l(line,  "%255s",*Clocale(), s);
#else
#if !defined(NO_FILE) && !defined(LABCAR)
	return sscanf(line, "%255s",  s);
#else
	return 0;
#endif
#endif
}

extern int sscanfCtext_s2(const char*line, const char*txtWithPercentD,char*a,char*b) {
#if _MSC_VER >= 1400
	return _sscanf_l(line,  txtWithPercentD,*Clocale(), a,b);
#else
#if !defined(NO_FILE) && !defined(LABCAR)
	return sscanf(line, txtWithPercentD, a,b);
#else
	return 0;
#endif
#endif
}
extern int sscanfCtext_s4(const char*line, const char*txtWithPercentD,char*a,char*b,char*c,char*d) {
#if _MSC_VER >= 1400
	return _sscanf_l(line,  txtWithPercentD,*Clocale(), a,b,c,d);
#else
#if !defined(NO_FILE) && !defined(LABCAR)
	return sscanf(line, txtWithPercentD, a,b,c,d);
#else
	return 0;
#endif
#endif
}
extern int sscanfCtext_sd(const char*line, const char*txtWithPercentD,char*a,int*b) {
#if _MSC_VER >= 1400
	return _sscanf_l(line,  txtWithPercentD,*Clocale(), a,b);
#else
#if !defined(NO_FILE) && !defined(LABCAR)
	return sscanf(line, txtWithPercentD, a,b);
#else
	return 0;
#endif
#endif
}
extern int sscanfCtext_s2d(const char*line, const char*txtWithPercentD,char*a,char*b,int*c) {
#if _MSC_VER >= 1400
	return _sscanf_l(line,  txtWithPercentD,*Clocale(), a,b,c);
#else
#if !defined(NO_FILE) && !defined(LABCAR)
	return sscanf(line, txtWithPercentD, a,b,c);
#else
	return 0;
#endif
#endif
}
extern int sprintfC(char*s, const char*format, ...) {
	va_list extra;
	int res;
	va_start(extra, format);
#if _MSC_VER >= 1400
	res = _vsprintf_l(s, format, *Clocale(), extra);
#else
	res =vsprintf(s, format, extra); 
#endif
	va_end(extra);
	return res;
}

extern int fprintfC(FILE*f, const char*format, ...) {
	va_list extra;
	int res;
	va_start(extra, format);
#if !defined(NO_FILE)
 #if _MSC_VER >= 1400
	res = _vfprintf_l(f, format, *Clocale(), extra);
 #else
	res =vfprintf(f, format, extra);
 #endif
#else
	res = -1;
#endif
	va_end(extra);
	return res;
}

extern int vfprintfC(FILE*f, const char*format, va_list extra) {
	int res;
#if !defined(NO_FILE)
 #if _MSC_VER >= 1400
	res = _vfprintf_l(f, format, *Clocale(), extra);
 #else
	res =vfprintf(f, format, extra);
 #endif
#else
	res = -1;
#endif
	return res;
}

extern int vsnprintfC(char*buf,size_t buf_len,const char*fmt,va_list arg) {
  int res;
  /* Use len-1 to ensure that string will be nul-terminated. */
#if _MSC_VER >= 1400
  res=_vsnprintf_l(buf, buf_len-1, fmt, *Clocale(), arg);
#elif defined(_MSC_VER) && _MSC_VER >= 1200
  res=_vsnprintf(buf, buf_len-1, fmt, arg);
#else
  res=vsnprintf(buf, buf_len-1, fmt, arg);
#endif
  buf[buf_len-1] = 0;
  return res;
}
