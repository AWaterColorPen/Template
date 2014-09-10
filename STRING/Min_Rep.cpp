#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

int MinRep(int *str, int len)
{
    int i = 0, j = 1, k = 0;
    while (i < len && j < len && k < len) 
	{
		int l1 = i + k;
		int l2 = j + k;
		if (l1 >= len) l1 -= len;
		if (l2 >= len) l2 -= len;
        
		int t = str[l1] - str[l2];
        if (t == 0) k++;
        else {
            if (t > 0) i = i + k + 1;
            else j = j + k + 1;
            if (i == j) j++;
            k = 0;
        }
    }
    return i < j ? i : j;
}

