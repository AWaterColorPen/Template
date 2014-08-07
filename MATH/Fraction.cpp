#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cmath>
#define _int64 long long 

using namespace std;

int sgn(double a, double eps=1e-8) { return (a<-eps)?-1:(a>eps); }
_int64 GCD(_int64 a, _int64 b) { for (_int64 t; b; t=a%b, a=b, b=t); return a; }
const double eps = 1e-8 ;
struct FRACTION {
	_int64 num, den;
	FRACTION (_int64 num=0, _int64 den=1)
	{
		if (den<0) num=-num, den=-den;
		_int64 gcd=GCD(abs(num), den);
		this->num=num/gcd;
		this->den=den/gcd;
	}
	FRACTION operator + (const FRACTION &o) const { return FRACTION( num*o.den + den*o.num, den*o.den); }
	FRACTION operator - (const FRACTION &o) const { return FRACTION( num*o.den - den*o.num, den*o.den); }
	FRACTION operator * (const FRACTION &o) const { return FRACTION( num*o.num, den*o.den); }
	FRACTION operator / (const FRACTION &o) const { return FRACTION( num*o.den, den*o.num); }
	bool operator < (const FRACTION &o) const { return num*o.den < den*o.num; }
	bool operator == (const FRACTION &o) const { return num*o.den == den*o.num; }
}	;