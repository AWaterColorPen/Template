#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;
vector <int> vec[505];
int Match[505];
bool vis[505];
void _addedge(int i, int j) { vec[i].push_back(j); }
int Hungary(int n)
{
	int i, j, siz=vec[n].size();
	for (i=vis[n]=0; i<siz; i++)
		if (Match[j=vec[n][i]]==0 || (vis[Match[j]] && Hungary(Match[j])))
			return Match[j]=n, 1;
	return 0;
}
int Pre_hungary(int n)
{
	int i, cnt=0;
	for (i=1; i<=n; i++)
		memset(vis, true, sizeof(vis)), cnt+=Hungary(i);
	return cnt;
}
