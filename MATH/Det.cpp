#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long LL ;
struct DET {
	static const int M = 205;
	LL a[M][M];
	LL det(int n, int mod)
	{
		int ans = 1;
		for (int i = 0; i < n; i++)
		{	 
			for (int j = i + 1; j < n; j++)
			while (a[j][i])
			{
				LL t = a[i][i] / a[j][i];
				for (int k = i; k < n; k++) a[i][k] = (a[i][k] - a[j][k] * t) % mod;
				for (int k = i; k < n; k++) swap(a[i][k], a[j][k]);
				ans = -ans;
			}
			if (a[i][i] == 0) return 0;
			ans = ans * a[i][i] % mod;
		}
		return (ans % mod + mod) % mod;
	}
}	;