#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int NN = 25005;
const int ASCII = 256;

int ARR[4][NN], Arr[NN], bu[NN];
int *sa, *_sa, *rk, *_rk;
void Suffix_Array(int n)
{
	sa = ARR[0];
	_sa = ARR[1];
	rk = ARR[2];
	_rk = ARR[3];	
	memset(bu, 0, sizeof(bu));
	for (int i = 1; i <= n; i++) bu[Arr[i]]++;
	for (int i = 1; i <= ASCII; i++) bu[i] += bu[i - 1];
	for (int i = n; i; i--)	sa[bu[Arr[i]]--] = i;
	
	rk[sa[1]] = 1;
	for (int i = 2; i <= n; i++) {
		rk[sa[i]] = rk[sa[i - 1]];
		rk[sa[i]] += (Arr[sa[i]] != Arr[sa[i - 1]]);
	}
	
	for(int k = 1; k <= n && rk[sa[n]] < n; k <<= 1)
	{
		for(int i = 1; i <= n; i++)	bu[rk[sa[i]]] = i;
		for(int i = n; i; i--) if(sa[i] - k > 0) _sa[bu[rk[sa[i] - k]]--] = sa[i] - k;
		for(int i = n - k + 1; i <= n; i++)	_sa[bu[rk[i]]--] = i;
		
		_rk[_sa[1]] = 1;
		for(int i = 2; i <= n; i++) {
			_rk[_sa[i]] = _rk[_sa[i - 1]],
			_rk[_sa[i]] += (rk[_sa[i]] != rk[_sa[i - 1]] || rk[_sa[i] + k] != rk[_sa[i - 1] + k]);
		}
		swap(sa, _sa);
		swap(rk, _rk);
	}
}

int HH[NN];
void CalH(int n)
{
	for (int i = 1, k = 0, j; i <= n; i++)
		if (rk[i] == 1) HH[1] = 0;
		else {
			for (int j = sa[rk[i] - 1]; Arr[i + k] == Arr[j + k]; k++) ;
			if (HH[rk[i]] = k, k) k--;
		}
}
