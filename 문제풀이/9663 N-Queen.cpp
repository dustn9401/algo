#include <cstdio>
#include <cstring>
#include <cstdlib>
int n;

int dfs(int x, int y, int **map) {
	int ret = 0, cnt = 0;
	int **new_map = (int **)malloc(sizeof(int *)*(n + 1));
	for (int i = 0; i <= n; i++)
		new_map[i] = (int *)malloc(sizeof(int)*(n + 1));
	memcpy(new_map, map, sizeof(int)*(n+1)*(n+1));
	new_map[x][y] = 2;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i == x || j == y || i - x == j - y || x + y == i + j) 
				if(new_map[i][j] != 2) new_map[i][j] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (!new_map[i][j]) dfs(i, j, new_map);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (new_map[i][j] == 2) cnt++;
	if (cnt == n) ret++;
	for (int i = 0; i <= n; i++)
		free(new_map[i]);
	free(new_map);
	return ret;
}
int main()
{
	scanf("%d", &n);
	int **map = (int **)malloc(sizeof(int *)*(n + 1));
	for (int i = 0; i <= n; i++)
		map[i] = (int *)malloc(sizeof(int)*(n + 1));
	printf("%d", dfs(1,1,map));
	for (int i = 0; i <= n; i++)
		free(map[i]);
	free(map);
	return 0;
}