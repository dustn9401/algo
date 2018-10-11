#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int m, n, k;
vector<int> ans;
bool map[101][101];
int dfs(int i, int j) {
	if (i < 0 || j < 0 || i >= m || j >= n || map[i][j]) return 0;
	map[i][j] = true;
	return dfs(i + 1, j) + dfs(i, j + 1) + dfs(i - 1, j) + dfs(i, j - 1) + 1;
}
int main()
{
	scanf("%d%d%d", &m, &n, &k);
	for (int i = 0; i < k; i++) {
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		for (int j = a; j < c; j++)
			for (int k = b; k < d; k++)
				map[k][j] = true;
	}
	int ret;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (ret = dfs(i, j)) ans.push_back(ret);
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for (int i : ans)
		printf("%d ", i);
	return 0;
}