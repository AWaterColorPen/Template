#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#define INF 40005

using namespace std;
vector <int> vec[INF], dis[INF];
int P[INF][17], Dis[INF], Lv[INF], Bin[INF];
bool vis[INF];
void _addedge(int i, int j, int d) { vec[i].push_back(j), dis[i].push_back(d); }
int Dfs(int n, int fath, int d, int l)
{
	int i, j, siz=vec[n].size(), lv=l;
	for (P[n][0]=fath, Dis[n]=d, Lv[n]=l, i=vis[n]=0; i<siz; i++)
		if (vis[j=vec[n][i]])
			lv=max(lv, Dfs(j, n, d+dis[n][i], l+1));
	return lv;
}
void Pre_RMQ_LCA(int n)
{
	int i, j, level;
	for (Bin[0]=i=1; i<17; i++) Bin[i]=Bin[i-1]<<1;
	memset(vis, true, sizeof(vis)), memset(P, 0xff, sizeof(P));
	level=Dfs(1, -1, 0, 1);
	for (i=1; Bin[i]<=level; i++)
		for (j=1; j<=n; j++)
			if (P[j][i-1]!=-1)
				P[j][i]=P[P[j][i-1]][i-1];
}
int RMQ_LCA(int x, int y)
{
	int i, log;
	if (Lv[x]<Lv[y]) swap(x, y);
	for (log=0; Bin[log]<=Lv[x]; log++) ;
	for (i=--log; i>=0; i--)
		if (Lv[x]-Bin[i]>=Lv[y])
			x=P[x][i];
	if (x==y) return x;
	for (i=log; i>=0; i--)
		if (P[x][i]!=-1 && P[x][i]!=P[y][i])
			x=P[x][i], y=P[y][i];
	return P[x][0];
}
