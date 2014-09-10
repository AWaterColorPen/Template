#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;

struct EBC {
	static const int M = 255 ;
	int con[M][M], mth[M], fa[M], base[M], path[M], inb[M], inq[M];
	int n;
	
	void init()
	{
		memset(con, 0, sizeof(con));
		memset(mth, 0, sizeof(mth));
	}
	void _addedge(int i, int j) { con[i][j] = con[j][i] = 1; }
	
	int lca(int i, int j)
	{
		memset(path, 0, sizeof(path));
		for ( ; i; i = fa[mth[i]]) i = base[i], path[i] = 1;
		for ( ; j; j = fa[mth[j]]) if (j = base[j], path[j]) return j;
	}
	void reset(int i, int anc)
	{
		for (int j; i != anc; i = j)
		{
			j = mth[i];
			inb[base[j]] = inb[base[i]] = 1;
			if (j = fa[j], base[j] != anc) fa[j] = mth[i];
		}
	}
	void contract(int x, int y, queue <int> &q)
	{
		memset(inb, 0, sizeof(inb));
		int anc = lca(x, y);
		reset(x, anc), reset(y, anc);
		if (base[x] != anc) fa[x] = y;
		if (base[y] != anc) fa[y] = x;
		for (int i = 1; i <= n; i++)
			if (inb[base[i]])
			{
				if (base[i] = anc, inq[i] == 0) q.push(i), inq[i] = 1;
			}
	}
	int dfs(int s)
	{
		queue <int> q;
		memset(fa, 0, sizeof(fa));
		memset(inq, 0, sizeof(inq));
		for (int i = 1; i <= n; i++) base[i] = i;
	
		for (q.push(s), inq[s] = 1; q.empty() == 0; )
		{
			int i = q.front(); q.pop();
			for (int j = 1; j <= n; j++)
				if (con[i][j] && base[j] != base[i] && mth[i] != j)
				{
					if (j == s || (mth[j] && fa[mth[j]])) contract(i, j, q);
					else if (fa[j] == 0)
					{
						if (fa[j] = i, mth[j]) q.push(mth[j]), inq[mth[j]] = 1;
						else return augment(j), 1;
					}
				}
		}
		return 0;
	}
	void augment(int i)
	{
		for (int j, t; i; i = t) j = fa[i], t = mth[j], mth[i] = j, mth[j] = i;
	}
	int solve()
	{
		int ans = 0;
		for (int i = 1; i <= n; i++) ans += (mth[i] == 0 && dfs(i));
		return ans;
	}
}	ebc;