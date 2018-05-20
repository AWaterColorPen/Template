#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;

const int NN = 105;
const int inf = 0x0f0f0f0f;

int Cost[NN][NN], Path[NN], cap[NN][NN];

void _addedge(int i, int j, int c, int d)
{
	cap[i][j] = c, Cost[i][j] = d, cap[j][i] = 0, Cost[j][i] = -d;
}

int ds[NN], inq[NN];
int SPFA(int s, int end)
{
	queue <int> q;
	memset(ds, 0x0f, sizeof(ds));
	memset(inq, 0, sizeof(inq));
	for (ds[s] = 0, inq[s] = 1, q.push(s); q.empty() == 0; )
	{
		int i = q.front();
		q.pop();
		inq[i] = 0;
		for (int j = 0; j <= end; j++)
			if (cap[i][j] && ds[j] > ds[i] + Cost[i][j])
				if (Path[j] = i, ds[j] = ds[i] + Cost[i][j], inq[j] == 0)
					inq[j] = 1, q.push(j);
	}
	return (ds[end] < inf);
}
int Min_cost_flow(int s, int end)
{
	int i, cost = 0, flow;
	while (SPFA(s, end))
	{
		for (flow = inf, i = end; i!=s; i = Path[i]) flow = min(flow, cap[Path[i]][i]);
		for (cost += flow * ds[end], i = end; i != s; i = Path[i]) cap[Path[i]][i] -= flow, cap[i][Path[i]] += flow;
	}
	return cost;
}
