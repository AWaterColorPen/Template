#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define INF 100

using namespace std;
struct NIM {
	static const int M = 105 ;
	int vis[M], sg[M];
	int _SG(int n)
	{
		memset(vis, 0, sizeof(vis));
		for (int i=0; i<n; i++)
			for (int j=0; j<=i; j++)
				vis[sg[i]^sg[j]]=1;
		for (int i=0; i<M; i++) if (vis[i]==0) return i;
	}
	void pre_sg(int n)
	{
		sg[0] = 0;
		for (int i=1; i<=n; i++) sg[i]=_SG(i);
	}
	void show(int n) { for (int i=0; i<=n; i++) printf("sg[%d] = %d\n", i, sg[i]); }
	int find_period()
	{
		for (int res=1, j; res*2<M; res++)
		{
			for (j=M/2; j<M; j++) if (sg[j]!=sg[j-res]) break;
			if (j==M) return res;
		}
		return -1;
	}
}	nim;
double SN(int *st, int n)
{
	int i;
	double ans=0, base=0.5;
	for (i=1; i<=n && st[i]==st[1]; i++) if (st[i]) ans++; else ans--;
	for ( ; i<=n; i++, base*=0.5) if (st[i]) ans+=base; else ans-=base;
	return ans;
}