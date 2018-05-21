//
// Created by slyao on 5/13/2018.
//

#ifndef ACM_LIBRARY_HELPER_H
#define ACM_LIBRARY_HELPER_H

#include <bits/stdc++.h>

template <typename T>
void addedge(T const& graph, int x, int y) { graph[x].push_back(y); }

template <typename T>
T gcd(T a, T b) { for (T t; b; t = a % b, a = b, b = t) ; return a; }

template <typename T>
T mul_mod(T a, T b, T const& mod) {
        T ans = 0;
        for ( ; b; b >>= 1, a = (a << 1) % mod) if (b & 1) ans = (ans + a) % mod;
        return ans;
}

template <typename T>
T mod_exp(T a, T b, T const& mod) {
        T ans = 1LL;
        for ( ; b; b >>= 1, a = mul_mod(a, a, mod)) if (b & 1) ans = mul_mod(ans, a, mod);
        return ans;
}

#endif //ACM_LIBRARY_HELPER_H
