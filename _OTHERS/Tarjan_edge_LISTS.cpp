#include <iostream>
#include <cstdio>
#define INF 205

using namespace std;
struct EDGE {
	int i; bool vis; EDGE *next,*ani;
}	*Edge[INF], E[INF<<2];

void _addedge(int i, int j, EDGE &e1, EDGE &e2)
{
	e1.i=j, e1.vis=1, e1.ani=&e2, e1.next=Edge[i], Edge[i]=&e1;
	e2.i=i, e2.vis=1, e2.ani=&e1, e2.next=Edge[j], Edge[j]=&e2;
}
int dfn[INF], low[INF], stk[INF], blo[INF], Block, Cnt, Now;
int ins[INF];
int brige;

void tarjan(int n)
{
	int i;
	low[n] = dfn[n] = ++Cnt, ins[stk[++Now] = n] = 1;
	for (EDGE *p = Edge[n]; p; p = p->next)
		if (p->vis) {
			p->ani->vis = 0;
			if (dfn[i = p->i]) {
				tarjan(i), low[n] = min(low[n], low[i]);
				if (dfn[n] < low[i]) brige++;
			}
			else if (ins[i]) low[n] = min(low[n], low[i]);
		}
	if (dfn[n] == low[n] && ++Block)
		do blo[i = stk[Now--]] = Block, ins[i] = 0;
		while (i != n);
}

