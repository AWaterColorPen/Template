#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const double eps = 1e-8 ;
int sgn(double x) { return (x < -eps) ? -1 : (x > eps) ; }

struct SIMPLEX {
	static const int ANS_NO = 0, ANS_OK = 1, ANS_INF = 2, M = 805 ;
	double A[M][M], b[M], c[M], OC[M];
	int N[M], B[M], n, m;
	double v, x[M];

	void clear()
	{
		memset(A, 0, sizeof(A));
		memset(c, 0, sizeof(c));
		memset(b, 0, sizeof(b));
	}

	void pivot(int l, int e)
	{
		int x, y;
		b[e] = b[l] / A[l][e];
		A[e][l] = 1.0 / A[l][e];
		for (int i = 1; i <= n; i++) if (y = N[i], y != e) A[e][y] = A[l][y] / A[l][e];

		for (int j = 1; j <= m; j++)
			if (x = B[j], x != l)
			{
				b[x] = b[x] - A[x][e] * b[e];
				for (int i = 1; i <= n; i++) if (y = N[i], y != e) A[x][y] = A[x][y] - A[e][y] * A[x][e];
				A[x][l] = -A[x][e] * A[e][l];
			}

		v += b[e] * c[e];
		c[l] = - A[e][l] * c[e];
		for (int i = 1; i <= n; i++) if (y = N[i], y != e) c[y] = c[y] - A[e][y] * c[e];

		for (int i = 1; i <= n; i++) if (N[i] == e) N[i] = l;
		for (int j = 1; j <= m; j++) if (B[j] == l) B[j] = e;
	}

	int opt()
	{
		for (int l = 0, e = 0, i, j, x, y, tl; 1; )
		{
			for (i = 1; i <= n; i++) if (sgn(c[N[i]]) == 1) break;
			if (i > n) return ANS_OK;

			double best = -1e30;
			for (i = 1; i <= n; i++)
				if (y = N[i], sgn(c[y]) == 1)
				{
					double now = 1e30, tmp;
					for (j = 1; j <= m; j++)
						if (x = B[j], sgn(A[x][y]) == 1)
						{
							tmp = b[x] / A[x][y];
							if (now > tmp || (now == tmp && tl > x)) now = tmp, tl = x;
						}
					if ((now * c[N[i]] > best) || (now * c[N[i]] >= best - eps && y < e))
						best = now * c[N[i]], l = tl, e = y;
				}
			if (best <= -1e29) return ANS_INF;
			pivot(l, e);
		}
	}

	void delete0()
	{
		int i, j;
		for (j = 1; j <= m; j++) if (B[j] == 0) break;
		if (j <= m)
		{
			for (i = 1; i <= n; i++) if (sgn(A[0][N[i]])) break;
			pivot(0, N[i]);
		}
		for (i = 1; i <= n && N[i]; i++) ;
		for (n--; i <= n; i++) N[i] = N[i+1];
	}

	int init()
	{
		int x, y, l = 0;
		for (int i = 1; i <= n; i++) N[i] = i;
		for (int j = 1; j <= m; j++) B[j] = n + j;
		v = 0;

		for (int j = 1; j <= m; j++) if (l == 0 || b[B[j]] < b[l]) l = B[j];
		if (sgn(b[l]) >= 0) return ANS_OK;

		memcpy(OC, c, sizeof(OC));
		memset(c, 0, sizeof(c));
		c[0] = -1; N[++n] = 0;
		for (int j = 1; j <= m; j++) A[B[j]][0] = -1;

		if (pivot(l, 0), opt(), sgn(v) < 0) return ANS_NO;
		delete0();
		memcpy(c, OC, sizeof(c));

		for (int j = 1; j <= m; j++)
			if (x = B[j], sgn(c[x]))
			{
				v += c[x] * b[x];
				for (int i = 1; i <= n; i++) y = N[i], c[y] -= A[x][y] * c[x];
				c[x] = 0;
			}
		return ANS_OK;
	}

	double simplex()
	{
		init();
		opt();
		return v;
		for (int j = 1; j <= m; j++) x[B[j]] = b[B[j]];
		//for (int i = 1; i <= n; i++) printf("x[%d] = %.2f\n", i, x[i]);
		//for (int i = 1; i <= n; i++) printf("%.3f%c", x[i], i==n?'\n':' ');
		return ANS_OK;
	}
}	slx;
