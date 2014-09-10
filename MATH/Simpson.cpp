#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

struct SIMPSON {
	double f(double x) { return x * x; }
	double simpson(double a, double b) 
	{
		double c = (a + b) / 2;
		return (f(a) + f(c) * 4 + f(b)) * (b - a) / 6;
	}
	double asr(double a, double b, double ep, double A) 
	{
		double c = (a + b) / 2;
		double L = simpson(a, c), R = simpson(c, b);
		if (fabs(L + R - A) < ep) return L + R;
		return asr(a, c, ep / 2, L) + asr(c, b, ep / 2, R);
	}
	double asr(double a, double b, double ep)
	{
		return asr(a, b, ep, simpson(a, b));
	}
}	sps;
