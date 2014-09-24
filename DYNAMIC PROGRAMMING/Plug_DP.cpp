#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long LL;
const int inf = 0x0f0f0f0f;

struct STATE {
	static int vs[10];
	static int m;

	int cn;
	STATE () {}
	STATE (int m) : m(m) {}
	bool operator == (STATE &o) { return cn == o.cn; }
	
	int hash() { return cn; }
	
	void decode(int now, int p[]) {
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
		for (int i = 0; i <= m; i++) if (vs[p[i]] == 0) vs[p[i]] = ++cnt;
		for (int i = 0; i <= m; i++) p[i] = vs[p[i]];
	}

	void merge(int px, int py, int p[])
	{
		if (px == 0 || py == 0 || px == py) return;
		for (int i = 0; i <= m; i++) if (p[i] == py) p[i] = px
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

bool maze[15][15];
int con[10];

void vary_vis(int to, int now)				 //to==1 向右，to==0 向左，3同to==1
{
	for (int cnt=(CON[now]==3); cnt; now+=to==1?1:-1) {
		if (to==1)	cnt+=(CON[now]==1), cnt-=(CON[now]==2);
		else		cnt+=(CON[now]==2), cnt-=(CON[now]==1);
		if (cnt==0 || (cnt==1 && (CON[now]==3 || CON[now]&1==to)))
			vis[now]=1;
		if (cnt==0) return ;
	}
}
void vary_no(int to, int now)				//to==1 向右，to==0 向左，3同to==1
{
	memset(vis, 0, sizeof(vis));
	if (CON[now]==1 || CON[now]==2) vary_vis(CON[now], now);
	
	memset(vis, 0, sizeof(vis));
	if (CON[now+1]==1 || CON[now+1]==2) vary_vis(CON[now+1], now+1);
}
int Merger(int to, int fire, int now)			  // //to==0无无，to==1无右，to==2无左
{
	memset(vis, 0, sizeof(vis));
	if (CON[now])
}
int Merger(int st, bool vec, int tmp)
{
	int cnt, num=3<<tmp, now=(vec?1:2)<<tmp;
	for (cnt=1; cnt; ) {
		if (vec)	now<<=2, num<<=2;
		else		now>>=2, num>>=2;	 
		if (st&num)
			cnt+=((st&num)==now)?1:-1;
	}
	return st^num;
}
void Shift(int conn, int num, int t, int r, int c)
{
	;
}
long long Plug_DP(int n, int m)
{
	int i, j, k, t, _t; long long ans=0;
	F[0].clear(), F[0].insert(0, 1);
	for (t=0, i=1; i<=n; i++)
	{
		for (k=1; k<=F[t].size; k++)
			F[t].st[k]<<=2;
		for (j=1; j<=m; j++)
			if(MAP[i][j])
				for(_t=t, t^=1, F[t].clear(), k=1; k<=F[_t].size; k++)
					Shift(F[_t].st[k], F[_t].f[k], t, i, j);
	}
	for(k=1; k<=F[t].size; k++)
		if (F[t].st[k]==(1|(1<<(2*m-1))))
			ans+=F[t].f[k];
	return ans;
}