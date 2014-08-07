#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#define M 105
#define _int64 long long

using namespace std;
struct NIM_MUL {
	static const int M = 105 ;
	_int64 pow2[10], sg[M][M];
	int vis[M*M];
	_int64 _SG(int x, int y)
	{
		memset(vis, 0, sizeof(vis));
		for (int i=1; i<x; i++)
			for (int j=1; j<y; j++)
			    vis[sg[i][y]^sg[x][j]^sg[i][j]]=1;
		for (int i=1; i<x; i++) vis[sg[i][y]]=1;
		for (int j=1; j<y; j++) vis[sg[x][j]]=1;
		vis[sg[0][0]]=1;
		for (int i=0; i<M*M; i++) if (vis[i]==0) return i;
	}
	void pre_sg()
	{
		pow2[0] = 2;
		for (int i=1; i<=6; i++) pow2[i]=pow2[i-1]*pow2[i-1];
		for (int i=1; i<=16; i++)
			for (int j=1; j<=16; j++) sg[i][j]=_SG(i, j);
	}
	_int64 nim_mul_pow(_int64 x, _int64 y)
	{
		if (x<=16) return sg[x][y];
		_int64 m;
		for (int i=0; x>=pow2[i]; i++) m=pow2[i];
		_int64 p=x/m, s=y/m, t=y%m;
		_int64 d1=nim_mul_pow(p, s), d2=nim_mul_pow(p, t);
		return (m*(d1^d2))^nim_mul_pow(m/2, d1);
	}
	_int64 nim_mul(_int64 x, _int64 y)
	{
		if (x<y) return nim_mul(y, x);
		if (x<=16) return sg[x][y];
		_int64 m;
		for (int i=0; x>=pow2[i]; i++) m=pow2[i];
		_int64 p=x/m, q=x%m, s=y/m, t=y%m;
		_int64 c1=nim_mul(p, s);
		_int64 c2=nim_mul(p, t)^nim_mul(q, s);
		_int64 c3=nim_mul(q, t);
		return ((c1^c2)*m)^c3^nim_mul_pow(m/2, c1);
	}
}	nim2;