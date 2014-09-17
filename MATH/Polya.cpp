#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define MOD 9973

using namespace std;

typedef long long LL;
//make to prime and phi
static const int M = 1000005 ;
int prime[M / 12], phi[M], mu[M];
bool primes[M];
void Euler_primes_phi()
{
	phi[1] = 1;
	for (int i = 2; i < M; i++)
	{
		if (primes[i] == 0)
			phi[i] = i - 1, prime[++prime[0]] = i;
		for (int j = 1; j <= prime[0] && prime[j] * i < M; j++)
		{
			primes[prime[j] * i] = 1;
			if (i % prime[j] == 0) { phi[i * prime[j]] = phi[i] * prime[j]; break; }
			phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
}

//prime to make phi
int Phi(int n)
{
	int res = n;
	for (int i = 1; prime[i] * prime[i] <= n; i++)
		if (n % prime[i] == 0)
			for (res -= res/prime[i]; n % prime[i] == 0; n /= prime[i]) ;
	if (n > 1) res -= res / n;
	return res % MOD;
}
//to make phi
int Phi(int n)
{
	int res = n;
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0)
			for (res -= res / i; n % i == 0; n /= i) ;
	if (n > 1) res -= res / n;
	return res % MOD;
}
//
int pow_mod(int a, int n)
{
	int ans = 1;
	for ( ; n; n >>= 1, a = (a * a) % MOD) if (n & 1) ans = (ans * a) % MOD;
	return ans;
}
//use factor to make polay
int cnt[100], fac[100];
void prime_factor(LL n)
{
	for (int i = 1; prime[i] * prime[i] <= n; i++)
		if (n % prime[i] == 0)
		{
			cnt[++cnt[0]] = 0, fac[cnt[0]] = prime[i];
			while (n % prime[i] == 0) cnt[cnt[0]]++, n /= prime[i];
		}
	if (n > 1) cnt[++cnt[0]] = 1, fac[cnt[0]] = n;
}
LL ANS;
void dfs(int step, int fact, int n, int base)
{
	if (step == cnt[0]) { ANS = (ANS + pow[base * fact] * phi[n / fact]) % MOD; return ; }
	dfs(step + 1, fact, n, base);
	for (int i = 1; i <= cnt[step + 1]; i++)
		dfs(step + 1, fact *= fac[step + 1], n, base);
}
//to make polay
int polya(int n, int base)
{
    int ans = 0;
	for (int i = 1; i * i <= n; i++)
		if (n % i == 0)
		{
			ans = (ans + pow_mod(base, i) * phi[n / i]) % MOD;
			if (i * i != n)
				ans = (ans + pow_mod(base, n / i) * phi[i]) % MOD;
		}

	ans = (ans * pow_mod(n, MOD - 2)) % MOD;
	return ans;
}
