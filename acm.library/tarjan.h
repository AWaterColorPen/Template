//
// Created by slyao on 5/15/2018.
//

#ifndef INC_05132_TARJAN_H
#define INC_05132_TARJAN_H

#include <bits/stdc++.h>

template <size_t size>
struct Tarjan {
        int _dfn[size], _low[size], _block[size], _inStack[size];
        auto _index = 0, _blockSize = 0;
        std::stack<int> _stack;
        std::vector<int> (&_graph)[size];

        Tarjan(const std::vector<int> (&graph)[size]) : _graph(graph) {}

        void stronglyconnected(int u) {
                _low[u] = _dfn[u] = ++_index;
                _stack.push(u);
                _inStack[u] = 1;

                for (const auto &v : _graph[u])
                        if (_dfn[v] == 0)
                                stronglyconnected(v), _low[u] = std::min(_low[u], _low[v]);
                        else if (_inStack[v]) _low[u] = std::min(_low[u], _low[v]);

                if (_dfn[u] == _low[u] && ++_blockSize)
                        for (auto v = 0; v != u;)
                                v = _stack.top(), _stack.pop(), _block[v] = _blockSize, _inStack[v] = 0;
        }

        void tarjan(int n) {
                for (auto i = 0; i < n; i++) if (_dfn[i] == 0) stronglyconnected(i);
        }
};

#endif //INC_05132_TARJAN_H
