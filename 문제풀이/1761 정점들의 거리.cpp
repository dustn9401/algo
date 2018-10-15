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
문제
N(2≤N≤40,000)개의 정점으로 이루어진 트리가 주어지고 M(M≤10,000)개의 두 노드 쌍을 입력받을 때 두 노드 사이의 거리를 출력하라.

입력
첫째 줄에 노드의 개수 N이 입력되고 다음 N-1개의 줄에 트리 상에 연결된 두 점과 거리를 입력받는다.
그 다음 줄에 거리를 알고 싶은 M개의 노드 쌍이 한 줄에 한 쌍씩 입력된다. 두 점 사이의 거리는 10,000보다 작거나 같은 자연수이다.
정점은 1번부터 N번까지 번호가 매겨져 있다.

출력
M개의 줄에 차례대로 입력받은 두 노드 사이의 거리를 출력한다.
*/