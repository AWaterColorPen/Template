#include <bits/stdc++.h>

template <typename T, size_t size>
struct BIT {
        T _array[size];

        void modify(int index, T delta) {
                for (auto i = index; i < size; i += i & (-i)) _array[i] += delta;
        }

        T ask(int index) {
                T sum = 0;
                for (auto i = index; i; i -= i & (-i)) sum += _array[i];
                return sum;
        }
};

template <typename T, size_t rows, size_t cols>
struct BIT2 {
        T _array[rows][cols];

        void modify(int x, int y, T delta) {
                for (auto i = x; i < rows; i += i & (-i))
                        for (auto j = y; j < cols; j += j& (-j))
                                _array[i][j] += delta;
        }

        T ask(int x, int y) {
                T sum = 0;
                for (auto i = x; i; i -=i & (-i))
                        for (auto j = y; j; j -= j& (-j))
                                sum += _array[i][j];
                return sum;
        }

        T ask(int x1, int y1, int x2, int y2) {
                return ask(x2, y2) - ask(x1 - 1, y2) - ask(x2, y1 - 1) + ask(x1 - 1, y1 - 1);
        }
};

template <typename T, size_t size>
struct BIT_RangeQuery {
        BIT<T, size>  _interval;
        BIT<T, size>  _boundary;

        void modify(int l, int r, T delta) {
                _boundary.modify(l, delta);
                _boundary.modify(r + 1, - delta);
                _interval.modify(l, delta * l);
                _interval.modify(r + 1, - delta * (r + 1));
        }

        T ask(int index) {
                return _boundary.ask(index) * (index + 1) - _interval.ask(index);
        }
};

