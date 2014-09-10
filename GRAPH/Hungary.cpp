#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

const int NN = 505;

vector <int> vv[NN];
int mth[NN], vis[NN];
void _addedge(int i, int j) { vv[i].push_back(j); }
int Hungary(int n)
{
	vis[n] = 1;
	for (int i = 0, j; i < vv[n].size(); i++)
		if (mth[j = vv[n][i]] == 0 || (vis[mth[j]] == 0 && Hungary(mth[j])))
			return mth[j] = n, 1;
	return 0;
}
int Pre_hungary(int n)
{
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		memset(vis, 0, sizeof(vis))
		cnt += Hungary(i);
	}
	return cnt;
}
