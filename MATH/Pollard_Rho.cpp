#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

typedef long long LL;
map <LL, int> Map;
map <LL, int>::iterator it;

LL GCD(LL a, LL b) { for (LL t; b; t = a % b, a = b, b = t) ; return a ; }
LL mul_mod(LL A, LL B, LL n)
{
	LL ans = 0;
	for ( ; B; B >>= 1, A = (A << 1) % n) if (B & 1) ans = (ans + A) % n;
	return ans;
}
LL mod_exp(LL A, LL B, LL n)
{
	LL ans = 1LL;
	for ( ; B; B >>= 1, A = mul_mod(A, A, n)) if (B & 1) ans = mul_mod(ans, A, n);
	return ans;
}
bool witness(LL n)
{
	LL m = n - 1, a = rand() % m + 1;
	while (m % 2 == 0) m >>= 1;
	if (a = mod_exp(a, m, n), a == 1) return true;
	while (m != n - 1 && a != n - 1)
		a = mul_mod(a, a, n), m <<= 1;
	return a == n - 1;
}
bool miller_rabin(LL n)
{
	if (n % 2 == 0) return n == 2;
	for (int i = 0; i < 10; i++)
		if (witness(n) == false) return false;
	return true;
}
LL pollard_rho(LL c, LL n)
{
	LL x = rand() % n, y = x, i = 1, k = 2, d;
	do {
		if (i++, d = GCD(n + y - x, n), d > 1 && d < n) return d;
		if (i == k) y = x, k <<= 1;
		x = (mul_mod(x, x, n) - c + n) % n;
	}	while (y != x);
	return n;
}
void rho(LL n)
{
	if (n <= 1) return ;
	if (miller_rabin(n)) { Map[n] = 1; return ; }
	LL t;
	do t = pollard_rho(rand() % (n - 1) + 1, n);
	while (t == 1 || t == n);
	rho(t), rho(n / t);
}
void prime_factor(LL n)
{
	Map.clear(), rho(n);
	for (it = Map.begin(); it != Map.end(); it++)
	{
		for (it->second = 0; n % it->first == 0; n /= it->first)
			it->second++;
	}
}
