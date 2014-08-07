#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#define INF 5005
#define inf 0x0f0f0f0f

using namespace std;
vector <int> vec[INF], dis[INF];
int Dis[INF]; bool Inq[INF];
void _addedge(int i, int j, int d) { vec[i].push_back(j), dis[i].push_back(d); }
int SPFA(int s, int end)
{
	int i, j, t, siz; queue <int> q;
	memset(Dis, 0x0f, sizeof(Dis)), memset(Inq, true, sizeof(Inq));
	for (Dis[s]=0, Inq[s]=0, q.push(s); q.empty()==0; )
	{
		i=q.front(), q.pop(), Inq[i]=true;
		for (j=0, siz=vec[i].size(); j<siz; j++)
			if (Dis[t=vec[i][j]]>Dis[i]+dis[i][j])
				if (Dis[t]=Dis[i]+dis[i][j], Inq[t])
					Inq[t]=0, q.push(t);
	}
	return Dis[end];
}
