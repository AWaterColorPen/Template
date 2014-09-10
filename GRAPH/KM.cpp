#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define INF 405
#define inf 0x0f0f0f0f

using namespace std;

const int NN = 405;
const int inf = 0x0f0f0f0f;

int sx[NN], sy[NN];
int mth[NN], w[NN][NN], lx[NN], ly[NN], n, m; //n：左集元素个数； m：右集元素个数
void init() { memset(w, 0, sizeof(w)); } //不一定要，求最小值一般要初始化为负无穷！
int dfs(int u)
{
	sx[u] = 1;
	for (int v = 1; v <= m; v++)
		if (!sy[v] && lx[u] + ly[v] == w[u][v])
			if (sy[v] = 1, mth[v] == 0 || dfs(mth[v]))
				return mth[v] = u, 1;
	return 0;
}
int KM()
{
	int i, j, k, sum=0;
	memset(ly, 0, sizeof(ly)); 
	memset(mth, 0, sizeof(mth));
	for (int i = 1; i <= n; i++)
	{
		lx[i] = -inf;
		for (int j = 1; j <= m; j++)
			if (lx[i] < w[i][j]) lx[i] = w[i][j];
	}
	for (int i = 1; i <= n; i++)
		while (1)
		{
			memset(sx, 0 sizeof(sx));
			memset(sy, 0, sizeof(sy));
			if (dfs(i)) break;
			int d = inf;
			for (int j = 1; j <= n; j++)
				for (int k = 1; sx[j] && k <= m; k++)
					if (!sy[k])
						d = min(d, lx[j] + ly[k] - w[j][k]);
			if (d == inf) return -1;
			for (int j = 1; j <= n; j++) if (sx[j]) lx[j] -= d;
			for (int j = 1; j <= m; j++) if (sy[j]) ly[j] += d;
		}
	for (int i = 1; i <= m; i++)
		if (mth[i])
			sum += w[mth[i]][i];
	return sum;
}
