#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#define INF 105

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

struct EDGE {
	int i, vis; EDGE *next,*ani;
}	*Edge[INF], E[INF<<4];

void _addedge(int i, int j, EDGE &e1, EDGE &e2)
{
	e1.i=j, e1.vis=1, e1.ani=&e2, e1.next=Edge[i], Edge[i]=&e1;
	e2.i=i, e2.vis=1, e2.ani=&e1, e2.next=Edge[j], Edge[j]=&e2;
}

int dfn[INF], low[INF], stk[INF], blo[INF], Block, Cnt, Now;
int ins[INF];

void tarjan(int n)
{
	int i, j;
	low[n] = dfn[n] = ++Cnt, ins[stk[++Now] = n] = 1;
	for (i = 0; i < vv[n].size(); i++)
		if (dfn[j = vv[n][i]] == 0)
			tarjan(j), low[n] = min(low[n], low[j]);
		else if (ins[j]) low[n] = min(low[n], low[j]);
	if (dfn[n] == low[n] && ++Block)
		do blo[i = stk[Now--]] = Block, ins[i] = 0;
		while (i != n);
}

void Tarjan_edge(int n)
{
	int i;
	Dfn[n]=Low[n]=++Cnt, Instack[Stack[++Now]=n]=1;
	for (EDGE *p=Edge[n]; p; p=p->next)
		if (p->vis) {
			if (p->ani->vis=0, Dfn[i=p->i]==0)
				Tarjan_edge(i), Low[n]=min(Low[n], Low[i]);
			else	if (Instack[i]) Low[n]=min(Low[n], Low[i]);
		}
	if (Dfn[n]==Low[n] && ++Block)
		do Blo[i=Stack[Now--]]=Block, Instack[i]=false;
		while (i!=n);
}
int CNTE[INF];
void make_gragh(int n)
{
	memset(CNTE, 0, sizeof(CNTE));
	for (int i=1; i<=n; i++)
		for (EDGE *p=Edge[i]; p; p=p->next)
		{
		    if (Blo[i]<Blo[p->i]) gnim._addedge(Blo[i], Blo[p->i]);
			if (Blo[i]==Blo[p->i] && p->vis) CNTE[Blo[i]]++;
		}
	for (int i=1, m=Block; i<=m; i++) if (CNTE[i]>1 && CNTE[i]&1) gnim._addedge(i, ++Block);
}