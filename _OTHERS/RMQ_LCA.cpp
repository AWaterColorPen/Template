#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

struct RMQ {
	static const int M = 40005;
	vector <int> vv[M], dd[M];
	int p[M][17], ds[M], lv[M], bb[20];
	int vs[M];
	
	void _addedge(int i, int j, int d) { vv[i].push_back(j); dd[i].push_back(d); }
	
	int dfs(int n, int fath, int d, int l)
	{
		p[n][0] = fath;
		ds[n] = d;
		lv[n] = l;
		vs[n] = 1;
		
		int ll = l;
		for (int i = 0; i < vv[n].size(); i++)
			if (vs[vv[n][i]] == 0)
				ll = max(ll, dfs(vv[n][i], n, d + dd[n][i], l + 1));
		return ll;
	}

	void init(int n)
	{
		bb[0] = 1;
		for (int i = 1; i < 20; i++) bb[i] = bb[i - 1] << 1;
		memset(vs, 0, sizeof(vs));
		memset(p, 0xff, sizeof(p));

		int ll = dfs(1, -1, 0, 1);
		for (int i = 1; bb[i] <= ll; i++)
			for (int j = 1; j <= n; j++)
				if (p[j][i - 1] != -1)
					p[j][i] = p[p[j][i - 1]][i - 1];
	}

	int ask(int x, int y)
	{
		if (lv[x] < lv[y]) swap(x, y);
		int ll = 0;
		while (bb[ll] <= lv[x]) ll++;

		for (int i = --log; i >= 0; i--) if (lv[x] - bb[i] >= lv[y]) x = p[x][i];
		if (x == y) return x;
		
		for (int i = log; i >= 0; i--) 
			if (p[x][i] != -1 && p[x][i] != p[y][i])
				x = p[x][i], y = p[y][i];
		return p[x][0];
	}
}	;