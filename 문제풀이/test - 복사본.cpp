#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
using namespace std;
int n, m, u[100001], v[100001], w[100001], level[100001], heavy[100001], divtree_size = 1;
int starts[100001];
typedef struct pair<int, int> ii;
vector<list<ii>> adj;
vector<list<int>> chlds;
vector<int> segtree, segtree_idx, idx_in_divtree, node_edge_idx, divtrees;
int parents[100001];
void maketree(int cur, int bef) {
	level[cur] = level[bef] + 1;
	for (ii i : adj[cur]) {
		if (bef == i.first) continue;
		chlds[cur].push_back(i.first);
		node_edge_idx[i.second] = i.first;
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
	//if (cur == 1) return;
	//if (starts[cur] == 0) starts[cur] = starts[bef];
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
void make_segtree() {
	for (int i = 1; i < divtree_size; i++)
		update(1, divtree_size - 1, idx_in_divtree[node_edge_idx[i]], w[i], 1);
}
int small_query(int st, int ed, int l, int r, int cur) {
	if (r < st || l > ed)
		return 0;
	//printf("(%d, %d, %d, %d, %d)\n", st, ed, l, r, cur);
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
		//printf("st %d, ed %d, ret = %d\n", st, ed, ret);
		ret = max(ret, small_query(idx_in_divtree[st], idx_in_divtree[starts[st]], 1, divtree_size - 1, 1));
		st = parents[starts[st]];
	}
	//printf("st %d, ed %d, ret = %d\n", st, ed, ret);
	if (heavy[st] > heavy[ed]) swap(st, ed);
	return max(ret, small_query(idx_in_divtree[st], idx_in_divtree[ed] - 1, 1, divtree_size - 1, 1));
}
int main()
{
	FILE *fp = fopen("C:\\input.txt", "r");
	fscanf(fp, "%d", &n);
	adj.resize(n + 1),
		idx_in_divtree.resize(n + 1),
		segtree_idx.assign(n + 1, -1),
		node_edge_idx.resize(n + 1),
		chlds.resize(n + 1),
		divtrees.resize(n + 1),
		segtree.resize(n * 4);
	starts[0] = starts[1] = parents[0] = parents[1] = 1;
	for (int i = 1; i < n; i++) {
		fscanf(fp, "%d%d%d", u + i, v + i, w + i);
		adj[v[i]].push_back({ u[i], i });
		adj[u[i]].push_back({ v[i], i });
	}

	long start = clock();
	maketree(1, 0);
	long end = clock();
	printf("maketree: %.3lf\n", (end - start) / (double)CLOCKS_PER_SEC);

	start = clock();
	HLD(1, 0);
	end = clock();
	printf("HLD: %.3lf\n", (end - start) / (double)CLOCKS_PER_SEC);

	start = clock();
	make_segtree();
	end = clock();
	printf("make segtree: %.3lf\n", (end - start) / (double)CLOCKS_PER_SEC);
	//for (int i = 1; i < divtree_size; i++)printf("%d, ", divtrees[i]);
	double quer = 0, updat = 0;
	FILE *fp2 = fopen("C:\\output.txt", "r");
	fscanf(fp, "%d", &m);
	//scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		fscanf(fp, "%d%d%d", &a, &b, &c);
		//scanf("%d%d%d", &a, &b, &c);

		if (a == 2) {
			start = clock();
			int res = query(b, c);
			end = clock();
			quer += ((end - start) / (double)CLOCKS_PER_SEC);

			int tmp;
			fscanf(fp2, "%d", &tmp);
			if (res == tmp) printf("O");
			else printf("X");
			//printf("res = %d\n", res);
		}
		if (a == 1) {
			start = clock();
			int node = node_edge_idx[b];
			int idx = idx_in_divtree[node];
			update(1, divtree_size - 1, idx, c, 1);

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