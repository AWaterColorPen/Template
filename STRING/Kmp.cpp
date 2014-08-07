#include <iostream>
#include <cstring>
#include <cstdio>
#define INF 10005

using namespace std;
int next[INF];
void get_next(char *s, int len)
{
	int i, j=0;
	for (next[0]=-1, i=2; i<=len; i++)
	{
		while (j>-1 && s[i-1]!=s[j]) j=next[j];
		next[i]=++j;
	}
}
int kmp(char *s, char *t, int ls, int lt)
{
	int i, j=0, cnt=0;
	for (i=1; i<=lt; i++)
	{
		while (j && s[j]!=t[i-1]) j=next[j];
		if (s[j]==t[i-1]) j++;
		cnt+=(j==ls);
	}
	return cnt;
}
