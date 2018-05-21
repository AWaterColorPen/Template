//
// Created by slyao on 5/21/2018.
//

#ifndef ACM_LIBRARY_PLAYBLOCK_H
#define ACM_LIBRARY_PLAYBLOCK_H

#include <bits/stdc++.h>

template <size_t size>
struct BLOCK {
        struct PT {
                int x, y;
                PT () {}
                PT (int x, int y) : x(x) , y(y) {}
                bool operator < (const PT &o) const { return (x == o.x) ? (y < o.y) : (x < o.x) ; }
        };

        bool _visit[size][size];
        int _maze[size][size];
        int mx, my;

        std::vector<PT> _pt;
        std::function<bool (int, int)> _used;

        bool operator == (const BLOCK &o) const {
                for (int i = 0; i < _pt.size(); i++) if (_pt[i].x != o._pt[i].x || _pt[i].y != o._pt[i].y) return false;
                return true;
        }

        void bfs(int sx, int sy)
        {
                auto dx[4] = {0, 1, 0,-1};
                auto dy[4] = {1, 0,-1, 0};

                std::queue<PT> q;
                for (q.push(PT(sx, sy)), _visit[sx][sy] = 1; !q.empty(); ) {
                        auto pt = q.front();
                        q.pop();
                        _pt.push_back(pt);
                        for (auto d = 0; d < 4; ++d) {
                                auto i = pt.x + dx[d], j = pt.y + dy[d];
                                if (!_visit[i][j] && _used(i, j) && _maze[i][j] == _maze[sx][sy])
                                        _visit[i][j] = true, q.push(PT(i, j));
                        }
                }
        }

        void adjust()
        {
                auto x = 99, y = 99;
                for (const auto& v : _pt) x = std::min(x, v.x), y = std::min(y, v.y);
                for (auto& v : _pt) v.x -= x, v.y -= y;
                mx = my = 0;
                for (const auto& v : _pt) mx = std::max(mx, v.x), my = std::max(my, v.y);
                std::sort(_pt.begin(), _pt.end());
        }

        void full(int x, int y, char c) {
                for (const auto& v : _pt) _maze[x + v.x][y + v.y] = c;
        }

        BLOCK rotate() {
                BLOCK ret;
                for (const auto& v : _pt) ret._pt.push_back(PT(v.y, mx - v.x));
                return ret;
        }

        BLOCK reflex() {
                BLOCK ret;
                for (const auto& v : _pt) ret._pt.push_back(PT(mx - v.x, v.y));
                return ret;
        }
};

#endif //ACM_LIBRARY_PLAYBLOCK_H
