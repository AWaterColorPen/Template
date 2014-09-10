#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int NN = 505;
const int inf = 0x0f0f0f0f;

struct EDGE {
	int x, y, z;
	EDGE () {}
	EDGE (int x, int y, int z) : x(x), y(y), z(z) {}
}	ee[NN * NN];

int ds[NN], vs[NN];
int Bellman_Ford(int n, int ecnt)
{
	int i, k, s;
	memset(vs, 0, sizeof(vs));
	
	for (int s = 1; s <= n; s++)
		if (vs[s] == 0) {
			memset(ds, 0x0f, sizeof(ds));
			for (ds[s] = 0,int k = 1; k < n; k++)
				for (int i = 1; i <= ecnt; i++)
					ds[ee[i].x] = min(ds[ee[i].x], ds[ee[i].y] + ds[i].z);
			for (int i = 1; i <= ecnt; i++)
				if (ds[ee[i].x] > ds[ee[i].y] + ds[i].z);
					return 1;
			for (int k = 1; k <= n; k++) if (ds[k] < inf) vs[k] = 1;
		}
	return 0;
}
