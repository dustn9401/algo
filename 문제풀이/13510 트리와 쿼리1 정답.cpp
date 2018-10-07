#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
using namespace std;
int n, m, u[100001], v[100001], w[100001], level[100001], heavy[100001], divtree_size = 1;
int starts[100001], parents[100001];
typedef struct pair<int, int> ii;
vector<list<ii>> adj;
vector<list<int>> chlds;
vector<int> segtree, segtree_idx, idx_in_divtree, node_edge_idx, divtrees, node_weights;
void maketree(int cur, int bef) {
	level[cur] = level[bef] + 1;
	for (ii i : adj[cur]) {
		if (bef == i.first) continue;
		chlds[cur].push_back(i.first);
		node_edge_idx[i.second] = i.first;
		node_weights[i.first] = w[i.second];
		maketree(i.first, cur);
		heavy[cur] += heavy[i.first];
	}
	parents[cur] = bef;
	heavy[cur]++;
}
void HLD(int cur, int bef) {
	int high = 0;
	for (int i : chlds[cur])
		if (heavy[i] > heavy[high])
			high = i;
	for (int i : chlds[cur])
		if (i != high)
			starts[i] = i, HLD(i, cur);
	if (high != 0)
		starts[high] = starts[cur], HLD(high, cur);
	divtrees[divtree_size] = cur;
	idx_in_divtree[cur] = divtree_size++;
}
int update(int st, int ed, int idx, int change, int cur) {
	if (st > idx || ed < idx)
		return segtree[cur];
	if (st == ed)
		return segtree[cur] = change;
	return segtree[cur] = max(
		update(st, (st + ed) / 2, idx, change, cur * 2),
		update((st + ed) / 2 + 1, ed, idx, change, cur * 2 + 1));
}
int make_segtree(int l, int r, int idx) {
	if (l == r) return segtree[idx] = node_weights[divtrees[l]];
	return segtree[idx] = max(
		make_segtree(l, (l + r) / 2, idx * 2),
		make_segtree((l + r) / 2 + 1, r, idx * 2 + 1));
}
int small_query(int st, int ed, int l, int r, int cur) {
	if (r < st || l > ed)
		return 0;
	if (l >= st && r <= ed)
		return segtree[cur];
	return max(
		small_query(st, ed, l, (l + r) / 2, cur * 2),
		small_query(st, ed, (l + r) / 2 + 1, r, cur * 2 + 1));
}
int query(int st, int ed) {
	int ret = 0;
	while (starts[st] != starts[ed]) {
		if (heavy[starts[st]] > heavy[starts[ed]])
			swap(st, ed);
		ret = max(ret, small_query(idx_in_divtree[st], idx_in_divtree[starts[st]], 1, divtree_size - 1, 1));
		st = parents[starts[st]];
	}
	if (heavy[st] > heavy[ed]) swap(st, ed);
	return max(ret, small_query(idx_in_divtree[st], idx_in_divtree[ed] - 1, 1, divtree_size - 1, 1));
}
int main()
{
	scanf("%d", &n);
	adj.resize(n + 1),
		idx_in_divtree.resize(n + 1),
		segtree_idx.assign(n + 1, -1),
		node_edge_idx.resize(n + 1),
		chlds.resize(n + 1),
		divtrees.resize(n + 1),
		segtree.resize(n * 4),
		node_weights.resize(n+1);
	starts[0] = starts[1] = parents[0] = parents[1] = 1;
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", u + i, v + i, w + i);
		adj[v[i]].push_back({ u[i], i });
		adj[u[i]].push_back({ v[i], i });
	}
	maketree(1, 0);
	HLD(1, 0);
	make_segtree(1, divtree_size - 1, 1);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		if (a == 2)
			printf("%d\n", query(b, c));
		if (a == 1)
			update(1, divtree_size - 1, idx_in_divtree[node_edge_idx[b]], c, 1);
	}
	return 0;
}
/*
����
N���� �������� �̷���� Ʈ��(������ ����Ŭ�� ���� ���� �׷���)�� �ִ�.
������ 1������ N������ ��ȣ�� �Ű��� �ְ�, ������ 1������ N-1������ ��ȣ�� �Ű��� �ִ�.
�Ʒ��� �� ������ �����ϴ� ���α׷��� �ۼ��Ͻÿ�.

1 i c: i�� ������ ����� c�� �ٲ۴�.
2 u v: u���� v�� ���� ��ο� �����ϴ� ��� �߿��� ���� ū ���� ����Ѵ�.

�Է�
ù° �ٿ� N (2 �� N �� 100,000)�� �־�����.
��° �ٺ��� N-1���� �ٿ��� i�� ������ �����ϴ� �� ���� ��ȣ u�� v�� ��� w�� �־�����.
���� �ٿ��� ������ ���� M (1 �� M �� 100,000)�� �־�����.
���� M���� �ٿ��� ������ �� �ٿ� �ϳ��� �־�����.
������ ����� �׻� 1,000,000���� �۰ų� ���� �ڿ����̴�.

���
������ 2�� ������ ����� ������� �� �ٿ� �ϳ��� ����Ѵ�.

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
1 4 20
2 8 9

17
10 2 1
10 6 2
10 4 3
2 5 4
2 1 5
6 7 6
4 8 7
4 9 8
4 11 9
1 13 10
9 12 11
9 3 12
13 16 13
13 17 14
12 14 15
12 15 16
100
*/