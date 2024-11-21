#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#ifndef _DCOMPLEX_DECLARE_T_
typedef struct DCOMPLEX {double r,i;} dcomplex;
#define _DCOMPLEX_DECLARE_T_
#endif /* _DCOMPLEX_DECLARE_T_ */


dcomplex Cadd(dcomplex a, dcomplex b);
dcomplex Csub(dcomplex a, dcomplex b);
dcomplex Cmul(dcomplex a, dcomplex b);
dcomplex Cmul3(dcomplex a, dcomplex b, dcomplex c);
dcomplex Complex(double re, double im);
dcomplex Conjg(dcomplex z);
dcomplex Cdiv(dcomplex a, dcomplex b);
double Cabs(dcomplex z);
double CSqr(dcomplex z);
dcomplex Csqrt(dcomplex z);
dcomplex RCmul(double x, dcomplex a);

#endif /* _COMPLEX_H_ */
