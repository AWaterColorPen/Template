#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long LL;
struct NIM_MUL {
	static const int M = 105 ;
	LL pow2[10], sg[M][M];
	int vis[M * M];
	LL _SG(int x, int y)
	{
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i < x; i++)
			for (int j = 1; j < y; j++)
			    vis[sg[i][y] ^ sg[x][j] ^ sg[i][j]] = 1;
		for (int i = 1; i < x; i++) vis[sg[i][y]] = 1;
		for (int j = 1; j < y; j++) vis[sg[x][j]] = 1;
		vis[sg[0][0]] = 1;
		for (int i = 0; i < M * M; i++) if (vis[i] == 0) return i;
	}
	void pre_sg()
	{
		pow2[0] = 2;
		for (int i = 1; i <= 6; i++) pow2[i] = pow2[i - 1] * pow2[i - 1];
		for (int i = 1; i <= 16; i++)
			for (int j = 1; j <= 16; j++)
				sg[i][j] = _SG(i, j);
	}
	LL nim_mul_pow(LL x, LL y)
	{
		if (x <= 16) return sg[x][y];
		LL m;
		for (int i = 0; x >= pow2[i]; i++) m = pow2[i];
		LL p = x / m, s = y / m, t = y % m;
		LL d1 = nim_mul_pow(p, s);
		LL d2 = nim_mul_pow(p, t);
		return (m * (d1 ^ d2)) ^ nim_mul_pow(m / 2, d1);
	}
	LL nim_mul(LL x, LL y)
	{
		if (x < y) return nim_mul(y, x);
		if (x <= 16) return sg[x][y];
		LL m;
		for (int i = 0; x >= pow2[i]; i++) m = pow2[i];
		LL p = x / m, q = x % m, s = y / m, t = y % m;
		LL c1 = nim_mul(p, s);
		LL c2 = nim_mul(p, t)^nim_mul(q, s);
		LL c3 = nim_mul(q, t);
		return ((c1 ^ c2) * m) ^ c3 ^ nim_mul_pow(m / 2, c1);
	}
}	nim2;