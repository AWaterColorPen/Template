#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
int MinRep(int *str, int len)
{
    int i=0, j=1, k=0, t;
    while (i<len && j<len && k<len) 
	{
        t = str[(i+k) >= len ? i+k-len : i+k] - str[(j+k) >= len ? j+k-len : j+k];
        if (t==0) k++;
        else {
            if (t>0) i=i+k+1;
            else j=j+k+1;
            if (i==j) ++j;
            k=0;
        }
    }
    return (i<j ? i:j);
}

