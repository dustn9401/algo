#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
using namespace std;
int n, m, u, v, w, divtree_size = 0;
typedef struct pair<int, int> ii;
typedef struct {
	int st, ed, weight;
}edge;
vector<edge> e;
vector<list<ii>> adj;
vector<vector<int>> segtrees, divtrees, chlds;
vector<int> level, heavy, segtree_idx, idx_in_divtree, node_edge_idx, node_weights;
int parents[100001][20];
void maketree(int cur, int bef) {
	level[cur] = level[bef] + 1;
	for (auto i : adj[cur]) {
		if (bef == i.first) continue;
		chlds[cur].push_back(i.first);
		node_edge_idx[i.second] = i.first;
		node_weights[i.first] = e[i.second].weight;
		parents[i.first][0] = cur;
		maketree(i.first, cur);
		heavy[cur] += heavy[i.first];
	}
	++heavy[cur];
}
void calc_parents() {
	for (int j = 1; j < 20; j++)
		for (int i = 1; i <= n; i++)
			parents[i][j] = parents[parents[i][j - 1]][j - 1];
}
void HLD(int cur, int bef, int idx) {
	int high = 0;
	for (auto i : chlds[cur])
		if (heavy[i] > heavy[high]) 
			high = i;
	for (auto i : chlds[cur]) {
		if(i == high)
			HLD(high, cur, idx);
		else
			HLD(i, cur, ++divtree_size);
	}
	if (cur == 1) return;
	idx_in_divtree[cur] = divtrees[idx].size();
	segtree_idx[cur] = idx;
	divtrees[idx].push_back(cur);
}
int seg(int l, int r, int idx, int tree_idx) {
	if (l == r)
		return segtrees[tree_idx][idx] = node_weights[divtrees[tree_idx][l]];
	return segtrees[tree_idx][idx] = max(
		seg(l, (l + r) / 2, idx * 2, tree_idx),
		seg((l + r) / 2 + 1, r, idx * 2 + 1, tree_idx));
}
void make_segtree() {
	for (int i = 0; i < divtree_size+1; i++) {
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
int query(int st, int ed) {
	int ret = 0, idx, high;
	while (true) {
		idx = segtree_idx[st], high = divtrees[idx].back();
		if (level[ed] >= level[parents[high][0]]) break;
		ret = max(ret, small_query(idx_in_divtree[st], idx_in_divtree[high], 1, divtrees[idx].size() - 1, 1, idx));
		st = parents[high][0];
	}
	return max(ret, small_query(idx_in_divtree[st], idx_in_divtree[high], 1, divtrees[idx].size() - 1, 1, idx));
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

int main()
{
	FILE *fp = fopen("C:\\input.txt", "r");
	fscanf(fp, "%d", &n);
	adj.resize(n + 1),
		level.assign(n + 1, 0),
		heavy.assign(n + 1, 0),
		idx_in_divtree.resize(n + 1),
		node_weights.resize(n + 1),
		segtree_idx.assign(n + 1, -1),
		segtrees.resize(n + 1),
		node_edge_idx.resize(n + 1),
		e.resize(n + 1),
		divtrees.assign(n + 1, { 0 }),
		chlds.resize(n + 1);

	for (int i = 1; i < n; i++) {
		fscanf(fp, "%d%d%d", &e[i].st, &e[i].ed, &e[i].weight);
		adj[e[i].st].push_back({ e[i].ed, i });
		adj[e[i].ed].push_back({ e[i].st, i });
	}

	long start = clock();
	maketree(1, 0);
	long end = clock();
	printf("maketree: %.3lf\n", (end - start)/(double)CLOCKS_PER_SEC);

	start = clock();
	calc_parents();
	end = clock();
	printf("calc_par: %.3lf\n", (end - start) / (double)CLOCKS_PER_SEC);

	start = clock();
	HLD(1, 0, divtree_size);
	end = clock();
	printf("HLD: %.3lf\n", (end - start) / (double)CLOCKS_PER_SEC);
	//printf("Divtrees = \n");
	//for (auto i : divtrees) {
	//	for (auto j : i) {
	//		printf("%d, ", j);
	//	}
	//	printf("\n");
	//}

	start = clock();
	make_segtree();
	end = clock();
	printf("make segtree: %.3lf\n", (end - start) / (double)CLOCKS_PER_SEC);
	//printf("Segtrees = \n");
	//for (auto i : segtrees) {
	//	for (auto j : i) {
	//		printf("%d, ", j);
	//	}
	//	printf("\n");
	//}
	double quer = 0, updat = 0;
	FILE *fp2 = fopen("C:\\output.txt", "r");
	fscanf(fp, "%d", &m);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		fscanf(fp, "%d%d%d", &a, &b, &c);

		if (a == 2) {
			start = clock();
			int lca = LCA(b, c);
			int res;
			if (b == c)
				res = 0;
			else if (b == lca)
				res = query(c, lca);
			else if (c == lca)
				res = query(b, lca);
			else
				res = max(query(b, lca), query(c, lca));
			int tmp;
			fscanf(fp2, "%d", &tmp);
			if (res == tmp) printf("O");
			else printf("X");

				/*printf("\nX query #%d a,b,c=%d,%d,%d, res=%d, cor = %d\n", i, a, b, c, res, tmp);
				printf("weights = ");
				for (auto i : node_weights)
				{
					printf("%d, ", i);
				}
				printf("\n");
				printf("\n");
				printf("divtrees\n");
				for (auto i : divtrees)
				{
					for(auto j : i)
						printf("%d, ", j);
					printf("\n");
				}
				printf("segtree b\n");
				for (auto i : segtrees[segtree_idx[b]])
					printf("%d, ", i);
				printf("\n");
				printf("segtree c\n");
				for (auto i : segtrees[segtree_idx[c]])
					printf("%d, ", i);
				printf("\n");*/
			
			end = clock();
			quer += ((end - start) / (double)CLOCKS_PER_SEC);
		}
		if (a == 1) {
			start = clock();
			int node = node_edge_idx[b];
			int idx = segtree_idx[node];
			update(1, divtrees[idx].size() - 1, idx_in_divtree[node], c, 1, idx);
			node_weights[node] = c;

			end = clock();
			updat += ((end - start) / (double)CLOCKS_PER_SEC);
		}
	}

	printf("query: %.3lf\n", quer);
	printf("update: %.3lf\n", updat);

	fclose(fp);
	fclose(fp2);
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