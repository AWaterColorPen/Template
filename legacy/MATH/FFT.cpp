#include <algorithm>
#include <iostream>
#include <cstring>
#include <complex>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

const int M = 70005;

const long double PI = acos(-1);
typedef long long LL;
//typedef complex <double> CPX ;

struct CPX
{
	double x, y;
	CPX (double x = 0, double y = 0) : x(x), y(y) {}
	CPX operator + (const CPX &o) const { return CPX(x + o.x, y + o.y); }
	CPX operator - (const CPX &o) const { return CPX(x - o.x, y - o.y); }
	CPX operator * (const CPX &o) const { return CPX(x * o.x - y * o.y, x * o.y + y * o.x); }
}	;

void _FFT(vector <CPX> &A, int op) //慢一点，但是误差更小
{
	int n = A.size();
	for(int i = 0, j = 0, k; i < n; i++)
	{
		if (j > i) swap(A[i], A[j]);
		for (k = n; j & (k >>= 1); j &= (~k)) ;
		j |= k;
	}
	double pi = PI * op;
	for(int m = 1; m < n; m <<= 1)
		for(int i = 0; i < m; i++)
		{
			CPX tmp(cos(pi / m * i), sin(pi / m * i));
			for(int j = i; j < n; j += (m << 1))
			{
				CPX t = tmp * A[j + m];
				A[j + m] = A[j] - t, A[j] = A[j] + t;
			}
		}
	if (op == -1) for(int i = 0; i < n; i++) A[i].x /= n;
}

void FFT(vector <CPX> &A, int op)
{
	int n = A.size();
	for(int i = 0, j = 0, k; i < n; i++)
	{
		if (j > i) swap(A[i], A[j]);
		for (k = n; j & (k >>= 1); j &= (~k)) ;
		j |= k;
	}
	double pi = PI * op;
	for(int m = 1; m < n; m <<= 1)
	{
		CPX tmp(cos(pi / m), sin(pi / m));
		for(int i = 0; i < n; i += (m << 1))
		{
			CPX w(1, 0);
			for(int j = i; j < i + m; j++)
			{
				CPX t = w * A[j + m];
				A[j + m] = A[j] - t, A[j] = A[j] + t;
				w = w * tmp;
			} 
		}
	}
	if (op == -1) for(int i = 0; i < n; i++) A[i].x /= n;
}

void CMUL(LL a[], int len1, LL b[], int len2, LL ans[])
{
	int len = 1;
	while (len < (len1 + len2)) len <<= 1;
	vector <CPX> X(len, 0), Z(len, 0);
	
	for (int i = 0; i < len1; i++) Z[i].x = a[i];
	for (int i = 0; i < len2; i++) X[i].x = b[i];

	FFT(X, 1), FFT(Z, 1);

	for (int i = 0; i < len; i++) Z[i] = Z[i] * X[i];

	FFT(Z, -1);
	for (int i = 0; i < len; i++) ans[i] = Z[i].x + 0.5;
}

