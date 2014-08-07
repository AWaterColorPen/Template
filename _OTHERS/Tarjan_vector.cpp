#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#define INF 5005

using namespace std;
vector <int> vec[INF];
int Dfn[INF], Low[INF], Blo[INF], Stack[INF], Cnt, Now, Block;
bool Instack[INF];
void _addedge(int i, int j) { vec[i].push_back(j); }
void Tarjan(int n)
{
	int i, j, siz;
	Dfn[n]=Low[n]=++Cnt, Instack[Stack[++Now]=n]=true;
	for (j=0, siz=vec[n].size(); j<siz; j++)
		if (Dfn[i=vec[n][j]]==0)
			Tarjan(i), Low[n]=min(Low[n], Low[i]);
		else if (Instack[i]) Low[n]=min(Low[n], Low[i]);
	if (Low[n]==Dfn[n] && ++Block)
		do Blo[i=Stack[Now--]]=Block, Instack[i]=false;
		while (i!=n);
}
