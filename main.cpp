#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

const long double eps = 1e-8 ;
const long double PI = acos(-1) ;
int sgn(double x) { return (x < -eps) ? -1 : (x > eps) ; }

//2D PT
struct PT {
	double x, y;
	PT () {}
	PT (double x, double y) : x(x), y(y) {}
	PT operator + (const PT o) { return PT(x + o.x, y + o.y) ; }
	PT operator - (const PT o) { return PT(x - o.x, y - o.y) ; }
	PT operator * (double s) { return PT(x * s, y * s) ; }
	PT operator / (double s) { return PT(x / s, y / s) ; }
	bool operator < (const PT &o) const { return y < o.y - eps || (y < o.y + eps && x < o.x - eps) ; }
	bool operator == (const PT &o) const { return !sgn(y - o.y) && !sgn(x - o.x) ; }
	bool operator != (const PT &o) const { return sgn(y - o.y) || sgn(x - o.x) ; }
	void rd() { scanf("%lf %lf", &x, &y) ; }
	double ag() { return atan2(y, x) ; }
}	;

bool cmpx(PT a, PT b) { return a.x < b.x - eps || (a.x < b.x + eps && a.y < b.y - eps); }
bool cmpy(PT a, PT b) { return a.y < b.y - eps || (a.y < b.y + eps && a.x < b.x - eps); }

double cpr(PT a, PT b) { return a.x * b.y - a.y * b.x ; }
double dpr(PT a, PT b) { return a.x * b.x + a.y * b.y ; }

double cpr(PT a, PT b, PT c) { return cpr(b - a, c - a) ; }
double dpr(PT a, PT b, PT c) { return dpr(b - a, c - a) ; }

double vlen(PT a) { return sqrt(dpr(a, a)) ; }
double dist(PT a, PT b) { return vlen(a - b) ; }

struct LE {
	PT a, b, v;
	double k;
	LE () {}
	LE (PT a, PT b) : a(a), b(b) { k = (b - a).ag(); v = PT(a.y - b.y, b.x - a.x); v = v / vlen(v) ; }
	bool operator < (const LE &o) const { return sgn(k - o.k) == 0 ? cpr(a, o.a, b) > eps : sgn(k - o.k) < 0; }
}	;

struct CLE {
	PT c;
	double r;
	CLE () {}
	CLE (PT c, double r) : c(c), r(r) {}
	bool operator == (const CLE &o) { return c == o.c && !sgn(r - o.r) ; }
	bool operator != (const CLE &o) { return c != o.c || sgn(r - o.r) ; }
	void rd() { c.rd(); scanf("%lf", &r); }
	PT pt(double k) { return c + PT(cos(k), sin(k)) * r; }
	double ag(PT a) { return (a - c).ag() ; }
	double sector0(double k1, double k2)
	{
		if (k1 > k2 + eps) return sector0(k1, PI) + sector0(-PI, k2);
		return (k2 - k1) * r * r / 2;
	}
	double sector1(double k1, double k2) { return adjust(k2 - k1) * r * r / 2; }
	double adjust(double kk) 
	{
		if (kk < -PI) kk += PI * 2;
		if (kk > PI) kk -= PI * 2;
		return kk;
	}
}	;

//判两点ab与直线cd相对位置, 点在直线上0, 同侧1, 异侧-1
int plside(PT a, PT b, PT c, PT d) { return sgn(cpr(c, a, d) * cpr(c, b, d)); }

//判两线段ab cd严格相交
bool ints_ex(PT a, PT b, PT c, PT d) { return plside(a, b, c, d) == -1 && plside(c, d, a, b) == -1; }

//判两线段ab cd非严格相交
bool ints_in(PT a, PT b, PT c, PT d)
{
	int d1 = plside(a, b, c, d), d2 = plside(c, d, a, b);
	if (d1 == 1 || d2 == 1) return 0;
	if (d1 == -1 || d2 == -1) return 1;
	return dpr(c, a, b) < eps || dpr(d, a, b) < eps || dpr(a, c, d) < eps || dpr(b, c, d) < eps;
}

