#include<iostream>
#include<complex>
#include <cstdio>

using namespace std;
int main()
{
	complex <double> a(1, 1), b(1, 1);
	cout << a << endl;						// �ѿ�������
	cout << a + b << endl;					// ��������
	cout << a - b << endl;
	cout << a * b << endl;
	cout << a / b << endl;
	cout << boolalpha << (a == b) << endl;	// ���
	cout << boolalpha << (a != b) << endl;	// �����
	cout << a. real() << endl;				// ʵ��
	cout << a. imag() << endl;				// �鲿
	cout << abs(a) << endl;					// ģ
	cout << arg(a) << endl;					// ����
	cout << conj(a) << endl;				// ����
	cout << norm(a) << endl;				// ����(ģ��)
	cout << polar(a, b) << endl;			// a*e^(i*b)
	cout << exp(a) << endl;					// ָ����ʽ(e^a)
	cout << log(a) << endl;					// ����
	cout << pow(a, 2) << endl;				// ��
	cout << sqrt(a) << endl;				// ����
	cout << sin(a) << endl;					// ���Ǻ���
	cout << cos(a) << endl;
	cout << tan(a) << endl;
	cout << sinh(a) << endl;				// �����Ǻ���
	cout << cosh(a) << endl;
	cout << tanh(a) << endl;
	return 0;
}
