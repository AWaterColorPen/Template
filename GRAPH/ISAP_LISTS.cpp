#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int NN = 400005;
const int inf = 0x0f0f0f0f;
struct EDGE {
	int i, c;
	EDGE *next, *ani;
	EDGE () {}
	EDGE (int i, int c, EDGE *next, EDGE *ani) : i(i), c(c), next(next), ani(ani) {}
}	*Edge[NN], e[NN << 1];

void _addedge(int i, int j, int c, EDGE &e1, EDGE &e2)
{
	e1 = EDGE(j, c, Edge[i], &e2); Edge[i] = &e1;
	e2 = EDGE(i, 0, Edge[j], &e1); Edge[j] = &e2;
}

int Dfn[NN], Gap[NN], S, E, CNT;
int ISAP(int n, int flow)
{
	if (n == E) return flow;
	int i, tab = CNT, vary, now = 0;
	for (EDGE *p = Edge[n]; p; p = p->next)
		if (p->c) {
			if (Dfn[n] == Dfn[i = p->i] + 1)
				vary = ISAP(i, min(p->c, flow - now)),
				p->c -= vary, p->ani->c += vary, now += vary;
			if (Dfn[S] == CNT) return now;
			if (p->c) tab = min(tab, Dfn[i]);
			if (now == flow) break;
		}
	if (now == 0) {
		if (--Gap[Dfn[n]] == 0) Dfn[S] = CNT;
		Gap[Dfn[n] = tab + 1]++;
	}
	return now;
}
int Maxflow(int s,int end)
{
	int flow = 0;
	//S=s, E=end, CNT=E+1;
	//memset(Edge, 0, sizeof(Edge));
	memset(Gap, 0, sizeof(Gap));
	memset(Dfn, 0, sizeof(Dfn));
	for (Gap[0] = CNT; Dfn[S] < CNT; ) flow += ISAP(S, inf);
	return flow;
}

