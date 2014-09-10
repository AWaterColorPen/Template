#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long LL ;
struct MATRIX {
	static const int M = 2 ;
	int n;
	LL a[M][M];
	MATRIX () {}
	MATRIX (int n) : n(n) {}
	MATRIX operator * (const MATRIX &o) const {
		MATRIX  ret(n);
		memset(ret.a, 0, sizeof(ret.a));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++)
					ret.a[i][j] = (ret.a[i][j] + a[i][k] * o.a[k][j]) % MOD;
		return ret;
	}
}	g, gn, U;
