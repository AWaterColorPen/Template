#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;
int tmp[40];
int SP[13]={1,9,11,19,21,29,31,32,33,34,35,36,37};
struct MAHJONG {
	static const int M = 40 ;
    int card[M], size;
    void clear() { memset(card, size=0, sizeof(card)); }
    void erase(int now) { card[now]--, size--; }
    int feasible() {
		for (int i=0; i<M; i++)
			if (card[i]>4) return 0; return 1;
    }
    int insert(int now) {
    	if (card[now]++, size++, feasible()) return 1;
    	return card[now]--, size--, 0;
    }
    int meld(int i) {
    	memcpy(tmp, card, sizeof(tmp)), tmp[i]-=2;
    	for (i=0; i<M; i++)
		{
			if (tmp[i]>=3) tmp[i]-=3;
			while (tmp[i])
				if (tmp[i+1]==0 || tmp[i+2]==0 || i>29) return 0;
				else tmp[i+1]--, tmp[i+2]--, tmp[i]--;
		}	return 1;
    }
    int sp_win1() {
    	int n0=0;
		for (int i=0; i<M; i++)
			n0+= (card[i]==2); return (n0==7);
    }
    int sp_win2() {
    	int n1=0, n2=0;
		for (int i=0; i<13; i++)
			n1+= (card[SP[i]]==1), n2+= (card[SP[i]]==2);
		return (n1==12 && n2==1);
    }
    int win() {
    	if (sp_win1() || sp_win2()) return 1;
    	for (int i=0; i<M; i++)
			if (card[i]>=2 && meld(i)) return 1; return 0;
    }
}   majg;
