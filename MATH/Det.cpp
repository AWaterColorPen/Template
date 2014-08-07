#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define DET_SIZE 205
#define _int64 long long 

using namespace std;
_int64 N[DET_SIZE][DET_SIZE];
_int64 det(_int64 a[DET_SIZE][DET_SIZE], int n, int mod)
{
	int ans=1;
	for(int i=0; i<n; i++)
	{ 
		for(int j=i+1; j<n; j++)
			while (a[j][i])
			{
				_int64 t=a[i][i]/a[j][i];
				for(int k=i; k<n; k++) a[i][k]=(a[i][k]-a[j][k]*t)%mod;
				for(int k=i; k<n; k++) swap(a[i][k], a[j][k]);
				ans=-ans;
			}
		if(a[i][i]==0)return 0;
		ans=ans*a[i][i]%mod;
	}
	return (ans%mod+mod)%mod;
}