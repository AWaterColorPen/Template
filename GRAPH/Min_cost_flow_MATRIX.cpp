#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#define INF 105
#define inf 0x0f0f0f0f

using namespace std;
int Cost[INF][INF], Path[INF], cap[INF][INF];
int Dis[INF], Inq[INF];
void _addedge(int i, int j, int c, int d)
{
	cap[i][j]=c, Cost[i][j]=d, cap[j][i]=0, Cost[j][i]=-d;
}
int SPFA(int s, int end)
{
	int i, j; queue <int> q;
	memset(Dis, 0x0f, sizeof(Dis));
	memset(Inq, 0, sizeof(Inq));
	for (Dis[s]=Inq[s]=0, q.push(s);!q.empty();)
	{
		i=q.front(), q.pop(), Inq[i] = 0;
		for (j=0; j<=end; j++)
			if (cap[i][j] && Dis[j]>Dis[i]+Cost[i][j])
				if (Path[j] = i, Dis[j] = Dis[i]+Cost[i][j], Inq[j]==0)
					Inq[j] = 1, q.push(j);
	}
	return (Dis[end] < inf);
}
int Min_cost_flow(int s, int end)
{
	int i, cost=0, flow;
	while (SPFA(s, end))
	{
		for (flow=inf, i=end; i!=s; i=Path[i])
			flow = min(flow, cap[Path[i]][i]);
		for (cost+=flow*Dis[end], i=end; i!=s; i=Path[i])
			cap[Path[i]][i] -= flow, cap[i][Path[i]] += flow;
	}
	return cost;
}
