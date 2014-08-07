#include <algorithm>
#include <iostream>
#include <cstdio>
#define INF 105

using namespace std;
struct EDGE {
	int i, j, w;
}	E[INF*INF>>1];
int F[INF];
bool cmp(EDGE a, EDGE b) {
	return a.w<b.w;
}
void _addedge(int i, int j, int w, EDGE &e) { e.i=i, e.j=j, e.w=w; }
int Find(int n)
{
	if (F[n]==n) return n;
	return F[n]=Find(F[n]);
}
int Kruskal(int n, int edge)
{
	int i, cnt=1, cost=0;
	sort(E+1, E+edge+1, cmp);
	for (i=1; i<=n; i++) F[i]=i;
	for (i=1; i<=edge && cnt<n; i++)
		if (Find(E[i].i)!=Find(E[i].j))
			F[F[E[i].i]]=F[E[i].j], cnt++, cost+=Edge[i].w;
	if (cnt<n) return -1;
	return cost;
}
