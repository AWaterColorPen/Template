#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cmath>

using namespace std;

typedef long long LL;
const double eps = 1e-8 ;
int sgn(double x) { return (x < -eps) ? -1 : (x > eps) ; }

LL GCD(LL a, LL b) { for (LL t; b; t = a % b, a = b, b = t) ; return a; }
struct FRACTION {
	LL num, den;
	FRACTION (LL num = 0, LL den = 1)
	{
		if (den < 0) num = -num, den = -den;
		LL gcd = GCD(abs(num), den);
		this->num = num / gcd;
		this->den = den / gcd;
	}
	FRACTION operator + (const FRACTION &o) const { return FRACTION( num * o.den + den * o.num, den * o.den); }
	FRACTION operator - (const FRACTION &o) const { return FRACTION( num * o.den - den * o.num, den * o.den); }
	FRACTION operator * (const FRACTION &o) const { return FRACTION( num * o.num, den * o.den); }
	FRACTION operator / (const FRACTION &o) const { return FRACTION( num * o.den, den * o.num); }
	bool operator < (const FRACTION &o) const { return num * o.den < den * o.num; }
	bool operator == (const FRACTION &o) const { return num * o.den == den * o.num; }
}	;