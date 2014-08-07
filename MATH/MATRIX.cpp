#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define _int64 long long

using namespace std;
struct MATRIX {
	static const int M = 2 ;
	_int64 a[M][M];
	int n, m;
	void read(int x, int y) { n=x, m=y; }
	MATRIX operator * (const MATRIX &o) const {
		MATRIX  ret;
		memset(ret.a, 0, sizeof(ret.a));
		for (int i=0; i<n; i++)
			for (int j=0; j<o.m; j++)
				for (int k=0; k<o.n; k++)
					ret.a[i][j]=(ret.a[i][j] + a[i][k] * o.a[k][j]) % MOD;
		return ret.read(n, o.m), ret;
	}
}	g, gn, U;
