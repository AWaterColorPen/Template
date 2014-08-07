#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#define INF 50005
#define HEAP_SIZE 50005
#define inf 0x0f0f0f0f

using namespace std;
vector <int> vec[INF],dis[INF];
struct NODE {
	int d, i;
}	now;
struct HEAP {
	NODE hp[HEAP_SIZE], tmp;
	int pos[HEAP_SIZE], size;
	void push(int d, int v)
	{
		int i, n;	tmp.d=d, tmp.i=v;
		if (n=pos[v], pos[v]==0) n=++size;
		for (i=n>>1; i && hp[i].d>tmp.d; n=i, i=n>>1)
			hp[n]=hp[i], pos[hp[n].i]=n;
		hp[n]=tmp, pos[hp[n].i]=n;
	}
	void pop()
	{
		int i, j=1;
		for (tmp=hp[size--], i=j<<1; i<=size; j=i, i=j<<1)
		{
			if (i+1<=size && hp[i].d>hp[i+1].d) i++;
			if (tmp.d<hp[i].d) break;
			hp[j]=hp[i], pos[hp[j].i]=j;
		}
		hp[j]=tmp, pos[hp[j].i]=j;
	}
	NODE top() { return hp[1]; }
}	q;
int Dis[INF];
void _addedge(int i, int j, int d) { vec[i].push_back(j), dis[i].push_back(d); }
bool Dijkstra(int s, int end)
{
	int i, j, t, siz; 
	memset(Dis, 0x0f, sizeof(Dis));
	for (Dis[s]=0, q.push(0,s); q.size; )
	{
		now=q.top(), q.pop();
		for (siz=vec[i=now.i].size(), j=0; j<siz; j++)
			if (Dis[t=vec[i][j]]>now.d+dis[i][j])
				Dis[t]=now.d+dis[i][j], q.push(Dis[i],i);
	}
	return (Dis[end]<inf);
}
