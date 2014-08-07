#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define inf 0x0f0f0f0f

using namespace std;

typedef long long _int64 ; 

_int64 f[20][20][3];
int num[20];
int ST[3][3]={ { 0, 0, 1}, { 0, 2, 1}, { 2, 2, 2} };

_int64 dp(int pos, int res, int st, bool tab)
{
	if (pos == 0) return (res == 0 && st == 2);
	if (tab && f[pos][res][st] != -1) return f[pos][res][st];
	_int64 ans = 0;
	for (int i = 0, n = tab ? 9 : num[pos]; i <= n; i++)
		ans += dp(pos - 1, (res * 10 + i) % 13, ST[st][i % 3], tab || i < num[pos]);
	return tab ? f[pos][res][st] = ans : ans;
}
_int64 calc(_int64 n)
{
	int n0;
	for (n0 = 0; n; n /= 10) num[++n0] = n % 10;
	return dp(n0, 0, 0, false);
}
int main()
{
	_int64 x;
	memset(f, 0xff, sizeof(f));
	while (cin >> x) cout << calc(x)) << endl;
	return 0;
}
