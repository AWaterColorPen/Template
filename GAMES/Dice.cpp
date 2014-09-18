#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;

struct DICE {
	int k[6];
	bool operator == (const DICE &o) const {
		for (int i = 0; i < 6; i++) if (k[i] != o.k[i]) return 0;
		return 1;
	}
	DICE ratote(int r)
	{
		int R[4][6]={{ 0, 1, 5, 4, 2, 3}, { 4, 5, 2, 3, 1, 0}, { 0, 1, 4, 5, 3, 2}, { 5, 4, 2, 3, 0, 1}};
		DICE ret;
		for (int i = 0; i < 6; i++) ret.k[i] = k[R[r][i]];
		return ret;
	}
	void read()
	{
		char str[10];
		scanf("%s", str);
		for (int i = 0; i < 6; i++) k[i] = str[i] - 48;
		swap(k[2], k[3]);
	}
	int hash()
	{
		int ret = 0;
		for (int i = 0; i < 6; i++) ret = ret * 11 + k[i];
		return ret;
	}
}	;
