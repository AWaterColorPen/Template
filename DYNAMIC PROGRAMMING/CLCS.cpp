#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

struct CLCS {
	static const int M = 1005 ;
	int A[M+M], B[M];
	int len[M+M][M], pre[M+M][M];
	void reroot(int root, int m, int n)
	{
		int i=root, j=1;
		while (j<=n && pre[i][j]!=2) j++;
		if (j>n) return ;

		while (i<m*2 && j<n)
			if (pre[i+1][j]==3) pre[++i][j]=1;
			else 	if (pre[i+1][j+1]==2) pre[++i][++j]=1;
					else	j++;

		while (i<2*m && pre[i+1][j]==3) pre[++i][j]=1;
	}

	void lcs(int m, int n)
	{
		for (int i=1; i<=m; i++)
			for (int j=1; j<=n; j++)
			{
				len[i][j]=len[i][j-1], pre[i][j]=1;
				if (A[i]==B[j] && len[i][j]<len[i-1][j-1]+1) len[i][j]=len[i-1][j-1]+1, pre[i][j]=2;
				if (len[i][j]<len[i-1][j]) len[i][j]=len[i-1][j], pre[i][j]=3;
			}
	}

	int trace_lcs(int m, int n)
	{
		int len=0;
		for (int i=m, j=n; pre[i][j]; )
		{
			if (pre[i][j]==1) { j--; continue ; }
			if (pre[i][j]==2) { j--, i--, len++; continue ; }
			if (pre[i][j]==3) { i--; continue ; }
		}
		return len;
	}

	void init(int m, int n)
	{
		memset(len, 0, sizeof(len));
		memset(pre, 0, sizeof(pre));
		for (int i=1; i<=m; i++) A[i+m]=A[i];
		for (int i=1; i<=n; i++) pre[0][i]=1;
		for (int i=1; i<=2*m; i++) pre[i][0]=3;
	}

	int work(int m, int n)
	{
		init(m, n);
		lcs(2*m, n);
		int ans=trace_lcs(m, n);

		for (int i=1; i<m; i++)
		{
			reroot(i, m, n);
			int now=trace_lcs(m+i, n);
			ans=max(ans, now);
		}
		return ans;
	}
}	clcs;