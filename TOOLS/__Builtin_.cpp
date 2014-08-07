#include <iostream>
#include <cstdio>

using namespace std;
int main()
{
	int x = 0xF;
	cout << __builtin_ffs		((unsigned int) x) << endl; // If x is zero, returns zero. 返回右起第一个‘1’的位置。
	cout << __builtin_clz		((unsigned int) x) << endl; // If x is 0, the result is undefined. 返回左起第一个‘1’之前0的个数。
	cout << __builtin_ctz		((unsigned int) x) << endl; // If x is 0, the result is undefined. 返回右起第一个‘1’之后的0的个数。
	cout << __builtin_popcount	((unsigned int) x) << endl; // 返回‘1’的个数。
	cout << __builtin_parity	((unsigned int) x) << endl; // 返回‘1’的个数的奇偶性。

	cout << __builtin_ffsl		((unsigned long) x) << endl;
	cout << __builtin_clzl		((unsigned long) x) << endl;
	cout << __builtin_ctzl		((unsigned long) x) << endl;
	cout << __builtin_popcountl ((unsigned long) x) << endl;
	cout << __builtin_parityl	((unsigned long) x) << endl;

	cout << __builtin_ffsll		((unsigned long long) x) << endl;
	cout << __builtin_clzll		((unsigned long long) x) << endl;
	cout << __builtin_ctzll		((unsigned long long) x) << endl;
	cout << __builtin_popcountll((unsigned long long) x) << endl;
	cout << __builtin_parityll	((unsigned long long) x) << endl;
	return 0;
}
