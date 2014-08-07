#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;
struct NODE {
	int id, n;
	bool operator < (const NODE o) const{
		return n<o.n;
	}
};

struct NODE {
	int id, n;
};
struct cmp {
	bool operator() (const NODE &a, const NODE &b) {
		return a.n>b.n;
	}
};
priority_queue <NODE, vector<NODE>, cmp> small_q;

priority_queue <pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > small_q;

priority_queue <int, vector<int>, greater<int> > small_q;
priority_queue <int> large_q;
