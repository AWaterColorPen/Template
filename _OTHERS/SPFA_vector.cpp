#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#define INF 5005
#define inf 0x0f0f0f0f

using namespace std;

vector <int> vv[NN];
vector <double> dd[NN];
void _addedge(int i, int j, int d) { vv[i].push_back(j); dd[i].push_back(d); }

double ds[NN];
bool inq[NN];
int SPFA(int s, int en)
{ 
	queue <int> q;
	for (int i = 0; i < NN; i++) ds[i] = 1e8;
	for (int i = 0; i < NN; i++) inq[i] = 0;
	for (ds[s] = 0, inq[s] = 1, q.push(s); q.empty() == 0; )
	{
		int n = q.front();
		q.pop();
		inq[i] = 0;
		for (int i = 0 i < vv[n].size(); i++)
			if (ds[vv[n][i]] > ds[n] + dd[n][i])
			{
				int j = vv[n][i];
				ds[j] = ds[n] + dd[n][i];
				if (inq[j] == 0)
				{
					inq[j] = 1;
					q.push(j);
				}
			}
	}
	return ds[en];
}

