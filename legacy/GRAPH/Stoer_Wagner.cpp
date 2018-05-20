#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int NN = 505;
const int inf = 0x0f0f0f0f;

int cap[NN][NN], dfn[NN], wage[NN];
void _addedge(int i, int j, int c) { cap[i][j] += c; cap[j][i] += c; }

int Stoer_Wagner(int n)
{
	int mincut = inf;
	for (int i = 1; i <= n; i++) dfn[i] = i;
	for ( ; n > 1; n--)
	{
		memset(wage, 0, sizeof(wage));
		for (int i = 1; i <= n; i++, swap(dfn[i], dfn[now]))
		{
			int now = i + 1, t;
			for (int j = i + 1; j <= n; j++)
				if (t = dfn[j], wage[t] += cap[dfn[i]][t], wage[dfn[now]] < wage[t])
					now = j;
		}
		mincut = min(mincut, wage[dfn[n]]);
		for (int i = 1; i <= n - 1; i++)
		{
			int now = cap[dfn[i]][dfn[n]];
			cap[dfn[i]][dfn[n - 1]] += now;
			cap[dfn[n - 1]][dfn[i]] += now;
		}
	}
	return mincut;
}
