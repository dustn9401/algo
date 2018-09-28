#include <iostream>
#include <vector>
using namespace std;
int level[100001] = { 0 }, parent[100001][20] = {};
vector<vector<int>> v;
int n, m;
void make_tree(int node) {
	level[node] = level[parent[node][0]] + 1;
	for (int i = 0; i < v[node].size(); i++) {
		int chld = v[node][i];
		if (level[chld] != 0) continue;
		parent[chld][0] = node;
		make_tree(chld);
	}
}
void preproc() {
	for (int j = 1; j < 20; j++) {
		for (int i = 1; i <= n; i++) {
			parent[i][j] = parent[parent[i][j - 1]][j - 1];
		}
	}
}
int LCA(int a, int b) {
	if (level[a] < level[b]) {
		int tmp = a;
		a = b;
		b = tmp;
	}
	int ret = 0;
	int i;
	while (level[a] != level[b]) {
		i = -1;
		while (level[parent[a][i + 1]] >= level[b])
			++i;
		a = parent[a][i];
	}
	while (a != b) {
		i = 0;
		while (parent[a][i + 1] != parent[b][i + 1])
			++i;
		a = parent[a][i], b = parent[b][i];
	}
	return a;
}
int main()
{
	int a, b;
	scanf("%d", &n);
	v.resize(n + 1);
	for (int i = 0; i < n - 1; i++) {
		scanf("%d%d", &a, &b);
		v[a].push_back(b), v[b].push_back(a);
	}
	make_tree(1);
	preproc();

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		printf("%d\n", LCA(a, b));
	}
	return 0;
}
