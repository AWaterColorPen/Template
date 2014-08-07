#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

struct TRIE {
	static const int M = 250005 ;
	int val[M], ch[M][26], ID[128], size;
	TRIE() { for (int i=0; i<26; i++) ID[i+'a']=i; }
	void clear() {
		memset(ch[0], 0, sizeof(ch[0]));
		memset(val, size=0, sizeof(val));
	}
	void insert(char *s, int _val)
	{
		int id=0, i, j;
		for (i=0; s[i]; i++)
		{
			if(j=ID[s[i]], ch[id][j]==0)
				ch[id][j]=++size, memset(ch[size], 0, sizeof(ch[size]));
			id=ch[id][j];
		}
		val[id]+=_val;
	}
	int find(char *s)
	{
		int id=0, i, j;
		for (i=0; s[i]; i++)
		{
			j=ID[s[i]];
			if (id=ch[id][j], id==0) return 0;
		}
		return val[id];
	}
}	trie;
