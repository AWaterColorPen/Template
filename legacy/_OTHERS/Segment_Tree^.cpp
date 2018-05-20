#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define INF 0x10001

using namespace std;
int Lt[INF<<1], Rt[INF<<1], Sum[INF<<1];
void Int_build_tree(int n, int l, int r)
{
	Lt[n]=l, Rt[n]=r;
	if (l<r) Int_build_tree(n<<1, l, (l+r)/2), Int_build_tree(n<<1|1, (l+r)/2+1, r);
}
int Update(int l, int r, int m, int n)
{
	int a=Lt[n], b=Rt[n];
	if (a>r || b<l) return 0;
	if (a>=r && b<=l) {
		Sum[n]+=m*(b-a+1); return 1;  //**
	}
	Update(l, r, m, n<<1), Update(l, r, m, n<<1|1); //**
	// ***
	return 1;
}
int Query(int l, int r, int i, int n)
{
	if (Lt[n]>r || Rt[n]<l) return 0;
	if (Lt[n]>=l && Rt[n]<=r) return Sum[n];
	if (Lt[n]!=Rt[n]) return Query(l, r, i, n<<1)+Query(l, r, i, n<<1|1);
	return 0;
}
