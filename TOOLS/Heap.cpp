#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

struct HEAP {
	static const int M = 50005;
	struct NODE {
		int val, id;
		NODE () {}
		NODE (int val, int id) : val(val), id(id) {}
	} hp[M], tmp;
	int pos[M], size;
	
	void push(NODE tt)
	{
		int n = pos[tt.id];
		if (n == 0) n = ++size;
		for (int i = n >> 1; i && hp[i].val > tt.val; n = i, i = n >> 1)
			hp[n] = hp[i], pos[hp[n].id] = n;
		hp[n] = tt;
		pos[hp[n].id] = n;
	}
	void pop()
	{
		NODE tt = hp[size--];
		for (int j = 1, i = 2; i <= size; j = i, i = j << 1)
		{
			if (i + 1 <= size && hp[i].val > hp[i + 1].val) i++;
			if (tt.val < hp[i].val) break;
			hp[j] = hp[i];
			pos[hp[j].id] = j;
		}
		hp[j] = tt;
		pos[hp[j].id] = j;
	}
	NODE top() { return hp[1]; }
}	q;

