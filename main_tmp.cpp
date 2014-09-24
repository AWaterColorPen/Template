void tarjan(int n)
{
	int i, j;
	low[n] = dfn[n] = ++Cnt, ins[stk[++Now] = n] = 1;
	for (i = 0; i < vv[n].size(); i++)
		if (dfn[j = vv[n][i]] == 0)
			tarjan(j), low[n] = min(low[n], low[j]);
		else if (ins[j]) low[n] = min(low[n], low[j]);
	if (dfn[n] == low[n] && ++block)
		do blo[i = stk[Now--]] = block, ins[i] = 0;
		while (i != n);
}