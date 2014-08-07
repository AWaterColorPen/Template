#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define INF 305
#define inf 0x0f0f0f0f

using namespace std;
int cap[INF][INF], Dfn[INF], Wage[INF];
void _addedge(int i, int j, int c) { cap[i][j]+=c, cap[j][i]+=c; }
int Stoer_Wagner(int n)
{
	int mincut=inf, now, i, j, t;
	for (i=1; i<=n; i++) Dfn[i]=i;
	for (; n>1; n--)
	{
		memset(Wage, 0, sizeof(Wage));
		for (i=1; i<=n; i++, swap(Dfn[i], Dfn[now]))
			for (now=j=i+1; j<=n; j++)
				if (t=Dfn[j], Wage[t]+=cap[Dfn[i]][t], Wage[Dfn[now]]<Wage[t])
					now=j;
		mincut=min(mincut, Wage[Dfn[n]]);
		for (i=1; i<=n-1; i++)
			now=cap[Dfn[i]][Dfn[n]], cap[Dfn[i]][Dfn[n-1]]+=now, cap[Dfn[n-1]][Dfn[i]]+=now;
	}
	return mincut;
}