//求直线ab和直线cd的交点
PT ints(PT a, PT b, PT c, PT d)
{
	double v1 = cpr(a, b, c), v2 = cpr(b, a, d);
	return (c * v2 + d * v1) / (v2 + v1);
}

//点p到直线ab上的最近点
PT ptoline(PT p, PT a, PT b)
{
	PT t(p.x + a.y - b.y, p.y + b.x - a.x) ;
	return ints(p, t, a, b);
}

//点p到直线ab距离
double disptoline(PT p, PT a, PT b) { return fabs(cpr(p, a, b)) / dist(a, b); }

//点p到线段ab上的最近点
PT ptoseg(PT p, PT a, PT b)
{
	PT t = p + PT(a.y - b.y, b.x - a.x) ;
	if (plside(a, b, p, t) == 1) return dist(p, a) < dist(p, b) ? a : b;
	return ints(p, t, a, b);
}

//点到线段距离
double disptoseg(PT p, PT a, PT b)
{
	PT t = p + PT(a.y - b.y, b.x - a.x) ;
	if (plside(a, b, p, t) == 1) return min(dist(p, a),  dist(p, b));
	return disptoline(p, a, b);
}

//极角排序
PT curp ;
bool cmp_angle(PT a, PT b)
{
	int res = sgn(cpr(curp, a, b));
	if (res > 0) return 1;
	if (res < 0) return 0;
	return dist(a, curp) < dist(b, curp) ;
}

bool cmp_angle2(PT a, PT b)
{
	double k1 = a.ag();
	double k2 = b.ag();
	return (sgn(k1 - k2) == 0) ? (vlen(a) < vlen(b)) : (sgn(k1 - k2) < 0);
}

//点v绕着点p逆时针旋转angle并放大scale倍
PT protate(PT v, PT p, double ag, double scale)
{
	PT t = PT(cos(ag), sin(ag)) * scale;
	v = v - p;
	p.x += v.x * t.x - v.y * t.y;
	p.y += v.x * t.y + v.y * t.x;
	return p;
}

//三角形外心
PT circumcenter(PT a, PT b, PT c)
{
	PT u1 = (a + b) / 2;
	PT u2 = u1 + PT(a.y - b.y, b.x - a.x);
	PT v1 = (a + c) / 2;
	PT v2 = v1 + PT(a.y - c.y, c.x - a.x);
	return ints(u1, u2, v1, v2);
}

//三角形内心
PT incenter(PT a, PT b, PT c)
{
	double m, n;
	m = (b - a).ag();
	n = (c - a).ag();
	PT u = a + PT(cos((m + n) / 2), sin(m + n) / 2);
	m = (a - b).ag()
	n = (c - b).ag();
	PT v = b + PT(cos((m + n) / 2), sin(m + n) / 2);
	return ints(a, u, b, v);
}

//三角形垂心
PT perpencenter(PT a, PT b, PT c)
{

	PT u = c + PT(a.y - b.y, b.x - a.x);
	PT v = b + PT(a.y - c.y, c.x - a.x);
	return ints(c, u, b, v);
}

//重心
//到三角形三顶点距离的平方和最小的点，三角形内到三边距离之积最大的点
PT barycenter(PT a, PT b, PT c) { return (a + b + c) / 3; }

//多边形重心
PT barycenter(PT p[], int n)
{
	PT ret(0, 0);
	double t1 = 0, t2;
	for (int i = 1; i < n - 1; i++)
		if (sgn(t2 = cpr(p[i+1], p[0], p[i])))
		{
			ret = ret + (p[0] + p[i] + p[i+1]) / 3 * t2;
			t1 += t2;
		}
	if (sgn(t1)) ret = ret / t1;
	return ret;
}

