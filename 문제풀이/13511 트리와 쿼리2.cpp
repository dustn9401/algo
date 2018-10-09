#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
using namespace std;
int n, m, u[100001], v[100001], w[100001], level[100001], heavy[100001], divtree_size = 1;
int starts[100001], parents[100001];
vector<list<int>> adj;
vector<int> segtree(400000), idx(100001), divtrees(100001);
void maketree(int cur, int bef) {
	level[cur] = level[bef] + 1;
	for (int i : adj[cur]) {
		if (bef^i) maketree(i, cur), heavy[cur] += heavy[i];
	}
	parents[cur] = bef;
	heavy[cur]++;
}
void HLD(int cur, int bef) {
	int high = 0;
	for (int i : adj[cur])
		if (bef^i && heavy[i] > heavy[high])
			high = i;
	for (int i : adj[cur])
		if (bef^i && i != high)
			starts[i] = i, HLD(i, cur);
	if (high)
		starts[high] = starts[cur], HLD(high, cur);
	divtrees[divtree_size] = cur;
	idx[cur] = divtree_size++;
}
int make_segtree(int l, int r, int idx) {
	if (l == r) return segtree[idx] = node_weights[divtrees[l]];
	return segtree[idx] = make_segtree(l, (l + r) / 2, idx * 2) + make_segtree((l + r) / 2 + 1, r, idx * 2 + 1);
}
int small_query(int st, int ed, int l, int r, int cur) {
	if (r < st || l > ed)
		return 0;
	if (l >= st && r <= ed)
		return segtree[cur];
	return small_query(st, ed, l, (l + r) / 2, cur * 2) + small_query(st, ed, (l + r) / 2 + 1, r, cur * 2 + 1);
}
int query(int st, int ed, int k) {
	int ret = 0, rem = k, up;
	list<int> l, r;
	while (starts[st] != starts[ed]) {
		up = heavy[st] > heavy[ed] ? ed : st;
		ret += small_query(idx[up], idx[starts[up]], 1, divtree_size - 1, 1);
		if (up == st)
			st = parents[starts[st]];
		else
			ed = parents[starts[ed]];
	}
	up = heavy[st] > heavy[ed] ? ed : st;
	ret += small_query(idx[up], idx[up] - 1, 1, divtree_size - 1, 1);
	return ret;
}
int main()
{
	scanf("%d", &n);
	starts[0] = starts[1] = parents[0] = parents[1] = 1;
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", u + i, v + i, w + i);
		adj[v[i]].push_back(u[i]);
		adj[u[i]].push_back(v[i]);
	}
	maketree(1, 0);
	HLD(1, 0);
	make_segtree(1, divtree_size - 1, 1);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int a, b, c, k;
		scanf("%d%d%d", &a, &b, &c);
		if (a == 1)
			printf("%d\n", query(b, c, 0));
		else
			scanf("%d", &k), printf("%d\n", query(b, c, k));
	}
	return 0;
}
/*
13
1 2 1
1 11 2
2 3 3
2 7 4
3 4 5
3 5 6
5 6 7
7 8 8
7 9 9
8 10 10
11 12 11
11 13 12
100
*/