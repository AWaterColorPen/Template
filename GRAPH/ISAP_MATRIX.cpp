#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int NN = 205;
const int inf = 0x0f0f0f0f;

int cap[NN][NN];
void _addedge(int i, int j, int c) { cap[i][j] += c; }

int Dfn[NN], Gap[NN], S, E, CNT;
int ISAP(int n, int flow)
{
	if (n == E) return flow;
	int tab = CNT, vary, now = 0;
	for (int i = 0; i <= E; i++)
		if (cap[n][i])
		{
			if (Dfn[n] == Dfn[i] + 1)
				vary = ISAP(i, min(cap[n][i], flow - now)),
				cap[n][i] -= vary, cap[i][n] += vary, now += vary;
			if (Dfn[S] == CNT) return now;
			if (cap[n][i]) tab = min(tab, Dfn[i]);
			if (flow == now) break;
		}
	if (now == 0) {
		if (--Gap[Dfn[n]] == 0) Dfn[S] = CNT;
		Gap[Dfn[n] = tab + 1]++;
	}
	return now;
}
int Maxflow(int s, int end)
{
	int flow=0;
	//S=s, E=end, CNT=E+1;
	//memset(cap,0,sizeof(cap));
	memset(Gap, 0, sizeof(Gap));
	memset(Dfn, 0, sizeof(Dfn));
	for (Gap[0] = CNT; Dfn[S] < CNT; ) flow += ISAP(S, inf);
	return flow;
}
