#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long LL; 

LL f[20][20][3];
int num[20];
int ST[3][3]={ { 0, 0, 1}, { 0, 2, 1}, { 2, 2, 2} };

LL dp(int pos, int res, int st, bool mark)
{
	if (pos == 0) return res == 0 && st == 2;
	if (mark && f[pos][res][st] != -1) return f[pos][res][st];
	LL ans = 0;
	for (int i = 0, n = mark ? 9 : num[pos]; i <= n; i++)
		ans += dp(pos - 1, (res * 10 + i) % 13, ST[st][i % 3], mark || i < num[pos]);
	return mark ? f[pos][res][st] = ans : ans;
}
LL calc(LL n)
{
	int n0;
	for (n0 = 0; n; n /= 10) num[++n0] = n % 10;
	return dp(n0, 0, 0, false);
}
int main()
{
	LL x;
	memset(f, 0xff, sizeof(f));
	while (cin >> x) cout << calc(x)) << endl;
	return 0;
}
