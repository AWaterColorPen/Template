#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

char out[6][20]={{"Correct"}, {"Incorrect\n"}, {"Mate\n"}, {"Check"}, {"Draw\n"}, {""}};
int Xkn[]={-2,-2,-1,-1, 1, 1, 2, 2};
int Ykn[]={-1, 1,-2, 2,-2, 2,-1, 1};
int Xb[]={-1,-1, 1, 1};
int Yb[]={-1, 1,-1, 1};
int Xr[]={ 0, 0,-1, 1};
int Yr[]={-1, 1, 0, 0};
int Xki[]={ 0, 0,-1, 1,-1,-1, 1, 1};
int Yki[]={-1, 1, 0, 0,-1, 1,-1, 1};

struct CHESS {
	int B[10][10], T[10][10];
	void clear() { memset(B, 0, sizeof(B)); memset(T, 0, sizeof(T)); }
	int used(int x, int y) { return (x > 0 && x < 9 && y > 0 && y < 9) ; }
	int abs(int x) { return x < 0 ? -x : x; }

	void show(int n)
	{
		printf("%s\n", out[n]);
		if (n == 0 || n == 3)  return ;
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
				printf("%d%c", B[j][9-i], j == 8 ? '\n' : ' ');
	}

	int movep(int x0, int y0, int x1, int y1, int player)
	{
		if (B[x1][y1] == 0 && x1 == x0 && (y1 == y0 + player || (y1 == y0 + 2 * player && B[x0][y0 + player] == 0))) return 1;
		if (B[x1][y1] && (x1 == x0 + 1 || x1 == x0 - 1) && y1 == y0 + player) return 1;
		return 0;
	}

	int movekn(int x0, int y0, int x1, int y1) { for (int i = 0; i < 8; i++) if (x1 == x0 + Xkn[i] && y1 == y0 + Ykn[i]) return 1; return 0; }

	int moveb(int x0, int y0, int x1, int y1)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 1; 1; j++)
			{
				if (x1 == x0 + Xb[i] * j && y1 == y0 + Yb[i] * j) return 1;
				if (used(x0 + Xb[i] * j, y0 + Yb[i] * j) == 0 || B[x0 + Xb[i] * j][y0 + Yb[i] * j]) break;
			}
		return 0;
	}

	int mover(int x0, int y0, int x1, int y1)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 1; 1; j++)
			{
				if (x1 == x0 + Xr[i] * j && y1 == y0 + Yr[i] * j) return 1;
				if (used(x0 + Xr[i] * j, y0 + Yr[i] * j) == 0 || B[x0 + Xr[i] * j][y0 + Yr[i] * j]) break;
			}
		return 0;
	}

	int moveq(int x0, int y0, int x1, int y1) { return moveb(x0, y0, x1, y1) || mover(x0, y0, x1, y1) ; }

	int moveki(int x0, int y0, int x1, int y1) { for (int i = 0; i < 8; i++) if (x1 == x0 + Xki[i] && y1 == y0 + Yki[i]) return 1; return 0; }

	void move0(int x0, int y0, int x1, int y1) { B[x1][y1] = B[x0][y0]; B[x0][y0] = 0; T[x1][y1] = T[x0][y0] + 1; T[x0][y0] = 0; }

	int move_all(int x0, int y0, int x1, int y1)
	{
		if (B[x0][y0] * B[x1][y1] > 0) return 0 ;
		int ty = abs(B[x0][y0]);
		if (ty == 1) return movep(x0, y0, x1, y1, B[x0][y0] < 0 ? -1 : 1);
		if (ty == 2) return movekn(x0, y0, x1, y1);
		if (ty == 3) return moveb(x0, y0, x1, y1);
		if (ty == 4) return mover(x0, y0, x1, y1);
		if (ty == 5) return moveq(x0, y0, x1, y1);
		if (ty == 6) return moveki(x0, y0, x1, y1);
	}

	int illegal(int x0, int y0, int x1, int y1, int player)
	{
		if (player * B[x0][y0] <= 0) return  1;
		if (move_all(x0, y0, x1, y1) == 0) return 1;
		CHESS tmp = *this;
		if (tmp.move0(x0, y0, x1, y1), tmp.check(player)) return 1;
		return 0;
	}

	int check(int player)
	{
		for (int x = 1; x <= 8; x++)
			for (int y = 1; y <= 8; y++)
				if (B[x][y] == 6 * player)
					for (int i = 1; i <= 8; i++)
						for (int j = 1; j <= 8; j++)
							if (B[i][j] * player < 0)
								if (move_all(i, j, x, y))
									return 1;
		return 0;
	}

	int checkmate(int player)
	{
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
				if (B[i][j] * player > 0)
					for (int p = 1; p <= 8; p++)
						for (int q = 1; q <= 8; q++)
							if (illegal(i, j, p ,q, player) == 0)
								return 0;
		return 1;
	}

	int stalemate(int player)
	{
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
				if (B[i][j] * player > 0)
					for (int p = 1; p <= 8; p++)
						for (int q = 1; q <= 8; q++)
							if (illegal(i, j, p ,q, player) == 0)
								return 0;
		return 1;
	}

	int move(int x0, int y0, int x1, int y1, int player)
	{
		if (illegal(x0, y0, x1, y1, player)) return show(1), 0;

		move0(x0, y0, x1, y1);

		if (check(-player) && checkmate(-player)) return show(2), 0;
		if (stalemate(-player)) return show(4), 0;
		if (check(-player)) return show(3), 1;
		return show(0), 1;
	}
}	chess;

int main()
{
	int i, j, m;
	chess.clear();
	for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
				cin >> chess.B[j][9-i];

	char str[25];
	scanf("%d %s", &m, str);
	int pl = (str[0] == 'W') ? 1 : -1;

	for (i = 1; i <= m; i++, pl = -pl)
	{
		scanf("%s", str);
		int x0 = str[0]-96, y0 = str[1]-48;
		int x1 = str[3]-96, y1 = str[4]-48;
		if (chess.move(x0, y0, x1, y1, pl) == 0) break;
	}
	if (i > m) chess.show(5);

	return 0;
}
