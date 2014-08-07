#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define eps 1e-8

using namespace std;

const long double PI = acos(-1);
int sgn(double x) { return (x<-eps)?-1:(x>eps); }

//2D PT
struct PT {
	double x, y;
	PT () {}
	PT (double x, double y) : x(x), y(y) {}
	void read() { scanf("%lf %lf", &x, &y) ; }
	PT operator - (const PT &o) { return PT(x - o.x, y - o.y) ; }
	PT operator + (const PT &o) { return PT(x + o.x, y + o.y) ; }
	PT operator * (double &s) { return PT(x * s, y * s) ; }
	PT operator / (double &s) { return PT(x / s, y / s) ; }
	bool operator < (const PT &o) const { return y < o.y-eps || y < o.y+eps && x < o.x;}
	bool operator == (const PT &o) const { return !sgn(y - o.y) && !sgn(x - o.x) ; }
	bool operator != (const PT &o) const { return sgn(y - o.y) || sgn(x - o.x) ; }
}	;

struct LE {
	PT a, b;
	LE () {}
	LE (PT a, PT b) : a(a), b(b) {}
}	;

double cpr(PT a, PT b, PT c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) ; }
double dpr(PT a, PT b, PT c) { return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y) ; }

double cpr(PT a, PT b) { return a.x * b.y - a.y * b.x ; }
double dpr(PT a, PT b) { return a.x * b.x + a.y * b.y ; }

double vlen(PT a) { return sqrt(a.x * a.x + a.y * a.y) ; }
double dist(PT a, PT b) { return sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) ) ; }

//��������ֱ�����λ��, ����ֱ����0, ͬ��1, ���-1
int pl_side(PT a, PT b, PT c, PT d) { return sgn( cpr(c, a, d) * cpr(c, b, d) ); }  

//�����߶��ϸ��ཻ
bool intersect_ex(PT a, PT b, PT c, PT d) { return pl_side(a, b, c, d)==-1 && pl_side(c, d, a, b)==-1; }

//�����߶η��ϸ��ཻ
bool intersect_in(PT a, PT b, PT c, PT d)
{ 
	int d1 = pl_side(a, b, c, d), d2 = pl_side(c, d, a, b);
	if (d1 == 1 || d2 == 1) return 0;
	if (d1 == -1 || d2 == -1) return 1;
	return dpr(c, a, b) < eps || dpr(d, a, b) < eps || dpr(a, c, d) < eps || dpr(b, c, d) < eps;
}	

//��ֱ��ab��ֱ��cd�Ľ���
PT intersect(PT a, PT b, PT c, PT d)
{
	double v1 = cpr(a, b, c), v2 = cpr(a, b, d);
	return (c * v2 - d * v1) / (v2 - v1);
}

//��p��ֱ��ab�ϵ������
PT ptoline(PT p, PT a, PT b)
{
	PT t(p.x + a.y - b.y, p.y + b.x - a.x) ;
	return intersect(p, t, a, b);
}

//����������Ǻ�,��ʱ��Ϊ��
double angsum(PT p[], int n)
{
	double ret = 0, tmp;
	for (int i = 0; i < n; i++)
	{
		PT &A = p[i], &B = p[(i+1)%n], &C = p[(i+2)%n];
		tmp = PI - acos(dpr(B, A, C) / dis(A, B) / dis(B, C));
		if (cpr(A, B, C) < 0)
			tmp = -tmp;
		ret += tmp;
	}
	return ret;
}

//�ж�͹�����,���㰴˳ʱ�����ʱ�����,�������ڱ߹���(n>=3)
int is_convex(PT p[], int n)
{
	int s[3] = {1, 1, 1};
	for (int i=0; i<n && (s[0] | s[2]); i++)
		s[sgn(cpr(p[i], p[(i+1)%n], p[(i+2)%n])) + 1] = 0;
	return s[0] | s[2];
}

//�ж�͹�����,���㰴˳ʱ�����ʱ�����,���������ڱ߹���
int is_convex_v2(PT p[], int n)
{
	int s[3] = {1, 1, 1};
	for (int i = 0; i<n && s[1] && (s[0] | s[2]); i++)
		s[sgn(cpr(p[i], p[(i+1)%n], p[(i+2)%n])) + 1] = 0;
	return s[1] && (s[0] | s[2]);
}

//�е���͹������ڻ����α���,���㰴˳ʱ�����ʱ�����
int inside_convex(PT q, PT p[], int n)
{
	int s[3] = {1, 1, 1};
	for (int i = 0; i<n && (s[0] | s[2]); i++)
		s[sgn(cpr(p[i], p[(i+1)%n], q)) + 1] = 0;
	return s[0] | s[2];
}

