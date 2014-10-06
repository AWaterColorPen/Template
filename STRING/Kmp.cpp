#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const NN = 10005;
int next[NN];
void get_next(char s[], int len)
{
	next[0] = -1;
	for (int i = 2, j = 0; i <= len; i++)
	{
		while (j > -1 && s[i - 1] != s[j]) j = next[j];
		next[i] = ++j;
	}
}
int kmp(char s[], char t[], int ls, int lt)
{
	int cnt = 0;
	for (int i = 1, j = 0; i <= lt; i++)
	{
		while (j && s[j] != t[i - 1]) j = next[j];
		if (s[j] == t[i - 1]) j++;
		cnt += (j == ls);
	}
	return cnt;
}