//计算圆与圆的交点，保证圆与圆有交点，圆心不重合
void ints_circle_circle(PT c1, double r1, PT c2, double r2, PT &p1, PT &p2)
{
	double d = dist(c1, c2);
	double cosA = (r1 * r1 + d * d - r2 * r2) /  (r1 * d * 2);
	PT v1 = (c2 - c1) * r1 / d;
	PT v2 = PT(-v1.y, v1.x) * sqrt(1 - cosA * cosA);
	PT vv = c1 + v1 * cosA;
	p1 = vv + v2;
	p2 = vv - v2;
}

//计算直线与圆的交点，保证直线与圆有交点
//计算线段与圆的交点可用这个函数后判点是否在线段上
void ints_line_circle(PT c, double r, PT a, PT b, PT &p1, PT &p2)
{
	PT p = c + PT(b.y - a.y, a.x - b.x);
	p = ints(p, c, a, b);
	double d = dist(p, c), t = sqrt(r * r - d * d) / dist(a, b);
	p1 = p + (a - b) * t;
	p2 = p - (a - b) * t;
}

//两圆公切线切点对应的角度

//辅助函数
void find_tp(PT p, double c, double &ag1, double &ag2)
{
	double v1, v2;
	v1 = fabs(c) > eps ? (p * c).ag() : p.ag();
	v2 = acos(fabs(c) / vlen(p));
	ag1 = v1 - v2;
	ag2 = v1 + v2;
}

//外公切线(所求角度t1 t2均对两圆均适用)
void tangent1(PT c1, double r1, PT c2, double r2, double &t1, double &t2)
{
	find_tp(c2 - c1, r1 - r2, t1, t2);
}

//内公切线(所求角度t1 t2均对圆c1而言,对圆c2则需加(减)PI)
void tangent2(PT c1, double r1, PT c2, double r2, double &t1, double &t2)
{
	find_tp(c2 - c1, r1 + r2, t1, t2);
}

//判定凸多边形，顶点按顺时针或逆时针给出，允许相邻边共线(n>=3)
int is_convex(PT p[], int n)
{
	int s[3] = {1, 1, 1};
	for (int i = 0; i < n && (s[0] | s[2]); i++)
		s[sgn(cpr(p[i], p[(i + 1) % n], p[(i + 2) % n])) + 1] = 0;
	return s[0] | s[2];
}

//判定凸多边形，顶点按顺时针或逆时针给出，不允许相邻边共线
int is_convex_v2(PT p[], int n)
{
	int s[3] = {1, 1, 1};
	for (int i = 0; i < n && s[1] && (s[0] | s[2]); i++)
		s[sgn(cpr(p[i], p[(i + 1) % n], p[(i + 2) % n])) + 1] = 0;
	return s[1] && (s[0] | s[2]);
}

//判点在凸多边形内或多边形边上，顶点按顺时针或逆时针给出
int inside_convex(PT q, PT p[], int n)
{
	int s[3] = {1, 1, 1};
	for (int i = 0; i < n && (s[0] | s[2]); i++)
		s[sgn(cpr(p[i], p[(i + 1) % n], q)) + 1] = 0;
	return s[0] | s[2];
}

//判点在凸多边形内，顶点按顺时针或逆时针给出,在多边形边上返回0
int inside_convex_v2(PT q, PT p[], int n)
{
	int s[3] = {1, 1, 1};
	for (int i = 0; i < n && s[1] && (s[0] | s[2]); i++)
		s[sgn(cpr(p[i], p[(i + 1) % n], q)) + 1] = 0;
	return s[1] && (s[0] | s[2]);
}

//求多边形p[]的凸包，严格
void make_ch_jm_ex(PT p[], PT o[], int n, int &top)
{
	top = 0;
	sort(p, p + n);
	for (int i = 0, j, k = 1; i < 2 * n - 1; i++)
	{
		j = (i < n) ? i : 2 * (n - 1) - i;
		if (i == n) k = top;
		while (top > k && cpr(o[top - 2], o[top - 1], p[j]) < eps) top--;
		o[top++] = p[j];
	}
	top -- ;
}

