//
// Created by slyao on 5/13/2018.
//

#ifndef INC_05132_TRIES_H
#define INC_05132_TRIES_H

#include <bits/stdc++.h>

template <typename T, size_t size>
struct TRIE {
        T _value[size];
        int _ch[size][26];
        int _ID[128];
        int _count;

        TRIE() { for (int i = 0; i < 26; i++) _ID[i + 'a'] = i; }

        void clear() {
                memset(_ch[0], 0, sizeof(_ch[0]));
                memset(_value, _count = 0, sizeof(_value));
        }

        void insert(char *s, T value) {
                int id = 0, i, j;
                for (i = 0; s[i]; i++) {
                        if (j = _ID[s[i]], _ch[id][j] == 0)
                                _ch[id][j] = ++_count, memset(_ch[_count], 0, sizeof(_ch[_count]));
                        id = _ch[id][j];
                }
                _value[id] += value;
        }

        T find(char *s) {
                int id = 0, i, j;
                for (i = 0; s[i]; i++) {
                        j = _ID[s[i]];
                        if (id = _ch[id][j], id == 0) return 0;
                }
                return _value[id];
        }
};

#endif //INC_05132_TRIES_H
