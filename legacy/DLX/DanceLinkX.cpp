#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

const int inf = 0x0f0f0f0f;

struct DLX {
	static const int MC = 350, MR = 1005, M = 3505;
	int D[M], U[M], L[M], R[M], COL[M], ROW[M], S[MC];
	int BEG[MR], END[MR], ANS[MR], N;
	int vis[MC], ans, LIT;
	
	void init(int n)
	{
		memset(BEG, 0xff, sizeof(BEG));
		for (int i = 1; i <= n; i++) L[i + 1] = R[i - 1] = D[i] = U[i] = i, S[i] = 0;
		L[1] = R[n] = 0, L[0] = n, N = n + 1;
	}
	void link(int r, int c)
	{
		D[N] = D[c], U[N] = c, U[D[c]] = N, D[c] = N, COL[N] = c, ROW[N] = r, S[c]++;
		if (BEG[r] == -1) BEG[r] = END[r] = N;
		R[END[r]] = N, L[N] = END[r], R[N] = BEG[r], L[BEG[r]] = N, END[r] = N++;
	}
	void remove_exact(int c)
	{
		L[R[c]] = L[c], R[L[c]] = R[c];
		for (int i = D[c]; i != c; i = D[i])
			for (int j = R[i]; j != i; j = R[j])
				D[U[j]] = D[j], U[D[j]] = U[j], S[COL[j]]--;
	}
	void resume_exact(int c)
	{
		L[R[c]] = c, R[L[c]] = c;
		for (int i = U[c]; i != c; i = U[i])
			for (int j = L[i]; j != i; j = L[j])
				D[U[j]] = j, U[D[j]] = j, S[COL[j]]++;
	}
	
	void remove_repeat(int c)
	{
		for (int i = D[c]; i != c; i = D[i])
			L[R[i]] = L[i], R[L[i]] = R[i], S[COL[i]]--;
	}
	void resume_repeat(int c)
	{
		for (int i = U[c]; i != c; i = U[i])
			L[R[i]] = i, R[L[i]] = i, S[COL[i]]++;
	}
	
	{
	int dfs(int n)
	{
		int i, now = inf, c;
		if (R[0] == 0) return solve(n), 1;
		for (i = R[0]; i; i = R[i]) if (S[i] < now) now = S[c = i];
		for (remove_exact(c), i = D[c]; i != c; i = D[i])
		{
			ANS[n] = i;
			for (int j = R[i]; j != i; j = R[j]) remove_exact(COL[j]);
			if (dfs(n + 1)) return 1;
			for (int j = L[i]; j != i; j = L[j]) resume_exact(COL[j]);
		}
		return resume_exact(c), 0;
	}
	void solve(int n)
	{
		for (int i = 0; i < n; i++)
		{
			int j = ROW[ANS[i]];
		}
	}
	}
	
	{
	int heuristics() 
	{
		memset(vis, 0, sizeof(vis));
		int c, i, j, cnt = 0;
		for (c = R[0]; c; c = R[c])
			if (vis[c] == 0)
				for (cnt++, vis[c] = 1, i = D[c]; i != c; i = D[i])
					for (j = R[i]; j != i; j = R[j])
						vis[COL[j]] = 1;
		return cnt;
	}
	int dfs(int n)
	{
		if (heuristics() + n >= ans) return 0;
		if (R[0] == 0) return ans = n, 1;
		int now = inf, c;
		for (int i = R[0]; i; i = R[i]) if (now > S[i]) now = S[c = i];
		for (int i = D[c]; i !=c ; i = D[i])
		{
			remove_repeat(i);
			for (int j = R[i]; j != i; j = R[j]) remove_repeat(j);
			dfs(n + 1);
			for (int j = L[i]; j != i; j = L[j]) resume_repeat(j);
			resume_repeat(i);
		}
		return 0;
	}
	}
	
	{
	int heuristics() 
	{
		memset(vis, 0, sizeof(vis));
		int c, i, j, cnt=0;
		for (c = R[0]; c <= LIT && c; c = R[c])
			if (vis[c] == 0)
				for (cnt++, vis[c] = 1, i = D[c]; i != c; i = D[i])
					for (j = R[i]; j != i; j = R[j])
						vis[COL[j]] = 1;
		return cnt;
	}
	int dfs(int n)
	{
		int i, j, now = inf, c;
		if (heuristics() + n >= ans) return 0;
		if (R[0] == 0 || R[0] > LIT) return ans = n, 1;
		for (i = R[0]; i <= LIT && i; i = R[i]) if (S[i] < now) now = S[c = i];
		for (i = D[c]; i != c; i = D[i])
		{
			remove_repeat(i);
			ANS[n] = i;
			for (j = R[i]; j != i; j = R[j]) if (COL[j] <= LIT) remove_repeat(j);
			for (j = R[i]; j != i; j = R[j]) if (COL[j] > LIT) remove_exact(COL[j]);
			if (dfs(n + 1)) return 1;
			for (j = L[i]; j != i; j = L[j]) if (COL[j] > LIT) resume_exact(COL[j]);
			for (j = L[i]; j != i; j = L[j]) if (COL[j] <= LIT) resume_repeat(j);
			resume_repeat(i);
		}
		return 0;
	}
	}
	
}	dlx;