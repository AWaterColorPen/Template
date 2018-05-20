#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long LL;
const LL inf = 0x0f0f0f0f0f0f0f0fLL;
const int NN = 100005;

int idx;
struct NODE {
	static const int KD = 2;
	int id;
	_int64 x[KD], dis;
	void read(int m) { for (int i = 0; i < m; i++) scanf("%I64d", &x[i]); }
	void show(int m) { for (int i = 0; i < m; i++) printf("%I64d%c", x[i], i == m - 1 ? '\n' : ' '); }
	bool operator < (const NODE &o) const { return x[idx] < o.x[idx] ; }
}	tmp, pt[INF];

struct KDT
{
	static const int M = 100005 ;
	int mark[M], spt[M], D;
	NODE tre[M], ret;
	void clear() { memset(mark, 0, sizeof(mark)); }
	template <class TP> TP sqr(TP x) { return x * x; }
	void build(int l, int r, int cut)
	{
		if (l > r) return;
		int mid = (l + r) / 2;
		idx = spt[mid] = cut;
		nth_element(tre + l, tre + mid, tre + r + 1);
		build(l, mid - 1, (cut + 1) % D);
		build(mid + 1, r, (cut + 1) % D);
	}
	void query(int l, int r, NODE &o)
	{
		if (l > r) return;
		int mid = (l + r) / 2;
		_int64 dis = 0;
		for (int i = 0; i < D; i++) dis += sqr(o.x[i] - tre[mid].x[i]);
		
		if (mark[tre[mid].id] == 0 && dis < o.dis) o.dis = dis, ret = tre[mid];
		
		_int64 rad = sqr(o.x[spt[mid]] - tre[mid].x[spt[mid]]);
		if (o.x[spt[mid]] < tre[mid].x[spt[mid]])
		{
			if (query(l, mid - 1, o), rad <= o.dis) query(mid + 1, r, o);
		}
		else
		{
			if (query(mid + 1, r, o), rad <= o.dis) query(l, mid - 1, o);
		}
	}
}	kdt;