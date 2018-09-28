#include <iostream>
#include <vector>
using namespace std;
int level[50001] = { 0 }, parent[50001][20] = {};
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

/*
문제
N(2 ≤ N ≤ 50,000)개의 정점으로 이루어진 트리가 주어진다. 트리의 각 정점은 1번부터 N번까지 번호가 매겨져 있으며, 루트는 1번이다.
두 노드의 쌍 M(1 ≤ M ≤ 10,000)개가 주어졌을 때, 두 노드의 가장 가까운 공통 조상이 몇 번인지 출력한다.

입력
첫째 줄에 노드의 개수 N이 주어지고, 다음 N-1개 줄에는 트리 상에서 연결된 두 정점이 주어진다.
그 다음 줄에는 가장 가까운 공통 조상을 알고싶은 쌍의 개수 M이 주어지고, 다음 M개 줄에는 정점 쌍이 주어진다.

출력
M개의 줄에 차례대로 입력받은 두 정점의 가장 가까운 공통 조상을 출력한다.
*/