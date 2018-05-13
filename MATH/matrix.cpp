#include <bits/stdc++.h>

template <typename T, T mod, size_t size>
struct MATRIX {
	T _array[size][size];

	const T* operator[](size_t idx) const { return _array[idx]; }
	T* operator[](size_t idx) { return _array[idx]; }

	MATRIX operator * (const MATRIX &o) const {
		MATRIX<T, mod, size>  ret{};
		memset(ret._array, 0, sizeof(ret._array));
		for (auto i = 0; i < size; i++)
			for (auto j = 0; j < size; j++)
				for (auto k = 0; k < size; k++)
					ret[i][j] = (ret[i][j] + _array[i][k] * o[k][j]) % mod;
		return ret;
	}

	T determinant() {
		T ans = 1;
		for (auto i = 0; i < size; i++) {
			for (auto j = i + 1; j < size; j++)
				while (_array[j][i]) {
					T t = _array[i][i] / _array[j][i];
					for (auto k = i; k < size; k++) _array[i][k] = (_array[i][k] - _array[j][k] * t) % mod;
					for (auto k = i; k < size; k++) std::swap(_array[i][k], _array[j][k]);
					ans = -ans;
				}
			if (_array[i][i] == 0) return 0;
			ans = ans * _array[i][i] % mod;
		}
		return (ans % mod + mod) % mod;
	}
};
