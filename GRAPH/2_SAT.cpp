#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#define INF 105
#define inf 0x0f0f0f0f

using namespace std;

vector <int> vec[INF];
void _addedge(int x, int y) { vec[x].push_back(y) ; }

int dfn[INF], low[INF], stk[INF], blo[INF], Block, Cnt, Now;
int ins[INF];

void tarjan(int n)
{
	int i, j;
	low[n] = dfn[n] = ++Cnt, ins[stk[++Now] = n] = 1;
	for (i=0; i< vv[n].size(); i++)
		if (dfn[j = vv[n][i]] == 0)
			tarjan(j), low[n] = min(low[n], low[j]);
		else	if (ins[j]) low[n] = min(low[n], low[j]);
	if (dfn[n] == low[n] && ++Block)
		do blo[i = stk[Now--]] = Block, ins[i] = 0;
		while (i != n);
}

vector <int> node[INF];
int Match[INF], Ind[INF];
int vis[INF];

void Top_sort(int n)
{
	queue <int> q; int i, j, t, siz;
	memset(vis, 0xff, sizeof(vis));
	for (i=1; i<=n; i++)
		Match[Blo[i]]=Blo[i+n], Match[Blo[i+n]]=Blo[i];
	for (i=1; i<=n*2; i++)
		for (j=0, siz=vec[i].size(); j<siz; j++)
			if (Blo[i]!=Blo[t=vec[i][j]])
				node[Blo[t]].push_back(Blo[i]), Ind[Blo[i]]++;
	for (i=1; i<=Block; i++)
		if (Ind[i]==0) q.push(i);
	while (!q.empty()) {
		if (i=q.front(), q.pop(), vis[i]==-1)
			vis[i]=1, vis[Match[i]]=0;
		for (j=0, siz=node[i].size(); j<siz; j++)
			if (--Ind[t=node[i][j]]==0)
				q.push(t);
	}
}
