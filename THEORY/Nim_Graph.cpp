#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#define INF 105

using namespace std;
struct EDGE {
	int i, vis; EDGE *next,*ani;
}	*Edge[INF], E[INF<<4];
struct GRAGH_NIM {
	static const int M = 105 ;
	vector <int> vec[M];
	int sg[M], vis[M];
	void clear()
	{
		for (int i=0; i<M; i++) vec[i].clear();
		memset(vis, 0, sizeof(vis));
		memset(sg, 0, sizeof(sg));
	}
	void _addedge(int i, int j) { vec[i].push_back(j); vec[j].push_back(i); }
	void dfs(int n)
	{
		vis[n]=1;
		for (int i=0; i<vec[n].size(); i++)
			if (vis[vec[n][i]]==0)
				dfs(vec[n][i]), sg[n]^=(1+sg[vec[n][i]]);
	}
}	gnim;

void _addedge(int i, int j, EDGE &e1, EDGE &e2)
{
	e1.i=j, e1.vis=1, e1.ani=&e2, e1.next=Edge[i], Edge[i]=&e1;
	e2.i=i, e2.vis=1, e2.ani=&e1, e2.next=Edge[j], Edge[j]=&e2;
}

int Low[INF], Dfn[INF], Stack[INF], Blo[INF];
int Block, Cnt, Now;
bool Instack[INF];
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