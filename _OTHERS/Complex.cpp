#include<iostream>
#include<complex>
#include <cstdio>

using namespace std;
int main()
{
	complex <double> a(1, 1), b(1, 1);
	cout << a << endl;						// 笛卡尔坐标
	cout << a + b << endl;					// 四则运算
	cout << a - b << endl;
	cout << a * b << endl;
	cout << a / b << endl;
	cout << boolalpha << (a == b) << endl;	// 相等
	cout << boolalpha << (a != b) << endl;	// 不相等
	cout << a. real() << endl;				// 实部
	cout << a. imag() << endl;				// 虚部
	cout << abs(a) << endl;					// 模
	cout << arg(a) << endl;					// 辐角
	cout << conj(a) << endl;				// 共轭
	cout << norm(a) << endl;				// 范数(模方)
	cout << polar(a, b) << endl;			// a*e^(i*b)
	cout << exp(a) << endl;					// 指数形式(e^a)
	cout << log(a) << endl;					// 对数
	cout << pow(a, 2) << endl;				// 幂
	cout << sqrt(a) << endl;				// 开方
	cout << sin(a) << endl;					// 三角函数
	cout << cos(a) << endl;
	cout << tan(a) << endl;
	cout << sinh(a) << endl;				// 反三角函数
	cout << cosh(a) << endl;
	cout << tanh(a) << endl;
	return 0;
}
