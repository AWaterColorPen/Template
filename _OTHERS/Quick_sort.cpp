#include <iostream>
#include <cstdio>

using namespace std;

const int NN = 2000005;

int N[NN];
void Qsort(int l, int r)
{
	if (l >= r) return ;
	int i = l, j = r, mid = N[(r + l) / 2];
	while (i <= j)
	{
		while (Num[i] < mid) i++;
		while (Num[j] > mid) j--;
		if (i <= j) swap(N[i], N[j]), i++, j--;
	}
	Qsort(l, j);
	Qsort(i, r);
}

