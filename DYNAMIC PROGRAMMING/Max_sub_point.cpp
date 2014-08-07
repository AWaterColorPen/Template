#include <algorithm>
#include <iostream>
#include <cstdio>
#define INF 5050

using namespace std;
struct PT {
	int x, y;
	PT () {}
	PT (int x, int y) : x(x), y(y) {} 
}	pt[INF];
bool cmp_i(PT a, PT b) { return a.x<b.x; }
bool cmp_j(PT a, PT b) { return a.y<b.y; }
int Max_sub_point(int n, int m, int k)
{
	int now, ans=0, u, d;
	pt[++k]=PT(0, 0); pt[++k]=PT(0, m);
	pt[++k]=PT(n, 0); pt[++k]=PT(n, m);
	sort(pt+1, pt+k+1, cmp_i);
	for (int i=1, j; i<=k; i++)
	{
		for (j=i+1, now=pt[i].x; j<=k && pt[j].x==now; j++);
		for (u=0, d=m; j<=k; j++)
		{
			ans=max(ans, (pt[j].x-now)*(d-u));
			if (pt[j].y>pt[i].y) d=min(d, pt[j].y);
			else u=max(u, pt[j].y);
		}
	}
	for (int i=k, j; i; i--)
	{
		for (j=i-1, now=pt[i].x; j && pt[j].x==now; j--);
		for (u=0, d=m; j; j--)
		{
			ans=max(ans,(now-pt[j].x)*(d-u));
			if (pt[j].y>pt[i].y) d=min(d, pt[j].y);
			else u=max(u, pt[j].y);
		}
	}
	sort(pt+1, pt+k+1, cmp_j);
	for (int i=1; i<k; i++)
		ans=max(ans, (pt[i+1].j-pt[i].y)*n);
	return ans;
}
