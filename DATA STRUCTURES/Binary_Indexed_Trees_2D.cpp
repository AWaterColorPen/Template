#include <iostream>
#include <cstdio>

using namespace std;

struct BIT {
	static const int M = 400005;
	int T[M];
	void modify(int i, int m)
	{
		for ( ; i < M; i += i & (-i)) T[i] += m;
	}
	int ask(int i)
	{
		int sum = 0;
		for ( ; i ; i -=i & (-i)) sum += T[i];
		return sum;
	}
}	bt;

struct BIT2 {
	static const int M = 1005;
	int T[M][M];
	void modify(int i, int j, int m)
	{
		for ( ; i < M; i += i & (-i)) 
			for (int k = j; k < M; k += k& (-k))
				T[i][k] += m;
	}
	int cnt(int i, int j)
	{
		int sum = 0;
		for ( ; i ; i -=i & (-i))
			for (int k = j; k ; k -= k& (-k))
				sum += T[i][k];
		return sum;
	}
	int ask(int i, int j, int x, int y) 
	{
		return cnt(x, y) - cnt(i - 1, y) - cnt(x, j - 1) + cnt(i - 1, j - 1);
	}
}	bt2;

