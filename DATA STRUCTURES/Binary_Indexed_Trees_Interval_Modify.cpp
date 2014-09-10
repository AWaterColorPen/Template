#include <iostream>
#include <cstdio>

using namespace std;

typedef long long LL;
const int NN = 0x20001;

LL so[NN], tdi[NN], td[NN];
void update(int i, int m, LL t[])
{
	for ( ; i < NN; i += i & (-i)) t[i] += m;
}
void modify(int i, int j, int m)
{
	update(i, m * i, tdi);
	update(i, m, td);
	update(j + 1, -m * (j + 1), tdi),
	update(j + 1, -m, td);
}
LL ask(int n)
{
	LL sum = so[n], k = n + 1, now;
	for (now = 0; n; n -= n&(-n))
		sum -= tdi[n], now += td[n];
	return sum += k * now;
}
int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		so[i] = so[i - 1] + x;
	}
	return 0;
}
