#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#define inf 0x0f0f0f0f

using namespace std;

int n, m;
int vis[25][25], maze[25][25];
	
int used(int x, int y) { return (x > 0 && x <= n && y > 0 && y <= m) ; }
	
struct PT {
	int x, y;
	PT () {}
	PT (int x, int y) : x(x) , y(y) {}
	bool operator < (const PT &o) const { return (x == o.x) ? (y < o.y) :  (x < o.x) ; }
}	;

struct BLOCK {
	vector <PT> p;
	int mx, my;
	bool operator == (const BLOCK &o) const {
		for (int i = 0; i < p.size(); i++) if (p[i].x != o.p[i].x || p[i].y != o.p[i].y) return 0;
		return 1;
	}
	void bfs(int sx, int sy)
	{
		queue <PT> q;
		int X[4]={0, 1, 0,-1};
		int Y[4]={1, 0,-1, 0};
		
		for (q.push(PT(sx, sy)), vis[sx][sy] = 1; q.empty() == 0; )
		{
			int x = q.front().x, y = q.front().y; q.pop();
			p.push_back(PT(x, y));
			for (int t = 0; t < 4; t++)
			{
				int i = x + X[t], j = y + Y[t];
				if (vis[i][j] == 0 && used(i, j) && maze[i][j] == maze[sx][sy])
					vis[i][j] = 1, q.push(PT(i, j));
			}
		}
	}
	void adjust()
	{
		int x = 99, y = 99;
		for (int i = 0; i < p.size(); i++) x = min(x, p[i].x), y = min(y, p[i].y);
		for (int i = 0; i < p.size(); i++) p[i].x -= x, p[i].y -= y;
		mx = my = 0;
		for (int i = 0; i < p.size(); i++) mx = max(mx, p[i].x), my = max(my, p[i].y);
		sort(p.begin(), p.end());
	}
	void full(int x, int y, char c)
	{
		for (int i = 0; i < p.size(); i++) maze[p[i].x + x][p[i].y + y] = c;
	}
	BLOCK rotate()
	{
		BLOCK ret;
		for (int i = 0; i < p.size(); i++) ret.p.push_back(PT(p[i].y, mx - p[i].x));
		return ret;
	}
	BLOCK reflex()
	{
		BLOCK ret;
		for (int i = 0; i < p.size(); i++) ret.p.push_back(PT(mx - p[i].x, p[i].y));
		return ret;
	}
}	;