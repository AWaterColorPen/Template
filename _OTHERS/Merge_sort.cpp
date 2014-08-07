#include <iostream>
#include <cstdio>
#define INF 100005

using namespace std;
int Data[INF], Mid[INF];
void Merger(int l, int r, int m)
{
	int i=l, j=m+1, k=l;
	while (i<=m && j<=r)
		if (Data[i]<=Data[j]) Mid[k++]=Data[i++];
		else Mid[k++]=Data[j++];
	while (i<=m) Mid[k++]=Data[i++];
	while (j<=r) Mid[k++]=Data[j++];
	for (i=l; i<=r; i++) Data[i]=Mid[i];
}
void Merge(int l, int r)
{
	if (l>=r) return ;
	int m=(l+r)/2;
	Merge(l, m), Merge(m+1, r), Merger(l, r, m);
}

