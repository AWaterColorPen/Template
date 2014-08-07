#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int X[2][2]={{ 3, 1}, { 2, 0}};
struct QDT {
	static const int M = 0x80000;
	int size;
	
	struct NODE {
		int x1, y1, x2, y2, sum, ch[4];
		NODE () {}
		NODE (int x1, int y1, int x2, int y2, int sum = 0) : x1(x1), y1(y1), x2(x2), y2(y2), sum(sum) {
			for (int i = 0; i < 4; i++) ch[i] = 0;
		}
	}	T[M];
	
	int build(int x1, int y1, int x2, int y2)
	{
		T[++size] = NODE(x1, y1, x2, y2);
		return size;
	}
	
	void modify(int x, int y, int m, int n)
	{
		if (T[n].x1 == T[n].x2 && T[n].y1 == T[n].y2) { T[n].sum += m; return ; }
		int mx = (T[n].x1 + T[n].x2) >> 1, my = (T[n].y1 + T[n].y2) >> 1;
		int i = X[x <= mx][y <= my], x1, y1, x2, y2;

		if (i & 1) x1 = mx + 1, x2 = T[n].x2; else x1 = T[n].x1, x2 = mx;
		if (i & 2) y1 = my + 1, y2 = T[n].y2; else y1 = T[n].y1, y2 = my;

		if (T[n].ch[i] == 0) T[n].ch[i] = build(x1, y1, x2, y2);
		modify(x, y, m, T[n].ch[i]);
		
		T[n].sum = 0;
		for (i = 0; i<4; i++) if (T[n].ch[i]) T[n].sum += T[T[n].ch[i]].sum;
	}
	
	bool cross(int x1, int y1, int x2, int y2, int n)
	{
		return (x2 < T[n].x1 || T[n].x2 < x1 || y2 < T[n].y1 || T[n].y2 < y1);
	}
	
	int ask(int x1, int y1, int x2, int y2, int n)
	{
		if (n == 0 || cross(x1, y1, x2, y2, n)) return 0;
		if (x1 <= T[n].x1 && T[n].x2 <= x2 && y1 <= T[n].y1 && T[n].y2 <= y2) return T[n].sum;
		int sum = 0;
		for (int i = 0; i < 4; i++) sum += ask(x1, y1, x2, y2, T[n].ch[i]);
		return sum;
	}
}	qt;