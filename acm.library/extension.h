//
// Created by slyao on 5/15/2018.
//

#ifndef INC_05132_EXTENSION_H
#define INC_05132_EXTENSION_H

#include <bits/stdc++.h>

template <typename T, T mod, size_t size>
void show(const MATRIX<T, mod, size>& o) {
        for (auto i = 0; i < size; i++) {
                for (auto j = 0; j < size; j++) std::cout << o[i][j] << " ";
                std::cout << std::endl;
        }
}

#endif //INC_05132_EXTENSION_H
