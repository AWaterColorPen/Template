#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

#include <tr1/unordered_map>

using namespace std;
using namespace std::tr1;

unordered_map <int, int> umap;

struct NODE {
	int s, x, y, c, val;
	NODE () {}
	NODE (int s, int x, int y, int c, int val) : s(s), x(x), y(y), c(c), val(val) {}
	int hash() { return val; }
	bool operator == (const NODE &o) { return o.val == val; }
}	;

struct HASHTABLE {
	static const int M = 10001 , HASH_SIZE = 10001;
	PT st[M];
	int hash[M], pos[M], size;
	int insert(PT n)
	{
		int m = n.hash() % HASH_SIZE;
		for (int i = hash[m]; i; i = pos[i]) if (n == st[i]) return 1;
		return ++size, st[size] = n, pos[size] = hash[m], hash[m] = size, 0;
	}
	void clear() { memset(hash, size = 0, sizeof(hash)); }
}	F;
