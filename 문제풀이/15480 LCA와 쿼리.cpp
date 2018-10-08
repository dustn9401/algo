#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
int n, m, u[100001], v[100001], parent[100001][20], level[100001];
vector<list<int>> adj(100001);
void maketree(int cur, int bef) {
	level[cur] = level[bef] + 1;
	for (int i : adj[cur])
		if (bef ^ i) 
			maketree(i, cur);
	parent[cur][0] = bef;
}
void preproc() {
	for (int j = 1; j < 20; j++)
		for (int i = 1; i <= n; i++)
			parent[i][j] = parent[parent[i][j - 1]][j - 1];
}
int LCA(int a, int b) {
	if(level[a] < level[b]) 
		swap(a, b);
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
int query(int a, int b, int c) {
	int ret = LCA(a, b), lca2 = LCA(b, c), lca3 = LCA(c, a);
	if (level[ret] < level[lca2]) ret = lca2;
	if (level[ret] < level[lca3]) ret = lca3;
	return ret;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", u + i, v + i);
		adj[v[i]].push_back(u[i]), adj[u[i]].push_back(v[i]);
	}
	maketree(1, 0);
	preproc();
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		printf("%d\n", query(a,b,c));
	}
	return 0;
}
/*
문제
N개의 정점으로 이루어져 있는 트리 T가 주어졌을 때, 다음 쿼리를 수행하는 프로그램을 작성하시오.
r u v: T의 루트가 r이라고 했을 때, u와 v의 LCA를 출력한다.

입력
첫째 줄에 정점의 개수 N(1 ≤ N ≤ 100,000)이 주어진다.
둘째 줄부터 N-1개의 줄에는 트리 T의 간선 정보 u와 v가 주어지다.
u와 v는 트리의 간선을 나타내는 두 정점이다.

다음 줄에는 쿼리의 개수 M(1 ≤ M ≤ 100,000)가 주어진다.
다음 M개의 줄에는 쿼리를 나타내는 r, u, v가 주어진다.

출력
각각의 쿼리마다 한 줄에 하나씩 결과를 출력한다.
*/