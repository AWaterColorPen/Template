#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int NN = 1005;
vector <int> vv[NN], qs[NN];

void _addedge(int i, int j) { vv[i].push_back(j); }//qs[i].push_back(j); }

int fa[NN];
int fath(int x) { return fa[x] == x ? x : fa[x] = fath(fa[x]); }

int vs[NN];
void Tarjan_LCA(int n)
{
	int fa[n] = n;
	for (int i = 0, j; i < vv[n].size(); i++)
	{
		Tarjan_LCA(j = vv[n][i]);
		fa[j] = n;
	}
	vs[n] = 1;
	for (int i = 0, j; i < qs[n].size(); i++) if (vs[j = qs[n][i]]) fath(j);
}
