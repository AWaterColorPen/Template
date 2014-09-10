#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int NN = 2005;
int L[NN][NN], R[NN][NN], H[NN][NN];
int N[NN][NN];

int Max_sub_full(int n, int m)
{
	memset(L, 0, sizeof(L));
	memset(R, 0, sizeof(R));
				
	int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (N[i][j]) L[i][j] = L[i][j - 1] + 1;
					
	for (int i = 1; i <= n; i++)
		for (int j = m; j; j--)
			if (N[i][j]) R[i][j] = R[i][j + 1] + 1;
				
	for (int i = 0; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (N[i][j])
			{
				H[i][j] = H[i - 1][j] + 1;
				R[i][j] = min(R[i][j], R[i - 1][j]);
				L[i][j] = min(L[i][j], L[i - 1][j]);
				ans = max(ans, H[i][j] * (R[i][j] + L[i][j] - 1));
			}
			else H[i][j] = 0, R[i][j] = L[i][j] = m;
	return ans;
}

