#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;
struct GRAPH_HASH {
	static const int M = 10005 ;
	vector <pair <int, int> > edge;
	int f[M], _f[M], hash[M];
	int n, A, B, C, D, P, K;
	
	void clear() { edge.clear(); }
	void init(int _n, int a, int b, int c, int d, int p, int k) { n=_n, A=a, B=b, C=c, D=d, P=p, K=k; }
	void _addedge(int i, int j) { edge.push_back(make_pair(i,j)); }
	void graph_hash()
	{
		for (int i=1; i<=n; i++)
		{
			for (int j=1; j<=n; j++) f[j]=1;
			for (int j=1; j<=K; j++)
			{
				memcpy(_f, f, sizeof(_f));
				for (int k=1; k<=n; k++) f[k]*=A;
				for (int k=0; k<edge.size(); k++)
				{
					f[edge[k].first]+=_f[edge[k].second]*B;
					f[edge[k].second]+=_f[edge[k].first]*C;
				}
				f[i]+=D;
				for (int k=1; k<=n; k++) f[k]%=P;
			}
			hash[i]=f[i];
		}
		sort(hash+1, hash+n+1);
	}
}	g[2];