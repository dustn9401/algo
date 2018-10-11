#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char map[21][21];
int r, c;
int dfs(int i, int j, bool flag[]) {
	if (i < 0 || j < 0 || i >= r || j >= c || flag[map[i][j]]) 
		return 0;
	bool f[100];
	memcpy(f, flag, sizeof(f));
	f[map[i][j]] = true;
	return 1 + max(dfs(i - 1, j, f), max(dfs(i, j - 1, f), max(dfs(i + 1, j, f), dfs(i, j + 1, f))));
}
int main()
{
	scanf("%d%d", &r, &c);
	for (int i = 0; i < r; i++)
		scanf("%s", map+i);
	bool f[100] = { false };
	printf("%d", dfs(0, 0, f));
	return 0;
}