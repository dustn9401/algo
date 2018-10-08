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
����
N���� �������� �̷���� �ִ� Ʈ�� T�� �־����� ��, ���� ������ �����ϴ� ���α׷��� �ۼ��Ͻÿ�.
r u v: T�� ��Ʈ�� r�̶�� ���� ��, u�� v�� LCA�� ����Ѵ�.

�Է�
ù° �ٿ� ������ ���� N(1 �� N �� 100,000)�� �־�����.
��° �ٺ��� N-1���� �ٿ��� Ʈ�� T�� ���� ���� u�� v�� �־�����.
u�� v�� Ʈ���� ������ ��Ÿ���� �� �����̴�.

���� �ٿ��� ������ ���� M(1 �� M �� 100,000)�� �־�����.
���� M���� �ٿ��� ������ ��Ÿ���� r, u, v�� �־�����.

���
������ �������� �� �ٿ� �ϳ��� ����� ����Ѵ�.
*/