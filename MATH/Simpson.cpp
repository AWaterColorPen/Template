#include <cstdio>
#include <cmath>

// Simpson��ʽ�õ��ĺ���
double F(double x) { return x * x; }
// ����Simpson��
double simpson(double a, double b) 
{
	double c = a + (b - a) / 2;
	return (F(a) + F(c) * 4 + F(b)) * (b - a) / 6;
}
// ����ӦSimpson��ʽ���ݹ���̣�
double asr(double a, double b, double eps, double A) 
{
	double c = a + (b - a) / 2;
	double L = simpson(a, c), R = simpson(c, b);
	if (fabs(L + R - A) < eps) return L + R;
	return asr(a, c, eps / 2, L) + asr(c, b, eps / 2, R);
}
// ����ӦSimpson��ʽ�������̣�
double asr(double a, double b, double eps)
{
	return asr(a, b, eps, simpson(a, b));
}
