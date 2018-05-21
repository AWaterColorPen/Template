//
// Created by slyao on 5/21/2018.
//

#ifndef ACM_LIBRARY_POLLARDRHO_H
#define ACM_LIBRARY_POLLARDRHO_H

#include <bits/stdc++.h>
#include "helper.h"

template <typename T>
struct Pollard_Rho {
        std::map<T, int> _factor;

        bool witness(T n)
        {
                T m = n - 1, a = rand() % m + 1;
                while (m % 2 == 0) m >>= 1;
                if (a = mod_exp(a, m, n), a == 1) return true;
                while (m != n - 1 && a != n - 1)
                        a = mul_mod(a, a, n), m <<= 1;
                return a == n - 1;
        }

        bool miller_rabin(T n)
        {
                if (n % 2 == 0) return n == 2;
                for (auto i = 0; i < 10; i++)
                        if (witness(n) == false) return false;
                return true;
        }

        T pollard_rho(T n, T c)
        {
                T x = rand() % n, y = x, i = 1, k = 2, d;
                do {
                        if (i++, d = gcd(n + y - x, n), d > 1 && d < n) return d;
                        if (i == k) y = x, k <<= 1;
                        x = (mul_mod(x, x, n) - c + n) % n;
                }	while (y != x);
                return n;
        }

        void rho(T n)
        {
                if (n <= 1) return ;
                if (miller_rabin(n)) { _factor[n] = 1; return ; }
                T t;
                do t = pollard_rho(n, rand() % (n - 1) + 1);
                while (t == 1 || t == n);
                rho(t), rho(n / t);
        }

        void primefactor(T n)
        {
                rho(n);
                for (auto& it : _factor) {
                        for (it.first = 0; n % it.first == 0; n /= it.first)
                                it.second++;
                }
        }
};


#endif //ACM_LIBRARY_POLLARDRHO_H
