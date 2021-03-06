#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
using namespace std;
int n, m, u, v, w, divtree_size, c;
typedef struct pair<int, int> ii;
typedef struct {
	int st, ed, weight;
}edge;
vector<edge> e;
vector<list<ii>> adj;
vector<vector<int>> segtrees, divtrees, chlds;
vector<int> level, heavy, segtree_idx, idx, node_edge_idx, node_weights;
int parents[100001][20];
void maketree(int cur, int bef) {
	level[cur] = level[bef] + 1;
	for (ii i : adj[cur]) {
		if (bef == i.first) continue;
		chlds[cur].push_back(i.first);
		node_edge_idx[i.second] = i.first;
		node_weights[i.first] = e[i.second].weight;
		maketree(i.first, cur);
		heavy[cur] += heavy[i.first];
	}
	parents[cur][0] = bef;
	heavy[cur]++;
}
void calc_parents() {
	for (int j = 1; j < 20; j++)
		for (int i = 1; i <= n; i++)
			parents[i][j] = parents[parents[i][j - 1]][j - 1];
}
void HLD(int cur, int bef, int tree_idx) {
	int high = 0;
	for (auto i : chlds[cur])
		if (heavy[i] > heavy[high])
			high = i;
	for (auto i : chlds[cur]) {
		if (i == high)
			HLD(high, cur, tree_idx);
		else
			HLD(i, cur, ++divtree_size);
	}
	if (cur == 1) return;
	idx[cur] = divtrees[tree_idx].size();
	segtree_idx[cur] = tree_idx;
	divtrees[tree_idx].push_back(cur);
}
int seg(int l, int r, int idx, int tree_idx) {
	if (l == r)
		return segtrees[tree_idx][idx] = node_weights[divtrees[tree_idx][l]];
	return segtrees[tree_idx][idx] = max(
		seg(l, (l + r) / 2, idx * 2, tree_idx),
		seg((l + r) / 2 + 1, r, idx * 2 + 1, tree_idx));
}
void make_segtree() {
	for (int i = 0; i < divtree_size + 1; i++) {
		if (divtrees[i].size() == 1) continue;
		segtrees[i].resize(divtrees[i].size() * 4);
		seg(1, divtrees[i].size() - 1, 1, i);
	}
}
int update(int st, int ed, int idx, int change, int cur, int tree_idx) {
	if (st > idx || ed < idx)
		return segtrees[tree_idx][cur];
	if (st == ed)
		return segtrees[tree_idx][cur] = change;
	return segtrees[tree_idx][cur] = max(
		update(st, (st + ed) / 2, idx, change, cur * 2, tree_idx),
		update((st + ed) / 2 + 1, ed, idx, change, cur * 2 + 1, tree_idx));
}
int small_query(int st, int ed, int l, int r, int cur, int tree_idx) {
	if (r < st || l > ed)
		return 0;
	if (l >= st && r <= ed)
		return segtrees[tree_idx][cur];
	return max(
		small_query(st, ed, l, (l + r) / 2, cur * 2, tree_idx),
		small_query(st, ed, (l + r) / 2 + 1, r, cur * 2 + 1, tree_idx));
}
int LCA(int a, int b) {
	if (level[a] < level[b]) swap(a, b);
	int i;
	while (level[a] != level[b]) {
		i = -1;
		while (level[parents[a][i + 1]] >= level[b])
			++i;
		a = parents[a][i];
	}
	while (a != b) {
		i = 0;
		while (parents[a][i + 1] != parents[b][i + 1])
			++i;
		a = parents[a][i], b = parents[b][i];
	}
	return a;
}
int query(int st, int ed) {
	int lca = LCA(st, ed);
	int ret = 0, i, last;
	if (st != lca) {
		while (true) {
			i = segtree_idx[st];
			last = divtrees[i].back();
			if (level[last] <= level[lca] + 1) break;
			ret = max(ret, small_query(idx[st], idx[last], 1, divtrees[i].size() - 1, 1, i));
			st = parents[last][0];
		}
		if(i == segtree_idx[lca])
			ret = max(ret, small_query(idx[st], idx[lca] - 1, 1, divtrees[i].size() - 1, 1, i));
		else
			ret = max(ret, small_query(idx[st], divtrees[i].size() - 1, 1, divtrees[i].size() - 1, 1, i));
	}
	if (ed != lca) {
		while (true) {
			i = segtree_idx[ed];
			last = divtrees[i].back();
			if (level[last] <= level[lca] + 1) break;
			ret = max(ret, small_query(idx[ed], idx[last], 1, divtrees[i].size() - 1, 1, i));
			ed = parents[last][0];
		}
		if (i == segtree_idx[lca])
			ret = max(ret, small_query(idx[ed], idx[lca] - 1, 1, divtrees[i].size() - 1, 1, i));
		else
			ret = max(ret, small_query(idx[ed], divtrees[i].size() - 1, 1, divtrees[i].size() - 1, 1, i));
	}
	return ret;
}

int main()
{
	scanf("%d", &n);
	adj.resize(n + 1),
		level.assign(n + 1, 0),
		heavy.assign(n + 1, 0),
		idx.resize(n + 1),
		node_weights.resize(n + 1),
		segtree_idx.assign(n + 1, -1),
		segtrees.resize(n + 1),
		node_edge_idx.resize(n + 1),
		e.resize(n + 1),
		divtrees.assign(n + 1, { 0 }),
		chlds.resize(n + 1);

	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", &e[i].st, &e[i].ed, &e[i].weight);
		adj[e[i].st].push_back({ e[i].ed, i });
		adj[e[i].ed].push_back({ e[i].st, i });
	}
	maketree(1, 0);
	calc_parents();
	HLD(1, 0, divtree_size);
	make_segtree();
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);

		if (a == 2)
			printf("%d\n", query(b, c));
		if (a == 1) {
			int node = node_edge_idx[b];
			int tree_idx = segtree_idx[node];
			update(1, divtrees[tree_idx].size() - 1, idx[node], c, 1, tree_idx);
			node_weights[node] = c;
		}
	}
	return 0;
}
/*
문제
N개의 정점으로 이루어진 트리(무방향 사이클이 없는 연결 그래프)가 있다.
정점은 1번부터 N번까지 번호가 매겨져 있고, 간선은 1번부터 N-1번까지 번호가 매겨져 있다.
아래의 두 쿼리를 수행하는 프로그램을 작성하시오.

1 i c: i번 간선의 비용을 c로 바꾼다.
2 u v: u에서 v로 가는 경로에 존재하는 비용 중에서 가장 큰 것을 출력한다.

입력
첫째 줄에 N (2 ≤ N ≤ 100,000)이 주어진다.
둘째 줄부터 N-1개의 줄에는 i번 간선이 연결하는 두 정점 번호 u와 v와 비용 w가 주어진다.
다음 줄에는 쿼리의 개수 M (1 ≤ M ≤ 100,000)이 주어진다.
다음 M개의 줄에는 쿼리가 한 줄에 하나씩 주어진다.
간선의 비용은 항상 1,000,000보다 작거나 같은 자연수이다.

출력
각각의 2번 쿼리의 결과를 순서대로 한 줄에 하나씩 출력한다.

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