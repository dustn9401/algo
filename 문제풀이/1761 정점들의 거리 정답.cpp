#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 40001
using namespace std;
typedef struct node {
	int e, w;
}node;
int n, m, sz = 1;
vector<vector<node>> adj(MAXN);
vector<int> segs(MAXN), tree(MAXN * 4), w(MAXN), h(MAXN, 0), st(MAXN, 1), idx(MAXN), par(MAXN, 1);
void calc(int cur, int bef) {
	h[cur]++;
	for (node i : adj[cur])
		if (i.e^bef) calc(i.e, cur), w[i.e]=i.w, h[cur] += h[i.e];
	par[cur] = bef;
}
void HLD(int cur, int bef) {
	int hi = 0;
	for (node i : adj[cur])
		if (i.e^bef && h[i.e] > h[hi]) hi = i.e;
	for (node i : adj[cur])
		if (i.e^bef && i.e^hi) st[i.e] = i.e, HLD(i.e, cur);
	if (hi) st[hi] = st[cur], HLD(hi, cur);
	segs[sz] = cur;
	idx[cur] = sz++;
}
int init(int l, int r, int i) {
	if (l == r) return tree[i] = w[segs[l]];
	return tree[i] = init(l, (l + r) / 2, i * 2) + init((l + r) / 2 + 1, r, i * 2 + 1);
}
int small_query(int l, int r, int s, int e, int i) {
	if (l > e || r < s) return 0;
	if (l >= s && r <= e) return tree[i];
	return small_query(l, (l + r) / 2, s, e, i * 2) + small_query((l + r) / 2 + 1, r, s, e, i * 2 + 1);
}
int query(int s, int e) {
	int ret = 0;
	while (st[s] ^ st[e]) {
		if (h[st[s]] > h[st[e]]) swap(s, e);
		ret += small_query(1, sz - 1, idx[s], idx[st[s]], 1);
		s = par[st[s]];
	}
	if (h[s] > h[e]) swap(s, e);
	return ret += small_query(1, sz - 1, idx[s], idx[e] - 1, 1);
}
void build() {
	calc(1, 0);
	HLD(1, 0);
	init(1, sz - 1, 1);
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int s, e, w;
		scanf("%d%d%d", &s, &e, &w);
		adj[s].push_back({ e,w });
		adj[e].push_back({ s,w });
	}
	build();
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int s, e;
		scanf("%d%d", &s, &e);
		printf("%d\n", query(s, e));
	}
	return 0;
}

/*
����
N(2��N��40,000)���� �������� �̷���� Ʈ���� �־����� M(M��10,000)���� �� ��� ���� �Է¹��� �� �� ��� ������ �Ÿ��� ����϶�.

�Է�
ù° �ٿ� ����� ���� N�� �Էµǰ� ���� N-1���� �ٿ� Ʈ�� �� ����� �� ���� �Ÿ��� �Է¹޴´�.
�� ���� �ٿ� �Ÿ��� �˰� ���� M���� ��� ���� �� �ٿ� �� �־� �Էµȴ�. �� �� ������ �Ÿ��� 10,000���� �۰ų� ���� �ڿ����̴�.
������ 1������ N������ ��ȣ�� �Ű��� �ִ�.

���
M���� �ٿ� ���ʴ�� �Է¹��� �� ��� ������ �Ÿ��� ����Ѵ�.
*/