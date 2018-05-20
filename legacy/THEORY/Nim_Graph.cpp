#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

struct GRAGH_NIM {
	static const int M = 105 ;
	vector <int> vec[M];
	int sg[M], vis[M];
	void clear()
	{
		for (int i = 0; i < M; i++) vec[i].clear();
		memset(vis, 0, sizeof(vis));
		memset(sg, 0, sizeof(sg));
	}
	void _addedge(int i, int j) { vec[i].push_back(j); vec[j].push_back(i); }
	void dfs(int n)
	{
		vis[n] = 1;
		for (int i = 0; i < vec[n].size(); i++)
			if (vis[vec[n][i]] == 0)
			{
				dfs(vec[n][i]);
				sg[n] ^= (1 + sg[vec[n][i]]);
			}
	}
}	gnim;

const int NN = 105;

struct EDGE {
	int i, v;
	EDGE *next,*ani;
	EDGE() {}
	EDGE(int i, int v, EDGE *next, EDGE *ani) : i(i), v(v), next(next), ani(ani) {}
}	*Edge[NN], E[NN << 4];

void _addedge(int i, int j, EDGE &e1, EDGE &e2)
{
	e1 = EDGE(j, 1, Edge[i], &e2); Edge[i] = &e1;
	e2 = EDGE(i, 1, Edge[j], &e1); Edge[j] = &e2;
}

int dfn[NN], low[NN], stk[NN], blo[NN], Block, Cnt, Now;
int ins[NN];

void tarjan(int n)
{
	int i;
	low[n] = dfn[n] = ++Cnt, ins[stk[++Now] = n] = 1;
	for (EDGE *p = Edge[n]; p; p = p->next)
		if (p->v) {
			p->ani->v = 0;
			if (dfn[i = p->i] == 0) tarjan(i), low[n] = min(low[n], low[i]);
			else if (ins[i]) low[n] = min(low[n], low[i]);
		}
	if (dfn[n] == low[n] && ++Block)
		do blo[i = stk[Now--]] = Block, ins[i] = 0;
		while (i != n);
}

int CNTE[INF];

void make_gragh(int n)
{
	memset(CNTE, 0, sizeof(CNTE));
	for (int i = 1; i <= n; i++)
		for (EDGE *p = Edge[i]; p; p = p->next)
		{
		    if (Blo[i] < Blo[p->i]) gnim._addedge(Blo[i], Blo[p->i]);
			if (Blo[i] == Blo[p->i] && p->vis) CNTE[Blo[i]]++;
		}
	for (int i = 1, m = Block; i <= m; i++) if (CNTE[i] > 1 && CNTE[i] & 1) gnim._addedge(i, ++Block);
}