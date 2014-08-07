#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define INF 405
#define inf 0x0f0f0f0f

using namespace std;

int sx[INF], sy[INF];
int match[INF], w[INF][INF], lx[INF], ly[INF], n, m; //n：左集元素个数； m：右集元素个数
void init() { memset(w, 0, sizeof(w)); } //不一定要，求最小值一般要初始化为负无穷！
int dfs(int u)
{
	int v; sx[u]=1;
	for (v=1; v<=m; v++)
		if (!sy[v] && lx[u]+ly[v]==w[u][v])
			if (sy[v]=1, match[v]==0 || dfs(match[v]))
				return match[v]=u, 1;
	return 0;
}
int KM()
{
	int i, j, k, sum=0;
	memset(ly, 0, sizeof(ly)); 
	memset(match, 0, sizeof(match));
	for (i=1; i<=n; i++)
		for (lx[i]=-inf, j=1; j<=m; j++)
			if (lx[i]<w[i][j]) lx[i]=w[i][j];
	for (i=1; i<=n; i++)
		while ( true )
		{
			memset(sx, 0 sizeof(sx));
			memset(sy, 0, sizeof(sy));
			if (dfs(i)) break;
			int d=inf;
			for (j=1; j<=n; j++)
				for (k=1; sx[j] && k<=m; k++)
					if (!sy[k])
						d=min(d, lx[j]+ly[k]-w[j][k]);
			if (d==inf) return -1;
			for (j=1; j<=n; j++) if (sx[j]) lx[j]-=d;
			for (j=1; j<=m; j++) if (sy[j]) ly[j]+=d;
		}
	for (i=1; i<=m; i++)
		if (match[i])
			sum+=w[match[i]][i];
	return sum;
}
