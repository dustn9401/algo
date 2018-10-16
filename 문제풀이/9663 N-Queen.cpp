#include <cstdio>
#include <cstring>
typedef struct point {
	int x, y;
}point;
int n;
int map[16][16];
point ek() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (!map[i][j]) return { i,j };
	return { 0,0 };
}
void ck(int x, int y) {
	map[x][y] = 2;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i == x || j == y || i - x == j - y || x + y == i + j) if(map[i][j] != 2) map[i][j] = 1;
}
int dfs(int x, int y) {
	int ret = 0;
	if (x < 1 || x > n || y < 1 || y > n || map[x][y]) return 0;
	if (!map[x][y]) ret = 1;
	ck(x, y);
	for (int i = 1; i <= n; i++, printf("\n"))
		for (int j = 1; j <= n; j++)
			printf("%d", map[i][j]);
	printf("\n");
	return ret + 
		dfs(x - 2, y - 1) + 
		dfs(x - 1, y - 2) +
		dfs(x - 2, y + 1) +
		dfs(x - 1, y + 2) +
		dfs(x + 1, y - 2) +
		dfs(x + 2, y - 1) +
		dfs(x + 1, y + 2) +
		dfs(x + 2, y + 1);
}
int solve() {
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int ans = 0;
			memset(map, 0, sizeof(map));
			ans += dfs(i, j);
			while (true) {
				point p = ek();
				if (p.x == 0) break;
				ans += dfs(p.x, p.y);
			}
			printf("ans = %d\n", ans);
			if (ans == n) ret++;
		}
	}
	return ret;
}
int main()
{
	scanf("%d", &n);
	printf("%d", solve());
	return 0;
}