#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

#include <tr1/unordered_map>

using namespace std;
using namespace std::tr1;


typedef long long LL;
unordered_map <int, int> umap;

const int inf = 0x0f0f0f0f;

struct STATE {
	int vs[10];
	int m;
	int cn;
	
	STATE () {}
	STATE (int m) : m(m) {}
	bool operator == (STATE &o) { return cn == o.cn; }
	
	int hash() { return cn; }
	
	void decode(int p[]) {
		int now = cn;
		for (int i = 0; i <= m; i++, now >>= 3) p[i] = now & 7;
	}
	
	void encode(int p[]) {
		cn = 0;
		for (int i = m; i >= 0; i--) cn = (cn << 3) | p[i];
	}

	int minrep(int p[])
	{
		memset(vs, 0, sizeof(vs));
		for (int i = 0; i <= m; i++) vs[p[i]] = 1;
		for (int i = 1; i <= m; i++) if (vs[i] == 0) return i;
	}

	void mintrim(int p[])
	{
		int cnt = 0; 
		memset(vs, 0, sizeof(vs));
		for (int i = 0; i <= m; i++) if (p[i] > 0 && vs[p[i]] == 0) vs[p[i]] = ++cnt;
		for (int i = 0; i <= m; i++) p[i] = vs[p[i]];
	}

	void merge(int px, int py, int p[])
	{
		if (px == 0 || py == 0 || px == py) return;
		for (int i = 0; i <= m; i++) if (p[i] == py) p[i] = px;
	}

	void fresh(int x, int y, int p[]) { p[x] = p[y] = minrep(p); }

	int tar(int x, int y, int z) { return z == 1 ? x : y ; }
	void trans(int i, int j, int x, int y, int p[])
	{
		int xx = p[i], yy = p[j];
		p[i] = (x == 0) ? 0 : tar(xx, yy, x);
		p[j] = (y == 0) ? 0 : tar(xx, yy, y);
	}
}	;
