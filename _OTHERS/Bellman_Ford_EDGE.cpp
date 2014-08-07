#include <iostream>
#include <cstring>
#include <cstdio>
#define INF 502
#define inf 0x0f0f0f0f

using namespace std;
struct EDGE {
	int i, j, d;
}	Edge[INF<<4];
int Dis[INF]; bool vis[INF];
void _addedge(int i, int j, int d, EDGE &e) { e.i=i, e.j=j, e.d=d; }
bool Bellman_Ford(int n, int edge)
{
	int i, k, s;
	for (memset(vis, true, sizeof(vis)), s=1; s<=n; s++)
		if (vis[s]) {
			for (memset(Dis, 0x0f, sizeof(Dis)), Dis[s]=0, k=1; k<n; k++)
				for (i=1; i<=edge; i++)
					Dis[Edge[i].i]=min(Dis[Edge[i].i], Dis[Edge[i].j]+Edge[i].d);
			for (i=1; i<=edge; i++)
				if (Dis[Edge[i].i]>Dis[Edge[i].j]+Edge[i].d)
					return true;
			for (i=1; i<=n; i++)
				if (Dis[i]<inf) vis[i]=false;
		}
	return false;
}
