#include <iostream>
#include <cstdio>
#include <vector>
#define INF 905

using namespace std;
int Fath[INF], Cnt[INF];
vector <int> vec[INF], qus[INF];
bool vis[INF];
void _addedge(int i, int j) { vec[i].push_back(j); //qus[i].push_back(j); }
int Find(int n)
{
	if (Fath[n]==n) return n;
	return Fath[n]=Find(Fath[n]);
}
void Tarjan_LCA(int n)
{
	int i, j, siz; Fath[n]=n;
	for (i=0, siz=vec[n].size(); i<siz; i++)
		Tarjan_LCA(j=vec[n][i]), Fath[j]=n;
	for (vis[n]=true, i=0, siz=qus[n].size(); i<siz; i++)
		if (vis[j=qus[n][i]]==true)
			Find(j), Cnt[Fath[j]]++;
}
