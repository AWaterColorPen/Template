//
// Created by slyao on 5/20/2018.
//

#ifndef ACM_LIBRARY_GRAPHHASH_H
#define ACM_LIBRARY_GRAPHHASH_H

#include <bits/stdc++.h>

template <typename TEdge, size_t size>
struct GRAPH_HASH {
        int _f[size], _tf[size], _hash[size];
        int _seed[6] = {107, 109, 101, 113, 10000007, 11};
        std::vector<TEdge> _edge;

        GRAPH_HASH(const std::vector<TEdge> edge) : _edge(edge) {}

        void graph_hash(int n)
        {
                for (auto i = 0; i < n; ++i)
                {
                        for (auto j = 0; j < n; ++j) _f[j] = 1;
                        for (auto j = 0; j < _seed[5]; ++j)
                        {
                                memcpy(_tf, _f, sizeof(_tf));
                                for (auto k = 0; k < n; ++k) _f[k] *= _seed[0];
                                for (const auto& e : _edge)
                                {
                                        _f[e.source] += _tf[e.target] * _seed[1];
                                        _f[e.target] += _tf[e.source] * _seed[2];
                                }
                                _f[i] += _seed[3];
                                for (int k = 1; k <= n; k++) _f[k] %= _seed[4];
                        }
                        _hash[i] = _f[i];
                }
                std::sort(_hash, _hash + n);
        }
};

#endif //ACM_LIBRARY_GRAPHHASH_H
