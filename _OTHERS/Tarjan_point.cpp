#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const NN = 10005;

vector <int> vv[NN];
void _addedge(int x, int y) { vv[x].push_back(y) ; }

int dfn[NN], low[NN], blo[NN], Cnt;
void Tarjan_point(int n)
{
	int i, j;
	dfn[n] = low[n] = ++Cnt;
	for (i = 0; i < vv[n].size(); i++)
		if (dfn[j = vv[n][i]] == 0)
			Tarjan_point(j), low[n] = min(low[n], low[j]);
			if (dfn[n] <= low[j]) blo[n]++;
		}
		else low[n] = min(low[n], dfn[j]);
}
