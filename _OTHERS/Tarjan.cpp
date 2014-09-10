#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

const NN = 105;

vector <int> vv[NN];
void _addedge(int x, int y) { vv[x].push_back(y) ; }

int dfn[NN], low[NN], stk[NN], blo[NN], Block, Cnt, Now;
int ins[NN];

void tarjan(int n)
{
	int i, j;
	low[n] = dfn[n] = ++Cnt, ins[stk[++Now] = n] = 1;
	for (i = 0; i < vv[n].size(); i++)
		if (dfn[j = vv[n][i]] == 0)
			tarjan(j), low[n] = min(low[n], low[j]);
		else if (ins[j]) low[n] = min(low[n], low[j]);
	if (dfn[n] == low[n] && ++Block)
		do blo[i = stk[Now--]] = Block, ins[i] = 0;
		while (i != n);
}

