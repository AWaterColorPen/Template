#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;
struct NFA {
	vector <int> g[55][3];
	int n, x, y;
	NFA (char *str)
	{
		build_nfa(str, n = 0, x, y);
		for (int i = 0; i < n; i++) g[i][0].push_back(i);
	}
	int build_nfa(char *str, int i, int &s, int &t)
	{
		if (str[i] == '(')
		{
			int s1, t1, s2, t2;
			i = build_nfa(str, i + 1, s1, t1);
			if (str[i] == '|')
			{
				i = build_nfa(str, i + 1, s2, t2);
				s = n++, t = n++;
				g[s][0].push_back(s1), g[t1][0].push_back(t);
				g[s][0].push_back(s2), g[t2][0].push_back(t);
			}
			else if (str[i] == '*') {
				s = s1, t = t1;
				g[s][0].push_back(t), g[t][0].push_back(s);
				++i;
			}
			else {
				i = build_nfa(str, i, s2, t2);
				s = s1, t = t2;
				g[t1][0].push_back(s2);
			}
		}
		else
		{
			s = n++, t = n++;
			g[s][str[i] - 'a' + 1].push_back(t);
		}
		return i + 1;
	}
}	;
