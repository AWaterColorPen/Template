#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define INF 25005
#define inf 0x0f0f0f0f
#define ASCII 256

using namespace std;
int ARR[4][INF], Height[INF], Arr[INF], Buck[INF];
int *SA, *_SA, *RANK, *_RANK;
void Suffix_Array(int n)
{
	SA=ARR[0], _SA=ARR[1], RANK=ARR[2], _RANK=ARR[3];
	int i, k, *t;		memset(Buck, 0, sizeof(Buck));
	for (i=1; i<=n; i++)		Buck[Arr[i]]++;
	for (i=1; i<=ASCII; i++)	Buck[i]+=Buck[i-1];
	for (i=n; i; i--)			SA[Buck[Arr[i]]--]=i;
	for (RANK[SA[1]]=1, i=2; i<=n; i++)
		RANK[SA[i]]=RANK[SA[i-1]],
		RANK[SA[i]]+=(Arr[SA[i]]!=Arr[SA[i-1]]);
	for(k=1; k<=n && RANK[SA[n]]<n; k<<=1)
	{
		for(i=1; i<=n; i++)				Buck[RANK[SA[i]]]=i;
		for(i=n; i; i--) if(SA[i]-k>0)	_SA[Buck[RANK[SA[i]-k]]--]=SA[i]-k;
		for(i=n-k+1; i<=n; i++)			_SA[Buck[RANK[i]]--]=i;
		for(_RANK[_SA[1]]=1, i=2; i<=n; i++)
			_RANK[_SA[i]]=_RANK[_SA[i-1]],
			_RANK[_SA[i]]+=(RANK[_SA[i]]!=RANK[_SA[i-1]] || RANK[_SA[i]+k]!=RANK[_SA[i-1]+k]);
		t=SA, SA=_SA, _SA=t, t=RANK, RANK=_RANK, _RANK=t;
	}
}
void Cal_Height(int n)
{
	for (int i=1, k=0, j; i<=n; i++)
		if (RANK[i]==1) Height[1]=0;
		else	{
			for (j=SA[RANK[i]-1]; Arr[i+k]==Arr[j+k]; k++);
			if (Height[RANK[i]]=k, k) k--;
		}
}
