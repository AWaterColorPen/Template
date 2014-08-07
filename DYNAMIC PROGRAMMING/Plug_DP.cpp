#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define HASH_SIZE 100001
#define inf 0x0f0f0f0f

using namespace std;
bool Maze[15][15];
int vis[20], CON[20];
struct STATE {
	int conn, fire;
	int hash() {return conn+fire;}
	int compare(STATE n) {return (conn==n.conn && fire==n.fire);}
	void decode(int now, int m, int p[]) {
		for (int i=0; i<=m; i++, now>>=3) p[i]=now&7;
	}
	void encode(int m, int p[]) {
		conn=0; for (int i=m; i>=0; i--) conn=conn<<3|p[i];
	}
	int min_rep(int m, int p[])
	{
		memset(vis, 0, sizeof(vis));
		for (int i=0; i<m; i++) if (p[i]!=inf) vis[CON[i]]=1;
		for (int i=1; i<=m; i++) if (vis[i]==0) return i;
	}
	void min_rearrange(int m, int p[])
	{
		int cnt=0, i; memset(vis, 0, sizeof(vis));
		for (i=0; i<m; i++) if (vis[p[i]]==0) vis[p[i]]=++cnt;
		for (i=0; i<m; i++) p[i]=vis[p[i]];
	}
	void gen_rearrange(int m, int p[])
	{
		int cnt=0, bef;
		for (int i=0; i<=m; i++) if (vis[i]) CON[i]=3, bef=i;
		if (cnt==1) { if (FIRE[bef]==0) CON[bef]=0; return ; }
		for (int i=0; i<=m; i++) if (vis[i]) { CON[i]=1; break; }
		for (int i=m; i>=0; i--) if (vis[i]) { CON[i]=2; break; }
	}
}
struct HASHTABLE {
	STATE st[HASH_SIZE];
	int hash[HASH_SIZE], pos[HASH_SIZE], size;
	int val[HASH_SIZE];
	void insert(STATE n, int _val)
	{
		int i, now=n.hash()%HASH_SIZE;
		for (i=hash[now]; i; i=pos[i])
			if (st1[i].compare(n)) { val[i]+=_val;  return ; }
		++size, val[size]=_val, st[size]=n, pos[size]=hash[now], hash[now]=size;
	}
	void clear() { memset(hash, size=0, sizeof(hash)); }
}	F[2];
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
