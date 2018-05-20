//
// Created by slyao on 5/13/2018.
//

#ifndef INC_05132_LEGACY_H
#define INC_05132_LEGACY_H

#include <bits/stdc++.h>

template <typename T, size_t size>
void qsort(T const (&array)[size], int l, int r)
{
        if (l >= r) return;
        auto i = l, j = r;
        auto mid = array[(r + l) / 2];
        while (i <= j)
        {
                while (array[i] < mid) i++;
                while (array[j] > mid) j--;
                if (i <= j) std::swap(array[i], array[j]), i++, j--;
        }
        qsort(array, l, j);
        qsort(array, i, r);
}

#endif //INC_05132_LEGACY_H
