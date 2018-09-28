#include <iostream>
#include <vector>
using namespace std;
int n, m, u, v, w, idx = 0;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
vector<iii> e;
vector<vector<ii>> adj, chld;
vector<vector<ii>> divtrees(1);
vector<vector<int>> segtrees;
vector<int> level, lazy, heavy, segtree_idx, idx_in_segtree;
vector<bool> edge_in_arr;
int parents[100001][20] = {};
int bigger(int a, int b) { return a > b ? a : b; }
void maketree(int node) {
	level[node] = level[parents[node][0]] + 1;
	for (int i = 0; i < adj[node].size(); i++) {
		ii next = adj[node][i];
		if (level[next.first] != 0) continue;
		chld[node].push_back(next);
		parents[next.first][0] = node;
		maketree(next.first);
	}
}
int calc_heavy(int cur) {
	for (int i = 0; i < chld[cur].size(); i++)
		heavy[cur] += calc_heavy(chld[cur][i].first);
	return ++heavy[cur];
}
void calc_parents() {
	for (int j = 1; j < 20; j++)
		for (int i = 1; i <= n; i++)
			parents[i][j] = parents[parents[i][j - 1]][j - 1];
}
int HLD(int cur) {
	int res, ret = -1;
	for (int i = 0; i < chld[cur].size(); i++) {
		res = HLD(chld[cur][i].first);
		int cur_vtx = chld[cur][i].first;
		if (heavy[cur] <= heavy[cur_vtx] * 2) {
			if (res == -1)
				ret = divtrees.size() - 1;
			else
				ret = res;
		}
		idx = res == -1 ? divtrees.size() - 1 : res;
		idx_in_segtree[cur_vtx] = divtrees[idx].size();
		segtree_idx[cur_vtx] = idx;
		divtrees[idx].push_back({ cur_vtx,  e[chld[cur][i].second].second });
		if (res == -1) divtrees.resize(divtrees.size() + 1);
	}
	return ret;
}
int seg(int l, int r, int idx, const vector<ii>& tree, vector<int>& segtree) {
	if (l == r)
		return segtree[l] = tree[l].second;
	return segtree[idx] = bigger(seg(l, (l + r) / 2, idx * 2, tree, segtree), seg((l + r) / 2 + 1, r, idx * 2 + 1, tree, segtree));
}
void make_segtree(const vector<vector<ii>>& trees) {
	for (int i = 0; i < trees.size() - 1; i++) {
		segtrees[i].resize(trees[i].size() * 2 + 10);
		seg(0, trees[i].size() - 1, 1, trees[i], segtrees[i]);
	}
}
int small_query(int st, int ed, int l, int r, int cur, int tree_idx) {
	if (l >= st && r <= ed)
		return segtrees[tree_idx][cur];
	if (r < st || l > ed)
		return 0;
	return bigger(small_query(st, ed, l, (l + r) / 2, cur * 2, tree_idx), small_query(st, ed, (l + r) / 2 + 1, r, cur * 2 + 1, tree_idx));
}
int query(int st, int ed) {
	int st_idx = segtree_idx[st];
	int ed_idx;
	int cur_st_lev = level[(--divtrees[st_idx].end())->first];
	st = idx_in_segtree[st_idx];
	if (cur_st_lev <= level[ed]) {
		ed_idx = segtrees[st_idx].size() - 1;
		return small_query(st, ed_idx, 0, ed_idx, 1, segtree_idx[st_idx]);
	}
	ed_idx = segtrees[st_idx].size() - 1;
	return bigger(small_query(st, ed_idx, 0, ed_idx, 1, segtree_idx[st_idx]), query(parents[ed][0], ed));
}
int LCA(int a, int b) {
	if (level[a] < level[b]) {
		int tmp = a;
		a = b;
		b = tmp;
	}
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

int main()
{
	scanf("%d", &n);
	adj.resize(n + 1), level.assign(n + 1, 0), lazy.assign(n + 1, 0), heavy.assign(n + 1, 0), chld.resize(n + 1), idx_in_segtree.resize(n + 1),
		segtree_idx.assign(n + 1, -1), edge_in_arr.assign(n + 1, false), segtrees.resize(n);
	for (int i = 0; i < n - 1; i++) {
		scanf("%d%d%d", &u, &v, &w);
		e.push_back({ {u,v},w });
		adj[u].push_back({ v,i });
		adj[v].push_back({ u,i });
	}
	maketree(1);
	calc_parents();
	calc_heavy(1);
	HLD(1);
	make_segtree(divtrees);

	printf("seg done\n");
	//for (int i = 0; i < idx + 1; i++) {
	//	for (int j = 0; j < divtrees[i].size(); j++)
	//		printf("%d, ", divtrees[i][j].first + 1);
	//	printf("\n");
	//}
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		if (a == 2) {
			int lca = LCA(b, c);
			printf("lca = %d\n", lca);
			printf("%d\n", bigger(query(b, lca), query(c, lca)));
		}
	}
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
1 11 1
2 3 2
2 7 1
3 4 1
3 5 1
5 6 1
7 8 1
7 9 1
8 10 1
11 12 1
11 13 1
1
2 3 13
*/