#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
using namespace std;
int n, m, u[100001], v[100001], w[100001], heavy[100001], divtree_size = 1;
int starts[100001], parents[100001];
vector<list<int>> adj;
vector<int> segtree, segtree_idx, idx_in_divtree, divtrees;
void maketree(int cur, int bef) {
	for (int i : adj[cur]) {
		if (bef ^ i) 
			maketree(i, cur), heavy[cur] += heavy[i];
	}
	parents[cur] = bef;
	heavy[cur]++;
}
void HLD(int cur, int bef) {
	int high = 0;
	for (int i : adj[cur])
		if (i ^ bef && heavy[i] > heavy[high])
			high = i;
	for (int i : adj[cur])
		if (i ^ bef && i ^ high)
			starts[i] = i, HLD(i, cur);
	if (high != 0)
		starts[high] = starts[cur], HLD(high, cur);
	divtrees[divtree_size] = cur;
	idx_in_divtree[cur] = divtree_size++;
}
int query(int st, int ed) {
	int ret = 0;
	while (starts[st] != starts[ed]) {
		if (heavy[starts[st]] > heavy[starts[ed]])
			swap(st, ed);
		st = parents[starts[st]];
	}
	if (heavy[st] > heavy[ed]) swap(st, ed);
	return ret;
}
int main()
{
	scanf("%d", &n);
	adj.resize(n + 1),
		idx_in_divtree.resize(n + 1),
		segtree_idx.assign(n + 1, -1),
		divtrees.resize(n + 1),
		segtree.resize(n * 4);
	starts[0] = starts[1] = parents[0] = parents[1] = 1;
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", u + i, v + i, w + i);
		adj[v[i]].push_back(u[i]), adj[u[i]].push_back(v[i]);
	}
	maketree(1, 0);
	HLD(1, 0);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		printf("%d\n", query(b, c));
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