//�е���͹�������,���㰴˳ʱ�����ʱ�����,�ڶ���α��Ϸ���0
int inside_convex_v2(PT q, PT p[], int n)
{
	int s[3] = {1, 1, 1};
	for (int i = 0; i<n && s[1] && (s[0] | s[2]); i++)
		s[sgn(cpr(p[i], p[(i+1)%n], q)) + 1] = 0;
	return s[1] && (s[0] | s[2]);
}

//������p[]��͹�����ϸ�
void make_ch_jm_ex(PT p[], PT o[], int n, int &top)
{
	top = 0;
	sort(p, p + n);
	for (int i=0, j, k=1; i < 2*n-1; i++)
	{
		j = (i < n) ? i : 2*(n-1)-i;
		if (i==n) k = top;
		while (top > k && cpr(o[top-2], o[top-1], p[j]) < eps) top--;
		o[top++] = p[j];
	}
	top -- ;
}

//������p[]��͹�����ϸ�
void make_ch_gs_ex(PT p[], PT o[], int n, int &top)
{
	top = 0;
	curp = p[0];
	sort(p + 1, p + n, cmp_angle);
	for (int i=0; i<n; i++)
	{
		while (top > 1 && cpr(o[top-2], o[top-1], p[i]) < eps) top--;
		o[top++] = p[i];
	}
}

//�����������p[]Ϊ���㣬��ʱ��Ϊ��
double poly_area(PT p[], int n)
{
	double ans = 0;
	for (int i=1; i<n-1; i++) ans += cpr(p[0], p[i], p[i+1]);
	return ans / 2;
}

//��ƽ�潻(�и�ֱ��Ϊab��p[]Ϊԭʼ����Σ�������Ϊn
//tmp[]��ʱ������ŵ㼯�����������Է���pol[])
//����ε���Ϊ��ʱ�룬�и������Ϊ��Ч��
void half_plane_its(PT a, PT b, PT p[], int &n, PT tmp[])
{
	int tot = 0;
	for (int i=0; i<n; i++)
	{
		int now = cpr(a, b, p[i]) > -eps;
		int next = cpr(a, b, p[(i+1)%n]) > -eps;
		if (now) tmp[tot++] = p[i];
		if (now ^ next) tmp[tot++] = intersect(a, b, p[i], p[(i+1)%n]);
	}
	n = tot;
	for (int i=0; i<n; i++) p[i] = tmp[i];
}

//���������
PT barycenter(int n, PT *p)
{
	PT ret(0, 0), t;
	double t1 = 0, t2;
	for (int i = 1; i < n - 1; i++)
	{
		if (fabs(t2 = cpr(p[i+1], p[0], p[i])) > eps)
		{
			t.x = (p[0].x + p[i].x + p[i+1].x) /3.0;
			t.y = (p[0].y + p[i].y + p[i+1].y) /3.0;
			ret.x += t.x*t2;
			ret.y += t.y*t2;
			t1 += t2;
		}
	}
	if (fabs(t1) > eps)
		ret.x /= t1, ret.y /= t1;
	return ret;
}

//��p��ֱ��ab����
double disptoline(const PT &p, const PT &a, const PT &b)
{
	return fabs(cpr(p, a, b)) / dis(a, b);
}

//��p���߶�ab�ϵ������
PT ptoseg(PT p, PT a, PT b)
{
	PT t = p;
	t.x += a.y - b.y;
	t.y += b.x - a.x;
	if (cpr(p,a,t) * cpr(p,b,t) > eps)
		return dis(p,a) < dis(p,b) ? a : b;
	return its(p, t, a, b);
}

//�㵽�߶ξ���
double disptoseg(PT p, PT a, PT b)
{
	PT t = p;
	t.x += a.y - b.y;
	t.y += b.x - a.x;
	if (cpr(p,a,t) * cpr(p,b,t) > eps)
		return min(dis(p,a), dis(p,b));
	return fabs(cpr(b,p,a)) / dis(a,b);
}

//��v���ŵ�p��ʱ����תangle���Ŵ�scale��
PT rotate(PT v, PT p, double angle, double scale)
{
	PT ret = p;
	v.x -= p.x;
	v.y -= p.y;
	p.x = scale * cos(angle);
	p.y = scale * sin(angle);
	ret.x += v.x * p.x - v.y * p.y;
	ret.y += v.x * p.y + v.y * p.x;
	return ret;
}

//����������
PT circumcenter(PT a, PT b, PT c)
{
	PT u1, u2, v1, v2;
	u1.x = (a.x+b.x)/2;
	u1.y = (a.y+b.y)/2;
	u2.x = u1.x-a.y+b.y;
	u2.y = u1.y+a.x-b.x;
	v1.x = (a.x+c.x)/2;
	v1.y = (a.y+c.y)/2;
	v2.x = v1.x-a.y+c.y;
	v2.y = v1.y+a.x-c.x;
	return its(u1, u2, v1, v2);
}

