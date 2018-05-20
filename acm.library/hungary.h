//
// Created by slyao on 5/20/2018.
//

#ifndef ACM_LIBRARY_HUNGARY_H
#define ACM_LIBRARY_HUNGARY_H

#include <bits/stdc++.h>

template <size_t size>
struct Hungary {
        int _match[size];
        bool _visit[size];
        std::vector<int> (&_graph)[size];

        Hungary(const std::vector<int> (&graph)[size]) : _graph(graph) {}

        int dfs(int u) {
                _visit[u] = true;
                for (const auto &v : _graph[u])
                        if (_match[v] == 0 || (!_visit[_match[v]] && dfs(_match[v])))
                                return _match[v] = u, 1;
                return 0;
        }

        int hungary(int n) {
                auto count = 0;
                for (auto i = 0; i < n; i++) {
                        std::memset(_visit, 0, sizeof(_visit));
                        count += dfs(i);
                }
                return count;
        }
};

#endif //ACM_LIBRARY_HUNGARY_H