//求多边形p[]的凸包，严格
void make_ch_gs_ex(PT p[], PT o[], int n, int &top)
{
	top = 0;
	curp = p[0];
	sort(p + 1, p + n, cmp_angle);
	for (int i = 0; i < n; i++)
	{
		while (top > 1 && cpr(o[top - 2], o[top - 1], p[i]) < eps) top--;
		o[top++] = p[i];
	}
}

//求多边形面积，p[]为顶点，逆时针为正
double poly_area(PT p[], int n)
{
	double ans = 0;
	for (int i = 1; i < n - 1; i++) ans += cpr(p[0], p[i], p[i + 1]);
	return ans / 2;
}

//计算多边形外角和，逆时针为正
double angsum(PT p[], int n)
{
	double ans = 0;
	for (int i = 0; i < n; i++)
	{
		PT A = p[i], B = p[(i+1)%n], C = p[(i+2)%n];
		double tmp = PI - acos(dpr(B, A, C) / dist(A, B) / dist(B, C));
		if (cpr(A, B, C) < -eps) tmp = -tmp;
		ans += tmp;
	}
	return ans;
}
//半平面交(切割直线为ab，p[]为原始多边形，顶点数为n
//tmp[]临时用来存放点集，交后多边形仍放入p[])
//多边形点序为逆时针，切割线左侧为有效区
void half_plane_its(PT a, PT b, PT p[], int &n, PT tmp[])
{
	int tot = 0;
	for (int i = 0; i < n; i++)
	{
		int now = sgn(cpr(a, b, p[i]));
		int next = sgn(cpr(a, b, p[(i+1)%n]));
		if (now >= 0) tmp[tot++] = p[i];
		if (now * next == -1) tmp[tot++] = ints(a, b, p[i], p[(i + 1) % n]);
	}
	n = tot;
	for (int i = 0; i < n; i++) p[i] = tmp[i];
}

bool parallel(LE l1, LE l2) { return sgn(cpr((l1.a - l1.b), (l2.a - l2.b))) == 0; }

PT lineints(LE l1, LE l2) { return ints(l1.a, l1.b, l2.a, l2.b); }

//l[]为加入的直线，n为直线个数，p[]为输出的交点，m为交点数
//q[]临时用来存放直线队列
//直线为向量，向量左侧为有效区
void hpi(LE l[], int n, PT p[], int &m, LE q[])
{
	int tot = 0;
	sort(l, l + n);
	for (int i = 0; i < n; i++) if (i == 0 || sgn(l[i].k - l[tot-1].k)) l[tot++] = l[i];
	
	n = tot, m = 0;
	int hh = 0, tt = -1;
	for (int i = 0; i < n; i++)
	{
		if (hh < tt && (parallel(q[hh], q[hh+1]) || parallel(q[tt], q[tt-1]))) return ;
		while (hh < tt && cpr(l[i].a, l[i].b, lineints(q[tt], q[tt-1])) < eps) tt--;
		while (hh < tt && cpr(l[i].a, l[i].b, lineints(q[hh], q[hh+1])) < eps) hh++;
		q[++tt] = l[i];
	}
	while (hh < tt && cpr(q[hh].a, q[hh].b, lineints(q[tt], q[tt-1])) < eps) tt--;
	while (hh < tt && cpr(q[tt].a, q[tt].b, lineints(q[hh], q[hh+1])) < eps) hh++;
	
	q[tt+1] = q[hh];
	for (int i = hh; i <= tt; ++i) p[m++] = lineints(q[i], q[i+1]);
	m = unique(p, p+m) - p;
}