//����������
PT incenter(PT a, PT b, PT c)
{
	PT u1, u2, v1, v2;
	double m, n;
	u1 = a;
	m = atan2(b.y-a.y, b.x-a.x);
	n = atan2(c.y-a.y, c.x-a.x);
	u2.x = u1.x + cos((m+n)/2);
	u2.y = u1.y + sin((m+n)/2);
	v1 = b;
	m = atan2(a.y-b.y, a.x-b.x);
	n = atan2(c.y-b.y, c.x-b.x);
	v2.x = v1.x + cos((m+n)/2);
	v2.y = v1.y + sin((m+n)/2);
	return its(u1, u2, v1, v2);
}

//����
PT perpencenter(PT a, PT b, PT c)
{
	PT u1, u2, v1, v2;
	u1 = c;
	u2.x = u1.x-a.y+b.y;
	u2.y = u1.y+a.x-b.x;
	v1 = b;
	v2.x = v1.x-a.y+c.y;
	v2.y = v1.y+a.x-c.x;
	return its(u1, u2, v1, v2);
}

//����
//������������������ƽ������С�ĵ�
//�������ڵ����߾���֮�����ĵ�
PT barycenter(PT a, PT b, PT c)
{
	PT ret;
	ret.x = (a.x + b.x + c.x) / 3;
	ret.y = (a.y + b.y + c.y) / 3;
	return ret;
}

//�����
//�����������������֮����С�ĵ�
PT fermentpoint(PT a, PT b, PT c)
{
	PT u, v;
	double step = fabs(a.x)+fabs(a.y)+fabs(b.x)+fabs(b.y)+fabs(c.x)+fabs(c.y);
	int i, j, k;
	u.x = (a.x+b.x+c.x)/3;
	u.y = (a.y+b.y+c.y)/3;
	while (step > 1e-10)
	{
		for (k = 0; k < 10; step/=2, k++)
		for (i = -1; i <= 1; i++)
		for (j = -1; j <= 1; j++)
		{
			v.x = u.x + step*i;
			v.y = u.y + step*j;
			if (dis(u,a) + dis(u,b) + dis(u,c) > dis(v,a) + dis(v,b) + dis(v,c))
				u = v;
		}
	}
	return u;
}

//����ֱ����Բ�Ľ���,��ֱ֤����Բ�н���
//�����߶���Բ�Ľ����������������е��Ƿ����߶���
void intersection_line_circle(PT c, double r, PT l1, PT l2, PT &p1, PT &p2)
{
	PT p = c;
	p.x += l1.y - l2.y;
	p.y += l2.x - l1.x;
	p = its(p, c, l1, l2);
	double d = dis(p,c), t = sqrt(r*r - d*d) / dis(l1,l2);
	p2.x = p.x + (l2.x-l1.x)*t;
	p2.y = p.y + (l2.y-l1.y)*t;
	p1.x = p.x - (l2.x-l1.x)*t;
	p1.y = p.y - (l2.y-l1.y)*t;
}


//����Բ��Բ�Ľ���,��֤Բ��Բ�н���,Բ�Ĳ��غ�
void intersection_circle_circle(PT c1, double r1, PT c2, double r2, PT &o, PT &p2)
{
	double d2 = (c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y);
	double cos = (r1 * r1 + d2 - r2 * r2) / (2 * r1 * sqrt(d2));
	PT v1 = (c2 - c1) / dis(c1, c2), v2 = PT(-v1.y, v1.x) * (r1 * sqrt(1 - cos * cos));
	PT X = c1 + v1 * (r1 * cos);
	o = X + v2;
	p2 = X - v2;
}


//��Բ�������е��Ӧ�ĽǶ�

//��������
void find_tp(double a, double b, double c, double &ang1, double &ang2)
{
	double v1, v2;
	v1 = fabs(c) > eps ? atan2(b*c, a*c) : atan2(b, a);
	v2 = acos(fabs(c)/sqrt(a*a+b*b));
	ang1 = v1 - v2;
	ang2 = v1 + v2;
}

//�⹫����(����Ƕ�t1 t2������Բ������)
void tangent1(PT c1, double r1, PT c2, double r2, double &t1, double &t2)
{
	find_tp(c2.x-c1.x, c2.y-c1.y, r1-r2, t1, t2);
}

//�ڹ�����(����Ƕ�t1 t2����Բc1����,��Բc2�����(��)PI)
void tangent2(PT c1, double r1, PT c2, double r2, double &t1, double &t2)
{
	find_tp(c2.x-c1.x, c2.y-c1.y, r1+r2, t1, t2);
}

int main()
{}
