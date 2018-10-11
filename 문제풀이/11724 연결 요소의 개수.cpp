#include <cstdio>
#include <vector>
using namespace std;
int n, m;
vector<vector<int>> adj(1001);
vector<bool> v(1001, false);
bool dfs(int cur) {
	if (v[cur]) return false;
	v[cur] = true;
	for (auto i : adj[cur]) dfs(i);
	return true;
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int res = 0;
	for (int i = 1; i <= n; i++)
		if (dfs(i)) res++;
	printf("%d", res);
	return 0;
}