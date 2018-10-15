#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef struct node {
	ll e, w;
}node;
ll w[100001];
int n, m, u[100001], v[100001], heavy[100001], sz = 1;
int st[100001], parents[100001], family[100001][20], level[100001];
vector<list<node>> adj(100001);
vector<ll> tree(400000), idx(100001), segs(100001);
void maketree(int cur, int bef) {
	level[cur] = level[bef] + 1;
	for (node i : adj[cur]) {
		if (bef^i.e) maketree(i.e, cur), heavy[cur] += heavy[i.e], w[i.e] = i.w;
	}
	parents[cur] = bef;
	family[cur][0] = bef;
	heavy[cur]++;
}
void HLD(int cur, int bef) {
	int high = 0;
	for (node i : adj[cur])
		if (bef^i.e && heavy[i.e] > heavy[high])
			high = i.e;
	for (node i : adj[cur])
		if (bef^i.e && i.e != high)
			st[i.e] = i.e, HLD(i.e, cur);
	if (high) st[high] = st[cur], HLD(high, cur);
	segs[sz] = cur;
	idx[cur] = sz++;

}
int LCA(int a, int b) {
	if (level[a] < level[b]) swap(a, b);
	int i;
	while (level[a] != level[b]) {
		i = -1;
		while (level[family[a][i + 1]] >= level[b])
			++i;
		a = family[a][i];
	}
	while (a != b) {
		i = 0;
		while (family[a][i + 1] != family[b][i + 1])
			++i;
		a = family[a][i], b = family[b][i];
	}
	return a;
}
ll make_tree(int l, int r, int idx) {
	if (l == r) return tree[idx] = w[segs[l]];
	return tree[idx] = make_tree(l, (l + r) / 2, idx * 2) + make_tree((l + r) / 2 + 1, r, idx * 2 + 1);
}
ll small_query(int s, int e, int l, int r, int cur) {
	if (r < s || l > e)
		return 0;
	if (l >= s && r <= e)
		return tree[cur];
	return small_query(s, e, l, (l + r) / 2, cur * 2) + small_query(s, e, (l + r) / 2 + 1, r, cur * 2 + 1);
}
ll query(int s, int e) {
	ll ret = 0;
	while (st[s] != st[e]) {
		if (heavy[st[s]] > heavy[st[e]]) swap(s, e);
		ret += small_query(idx[s], idx[st[s]], 1, sz - 1, 1);
		s = parents[st[s]];
	}
	if (heavy[s] > heavy[e]) swap(s, e);
	ret += small_query(idx[s], idx[e] - 1, 1, sz - 1, 1);
	return ret;
}
int query2(int s, int e, int k) {
	int lca = LCA(s, e);
	if (level[s] - level[lca] + 1 > k) {
		while (true) {
			int d = level[s] - level[st[s]] + 1;
			if (d >= k) return segs[idx[s] + k - 1];
			else k -= d, s = parents[st[s]];
		}
	}
	else {
		k -= (level[s] - level[lca] + 1);
		k = (level[e] - level[lca] + 1) - k;
		while (true) {
			int d = level[e] - level[st[e]] + 1;
			if (d >= k) return segs[idx[e] + k - 1];
			else k -= d, e = parents[st[e]];
		}
	}
}
void build() {
	st[0] = st[1] = parents[0] = parents[1] = 1;
	maketree(1, 0);
	HLD(1, 0);
	make_tree(1, sz - 1, 1);
	for (int i = 1; i < 20; i++)
		for (int j = 1; j <= n; j++)
			family[j][i] = family[family[j][i - 1]][i - 1];
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d%d%lld", u + i, v + i, w + i);
		adj[v[i]].push_back({ u[i], w[i] });
		adj[u[i]].push_back({ v[i], w[i] });
	}
	build();
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int a, b, c, k;
		scanf("%d%d%d", &a, &b, &c);
		if (a == 1)
			printf("%lld\n", query(b, c));
		else
			scanf("%d", &k), printf("%d\n", query2(b, c, k));
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