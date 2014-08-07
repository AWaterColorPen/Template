#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define INF 2005
#define inf 0x0f0f0f0f

using namespace std;
int L[INF][INF], R[INF][INF], H[INF][INF];
int N[INF][INF];
int Max_sub_full(int n, int m)
{
	memset(L, 0, sizeof(L));
	memset(R, 0, sizeof(R));
				
	int ans=0, i, j;
	for (i=1; i<=n; i++)
		for (j=1; j<=m; j++)
			if (N[i][j]) L[i][j]=L[i][j-1]+1;
					
	for (i=1; i<=n; i++)
		for (j=m; j; j--)
			if (N[i][j]) R[i][j]=R[i][j+1]+1;
				
	for (i=0; i<=n; i++)
		for (j=1; j<=m; j++)
			if (N[i][j])
			{
				H[i][j]=H[i-1][j]+1;
				R[i][j]=min(R[i][j], R[i-1][j]);
				L[i][j]=min(L[i][j], L[i-1][j]);
				ans=max(ans, H[i][j]*(R[i][j]+L[i][j]-1));
			}
			else H[i][j]=0, R[i][j]=L[i][j]=m;				
	return ans;
}

