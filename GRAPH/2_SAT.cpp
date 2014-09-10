#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const NN = 105;

vector <int> vv[NN];
void _addedge(int x, int y) { vv[x].push_back(y) ; }

int dfn[NN], low[NN], stk[NN], blo[NN], block, Cnt, Now;
int ins[NN];

void tarjan(int n)
{
	int i, j;
	low[n] = dfn[n] = ++Cnt, ins[stk[++Now] = n] = 1;
	for (i = 0; i < vv[n].size(); i++)
		if (dfn[j = vv[n][i]] == 0)
			tarjan(j), low[n] = min(low[n], low[j]);
		else if (ins[j]) low[n] = min(low[n], low[j]);
	if (dfn[n] == low[n] && ++block)
		do blo[i = stk[Now--]] = block, ins[i] = 0;
		while (i != n);
}

vector <int> vvv[NN];
int mth[NN], ind[NN];
int vis[NN];

void Top_sort(int n)
{
	memset(vs, 0xff, sizeof(vs));
	for (int i = 1; i <= n; i++) mth[blo[i]] = blo[i + n], mth[blo[i + n]] = blo[i];
	
	for (int i = 1; i <= n + n; i++)
		for (int j = 0; j < vv[i].size(); j++)
			if (blo[i] != blo[vv[i][j]])
				vvv[blo[vv[i][j]]].push_back(blo[i]), ind[blo[i]]++;
				
	queue <int> q;
	for (int i = 1; i <= block; i++) if (ind[i] == 0) q.push(i);
	while (q.empty() == 0) {
		int i = q.front();
		q.pop();
		if (vis[i] == -1) vs[i] = 1, vis[mth[i]] = 0;
		for (int j = 0; j < vvv[i].size(); j++) if (--ind[vvv[i][j]] == 0) q.push(vvv[i][j]);
	}
}
