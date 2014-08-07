#include <iostream>
#include <cstring>
#include <cstdio>
#define INF 10005

using namespace std;
struct EDGE {
	int i; EDGE *next;
} *Edge[INF], E[INF*INF];
int Dfn[INF], Low[INF], Blo[INF], Cnt, Cut;
bool vis[INF];
void _addedge(int i, int j, EDGE &e) { e.i=j,e.next=Edge[i], Edge[i]=&e; }
void Tarjan_point(int n)
{
	int i;
	Dfn[n]=Low[n]=++Cnt;
	for (EDGE *p=Edge[n]; p; p=p->next)
		 if (Dfn[i=p->i]==0) {
			Tarjan_point(i), Low[n]=min(Low[n], Low[i]);
			if (Dfn[n]<=Low[i]) Blo[n]++;
		}
		else Low[n]=min(Low[n], Dfn[i]);
}
