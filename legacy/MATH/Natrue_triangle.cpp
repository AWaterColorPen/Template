#include <algorithm>
#include <iostream>
#include <cstdio>
#include <map>

using namespace std;
const int MOD = 1000000007;
typedef long long LL ;
map <int, LL> F;
LL Natrue_triangle(int n)
{
	if (F[n] != 0) return F[n];
	LL cnt = 0, res = 0;
	for (int i = 1; i <= n / 3; i++)
		cnt = (cnt + max((n - i) / 2 - max((n - 2 * i) / 2 + 1, i) + 1, 0)) % MOD;
	for (int i = 2; i <= n / i; i++)
		if (n % i == 0) {
				res = (res + Natrue_triangle(n / i)) % MOD;
				if (n / i != i)
				res = (res + Natrue_triangle(i)) % MOD;
		}
	return F[n] = (cnt + MOD - res) % MOD, F[n];
}
