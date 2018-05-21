//
// Created by slyao on 5/21/2018.
//

#ifndef ACM_LIBRARY_STOERWAGNER_H
#define ACM_LIBRARY_STOERWAGNER_H

#include <bits/stdc++.h>

template <size_t size>
struct STOERWAGNER {
        int _id[size];
        int (&_cap)[size][size], _wage[size];

        STOERWAGNER(int (&_cap)[size][size]) : _cap(_cap) {}

        int mincut(int n) {
                auto ans = INT32_MAX;
                for (auto i = 0; i < n; ++i) _id[i] = i;
                for ( ; n > 1; n--)
                {
                        std::memset(_wage, 0, sizeof(_wage));
                        for (auto i = 0; i < n; ++i) {
                                auto now = i;
                                for (auto j = i + 1; j < n; ++j) {
                                        _wage[_id[j]] += _cap[_id[i]][_id[j]];
                                        if ( _wage[_id[now]] < _wage[_id[j]]) now = j;
                                }
                                std::swap(_id[i], _id[now]);
                        }

                        ans = std::min(ans, _wage[_id[n - 1]]);
                        for (auto i = 0; i < n - 1; ++i) {
                                auto flow = _cap[_id[i]][_id[n - 1]];
                                _cap[_id[i]][_id[n - 2]] += flow;
                                _cap[_id[n - 2]][_id[i]] += flow;
                        }
                }
                return ans;
        }
};


#endif //ACM_LIBRARY_STOERWAGNER_H
