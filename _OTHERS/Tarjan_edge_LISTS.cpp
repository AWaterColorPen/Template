#include <iostream>
#include <cstdio>
#define INF 205

using namespace std;
struct EDGE {
	int i; bool vis; EDGE *next,*ani;
}	*Edge[INF], E[INF<<2];
int Low[INF], Dfn[INF], Stack[INF], Blo[INF], Con[INF], Ans[INF];
int Block, Brige, Cnt, Now;
bool Instack[INF];
void _addedge(int i, int j, EDGE &e1, EDGE &e2)
{
	e1.i=j, e1.vis=true, e1.ani=&e2, e1.next=Edge[i], Edge[i]=&e1;
	e2.i=i, e2.vis=true, e2.ani=&e1, e2.next=Edge[j], Edge[j]=&e2;
}
void Tarjan_edge(int n)
{
	int i;
	Dfn[n]=Low[n]=++Cnt, Instack[Stack[++Now]=n]=true;
	for (EDGE *p=Edge[n]; p; p=p->next)
		if (p->vis) {
			if (p->ani->vis=false, Dfn[i=p->i]==0) {
				Tarjan_edge(i), Low[n]=min(Low[n], Low[i]);
				if (Dfn[n]<Low[i]) Brige++;
			}
			else	if (Instack[i]) Low[n]=min(Low[n], Low[i]);
		}
	if (Dfn[n]==Low[n] && ++Block)
		do Blo[i=Stack[Now--]]=Block, Instack[i]=false;
		while (i!=n);
}
