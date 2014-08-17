#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#define INF 5005
#define inf 0x0f0f0f0f

using namespace std;
struct EDGE {
	int i, c, d; EDGE *next, *ani;
}	*Edge[INF], *Path[INF], e[INF<<3];
void _addedge(int i, int j, int c, int d, EDGE &e1, EDGE &e2)
{
	e1.i=j, e1.c=c, e1.d= d, e1.ani=&e2, e1.next=Edge[i], Edge[i]=&e1;
	e2.i=i, e2.c=0, e2.d=-d, e2.ani=&e1, e2.next=Edge[j], Edge[j]=&e2;
}
int ds[INF], inq[INF];
int SPFA(int s, int end)
{
	int i, j; queue <int> q;
	memset(ds, 0x0f, sizeof(ds));
	memset(inq, 0, sizeof(inq));
	for (ds[s] = 0, inq[s] = 1, q.push(s); !q.empty(); )
	{
		i = q.front(), q.pop(), inq[i] = 0;
		for (EDGE *p = Edge[i]; p; p = p->next)
			if (p->c && ds[j = p->i] > ds[i] + p->d)
				if (Path[j] = p, ds[j] = ds[i] + p->d, inq[j] == 0)
					inq[j] = 1, q.push(j);
	}
	return (ds[end]<inf);
}
int Min_cost_flow(int s, int end)
{
	int i, cost = 0, flow;
	while (SPFA(s, end))
	{
		for (flow = inf, i = end; i != s; i = Path[i]->ani->i) flow = min(flow, Path[i]->c);
		for (cost + =ds[end] * flow, i = end; i != s; i = Path[i]->ani->i) Path[i]->c -= flow, Path[i]->ani->c += flow;
	}
	return cost;
}
