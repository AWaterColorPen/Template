#include <iostream>
#include <cstdio>

using namespace std;
static const int M = 1000005 ;
int prime[M/12], phi[M], mu[M];
bool primes[M];
void Euler_primes_phi_mu()
{
	phi[1]=mu[1]=1;
	for (int i=2; i<M; i++)
	{
		if (primes[i]==0)
			phi[i]=i-1, mu[i]=-1, prime[++prime[0]]=i;
		for (int j=1; j<=prime[0] && prime[j]*i<M; j++)
		{
			primes[prime[j]*i]=true;
			if (i%prime[j]==0) { phi[i*prime[j]] = phi[i]*prime[j], mu[i*prime[j]] = 0; break; }
			phi[i*prime[j]] = phi[i]*(prime[j]-1), mu[i*prime[j]]=-mu[i];
		}
	}
}