//旋转卡壳 凸包直径
double rotating_calipers(PT p[], int n)
{
	double ans = 0;
	int q = 0;
	for (int i = 0; i < n; i++)
	{
		while (cpr(p[i], p[(i+1)%n], p[q]) < cpr(p[i], p[(i+1)%n], p[(q+1)%n])) q = (q + 1) % n;
		ans = max(ans, max(dist(p[i], p[q]), dist(p[i+1], p[q])));
	}
	return ans * ans;
}

//旋转卡壳 两凸包间的最短距离
double rotating_calipers(PT p[], int n1, PT q[], int n2)
{
	int pp = 0, qq = 0;
	for (int i = 0; i < n1; i++) if (p[i] < p[pp]) pp = i;
	for (int i = 0; i < n2; i++) if (q[qq] < q[i]) qq = i;
	double ans =1e20;
	for (int i = 0; i < n1 + n2; i++)
	{
		if (cpr(p[(pp+1)%n1] - p[pp], q[(qq+1)%n2] - q[qq]) < -eps)
		{
			ans = min(ans, disptoseg(q[qq], p[pp], p[(pp+1)%n1]));
			pp = (pp + 1) % n1;
		}
		else
		{
			ans = min(ans, disptoseg(p[pp], q[qq], q[(qq+1)%n2]));
			qq = (qq + 1) % n2;
		}
	}
	return ans;
}

//求最近点对 要先cmpx排序
//double dis(PT a, PT b) { return (a.mark == b.mark) ? 1e20 : vlen(a - b); }

double p2pmindis(PT p[], PT o[], int l, int r) 
{
	if (r == l) return 1e20;
	if (r == l + 1) return dis(p[l], p[r]);

	int mid = (l + r) >> 1;
	double ans = min(p2pmindis(p, o, l, mid), p2pmindis(p, o, mid + 1, r));

	int cnt = 0;
	for (int i = l; i <= r; i++)
		if (p[i].x > p[mid].x - ans + eps && p[i].x < p[mid].x + ans - eps)
		   o[cnt++] = p[i];

	sort(o, o + cnt, cmpy);
	for (int i = 0; i < cnt; i++)
		for (int j = i + 1; j < cnt; j++)
		{
			if (o[j].y - o[i].y > ans - eps) break;
			ans = min(ans, dis(o[i], o[j]));
		}

	return ans;
}

//最小包围圆，增量算法
CLE mincircle(PT p[], int n) 
{
	random_shuffle(p, p + n);
	CLE ret(p[0], 0);
	
	for (int i = 0; i < n; i++) 
		if (dist(ret.c, p[i]) > ret.r + eps)
		{
			ret = CLE(p[i], 0);
			for (int j = 0; j < i; j++)
				if (dist(ret.c, p[j]) > ret.r + eps)
				{
					PT t = (p[i] + p[j]) / 2;
					ret = CLE(t, dist(t, p[j]));
					for (int k = 0; k < j; k++)
						if (dist(ret.c, p[k]) > ret.r + eps)
						{
							t = circumcenter(p[i], p[j], p[k]);
							ret = CLE(t, dist(t, p[k]));
						}
				}
		}
	return ret;
}

//计算圆与圆的相交的面积并
double area_circle_circle(PT c1, double r1, PT c2, double r2)
{
	if (r1 < r2) swap(c1, c2);
	if (r1 < r2) swap(r1, r2);
	
	double d = dist(c1, c2);
	if (d > r1 + r2 - eps) return 0;
	if (d < r1 - r2 + eps) return r2 * r2 * PI;
	
	double cosA1 = (r1 * r1 + d * d - r2 * r2) / (r1 * d * 2);
	double cosA2 = (r2 * r2 + d * d - r1 * r1) / (r2 * d * 2);
	double th1 = acos(cosA1) * 2;
	double th2 = acos(cosA2) * 2;
	
	double s1 = th1 / 2 * r1 * r1 -  r1 * r1 * sin(th1) / 2;
	double s2 = th2 / 2 * r2 * r2 -  r2 * r2 * sin(th2) / 2;
	
	return s1 + s2;
}

