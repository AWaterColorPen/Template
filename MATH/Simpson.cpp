#include <bits/stdc++.h>

using namespace std;

struct SIMPSON {
	double f(double x);
	double simpson(double a, double b)
	{
		auto c = (a + b) / 2;
		return (f(a) + f(c) * 4 + f(b)) * (b - a) / 6;
	}

	double asr(double a, double b, double ep, double s)
	{
		auto c = (a + b) / 2;
		auto s1 = simpson(a, c), s2 = simpson(c, b);
		if (fabs(s1 + s2 - s) < ep) return s1 + s2;
		return asr(a, c, ep / 2, s1) + asr(c, b, ep / 2, s2);
	}

	double asr(double a, double b, double ep)
	{
		return asr(a, b, ep, simpson(a, b));
	}
}	sps;
