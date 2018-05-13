#include <bits/stdc++.h>

using namespace std;

template <typename T, size_t size>
struct BIT {
	T _array[size];

	void modify(int i, T value) {
		for (; i < size; i += i & (-i)) _array[i] += value;
	}

	T ask(int i) {
		T sum = 0;
		for (; i; i -= i & (-i)) sum += _array[i];
		return sum;
	}
};

template <typename T, size_t rows, size_t cols>
struct BIT2 {
	T _array[rows][cols];

	void modify(int i, int j, T value)
	{
		for ( ; i < rows; i += i & (-i))
			for (int k = j; k < cols; k += k& (-k))
				_array[i][k] += value;
	}

	T ask(int i, int j)
	{
		T sum = 0;
		for ( ; i ; i -=i & (-i))
			for (int k = j; k ; k -= k& (-k))
				sum += _array[i][k];
		return sum;
	}

	T ask(int i, int j, int x, int y)
	{
		return ask(x, y) - ask(i - 1, y) - ask(x, j - 1) + ask(i - 1, j - 1);
	}
};

