#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
struct Romberg {
	double T[2][4] , F[4];
	Romberg () { F[0]=1 ,F[1]=4, F[2]=16, F[3]=64; }
	double fn(double x) { return 1.0/x ; }
	double sigma(double h, double a, int n)
	{
		double sum=0;
		for (int i=0; i<n; i++)
			sum+=fn(a + (2 * i + 1) * h) ;
		return sum*h;
	}
	double count(double a, double b, double eps)
	{
		double h=b - a;
		T[0][0]=h/2 * (fn(a)+fn(b));
		for (int t=0, _t=1, i=1; true; t=1^t, _t=1^t, i++, h/=2)
		{
			T[t][0]=T[_t][0]/2 + sigma(h/2, a, 1<<(i - 1)) ;
			for (int j=1; j<=min(i, 3); j++)
				T[t][j]=(T[t][j-1] * F[j] - T[_t][j-1]) / (F[j] - 1) ;
			if (i>=4 && abs(T[t][3]-T[_t][3])<=eps) return T[t][3];
		}
	}
};