//三角形剖分，圆与三角形的交
double delaunay_circle(PT a, PT b, PT o, double r)
{
	int d1 = (dist(a, o) > r - eps);
	int d2 = (dist(b, o) > r - eps);
	int dd = (disptoseg(o, a, b) < r - eps);
	
	CLE oo = CLE(o, r);
	double ka = oo.ag(a);
	double kb = oo.ag(b);
	
	if (dd)
	{
		if (d1 == 0 && d2 == 0) return cpr(o, a, b) / 2;
		
		PT p1, p2;
		ints_line_circle(o, r, a, b, p1, p2);
		double k1 = oo.ag(p1);
		double k2 = oo.ag(p2);
		
		if (d1 == 1 && d2 == 1)
		{
			if (dist(p1, a) > dist(p2, a)) swap(p1, p2), swap(k1, k2);
			double ans = oo.sector1(ka, k1) + oo.sector1(k2, kb);
			return ans + cpr(o, p1, p2) / 2;
		}
		
		if (disptoseg(p1, a, b) > eps) swap(p1, p2), swap(k1, k2);
		
		if (d1 == 1 && d2 == 0) return oo.sector1(ka, k1) + cpr(o, p1, b) / 2;
		if (d1 == 0 && d2 == 1) return oo.sector1(k1, kb) + cpr(o, a, p1) / 2;
	}
	
	return oo.sector1(ka, kb);
}

//3D PT
struct PT3 {
	double x, y, z;
	PT3 () {}
	PT3 (double x, double y, double z) : x(x), y(y), z(z) {}
	PT3 operator + (const PT3 o) { return PT3(x + o.x, y + o.y, z + o.z) ; }
	PT3 operator - (const PT3 o) { return PT3(x - o.x, y - o.y, z - o.z) ; }
	PT3 operator * (const PT3 o) { return PT3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x) ; } // * sin
	double operator ^ (PT3 o) { return x * o.x + y * o.y + z * o.z ; } // * cos
	PT3 operator * (double s) { return PT3(x * s, y * s, z * s) ; }
	PT3 operator / (double s) { return PT3(x / s, y / s, z / s) ; }
	bool operator < (const PT3 &o) const { return z < o.z - eps || (z < o.z + eps && y < o.y - eps) || (z < o.z + eps && y < o.y + eps && x < o.x - eps) ; }
	void rd() { scanf("%lf %lf %lf", &x, &y, &z) ; }
}	;

double dpr(PT3 a, PT3 b) { return a ^ b ; }
double dpr(PT3 a, PT3 b, PT3 c) { return dpr(b - a, c - a) ; }

double vlen(PT3 a) { return sqrt(a ^ a) ; }
double dist(PT3 a, PT3 b) { return vlen(a - b) ; }

struct SPH {
	PT3 o;
	double r;
	void rd() { o.rd(); scanf("%lf", &r); }
}	;

//点p到直线ab距离
double disptoline(PT3 p, PT3 a, PT3 b) { return vlen((b - p) * (a - p)) / dist(a, b); }

void ints_line_sphere(PT3 s, double r, PT3 a, PT3 b, PT3 &p1, PT3 &p2)
{
	double d = disptoline(s, a, b);
	double t = sqrt(r * r - d * d) / dist(a, b);
	PT3 v = (s - a) * (b - a) * (b - a);
	PT3 p = sgn(d) == 0 ? s : s + v / vlen(v) * d;
	p1 = p + (a - b) * t;
	p2 = p - (a - b) * t;
}

PT3 sphere(double lam, double phi) { return PT3(cos(phi) * cos(lam), cos(phi) * sin(lam), sin(phi)); }
double dissphere(PT3 a, PT3 b, double r) { return asin( dist(a, b) / 2) * r ; }
