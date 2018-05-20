#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

const int NN = 105;

struct EDGE {
	int x, y, z;
	EDGE () {}
	EDGE (int x, int y, int z) : x(x), y(y), z(z) {}
	bool operator < (const EDGE &o) { return z < o.z ; }
}	ee[NN * NN];

int fa[NN];
int fath(int x) { return fa[x] == x ? x : fa[x] = fath(fa[x]); }

int Kruskal(int n, int ecnt)
{
	int cnt = 1, cost = 0;
	sort(ee ,ee + ecnt);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 0; i < ecnt && cnt < n; i++)
		if (fath(ee[i].x) != fath(ee[i].y))
		{
			fa[fa[ee[i].x]] = fa[ee[i].y];
			cnt++;
			cost += ee[i].z;
		}
	if (cnt < n) return -1;
	return cost;
}
