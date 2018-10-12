#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> ii;
typedef struct {
	int e, w;
}vt;
int n, k, sz = 1;
vector<vector<vt>> adj(100001);
vector<ii> tree(400000);
vector<int> segs(100001), hv(100001, 0), par(100001, 1), st(100001, 1), idx(100001), w(100001);
void calc(int c, int b) {
	for (vt i : adj[c])
		if (i.e^b) calc(i.e, c), hv[c] += hv[i.e], w[i.e] = i.w;
	par[c] = b, hv[c]++;
}
void HLD(int c, int b) {
	int hi = 0;
	for (vt i : adj[c])
		if (i.e^b && hv[hi] < hv[i.e]) hi = i.e;
	for (vt i : adj[c])
		if (i.e^b && i.e^hi) st[i.e] = i.e, HLD(i.e, c);
	if (hi) st[hi] = st[c], HLD(hi, c);
	segs[sz] = c;
	idx[c] = sz++;
}
ii minmax(ii a, ii b) {
	return { max(a.first, b.first), min(a.second, b.second) };
}
ii init(int l, int r, int i) {
	if (l == r) return tree[i] = { w[segs[l]], w[segs[l]] };
	return tree[i] = minmax(init(l, (l + r) / 2, i * 2), init((l + r) / 2 + 1, r, i * 2 + 1));
}
ii small_query(int l, int r, int s, int e, int i) {
	if (l > e || r < s) return { 0,1000000 };
	else if (l >= s && r <= e) return tree[i];
	return minmax(small_query(l, (l + r) / 2, s, e, i * 2), small_query((l + r) / 2 + 1, r, s, e, i * 2 + 1));
}
ii query(int s, int e) {
	ii ret = { 0,1000000 };
	while (st[s] ^ st[e]) {
		if (hv[st[s]] > hv[st[e]]) swap(s, e);
		ret = minmax(ret, small_query(1, sz - 1, idx[s], idx[st[s]], 1));
		s = par[st[s]];
	}
	if (hv[s] > hv[e]) swap(s, e);
	return ret = minmax(ret, small_query(1, sz - 1, idx[s], idx[e] - 1, 1));
}
void build() {
	calc(1, 0);
	HLD(1, 0);
	init(1, sz - 1, 1);
}
int main()
{
	scanf("%d", &n);
	int a, b, c;
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", &a, &b, &c);
		adj[a].push_back({ b,c });
		adj[b].push_back({ a,c });
	}
	build();
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		scanf("%d%d", &a, &b);
		ii res = query(a, b);
		printf("%d %d\n", res.second, res.first);
	}
	return 0;
}
/*
문제
N개의 도시와 그 도시를 연결하는 N-1개의 도로로 이루어진 도로 네트워크가 있다.
모든 도시의 쌍에는 그 도시를 연결하는 유일한 경로가 있고, 각 도로의 길이는 입력으로 주어진다.
총 K개의 도시 쌍이 주어진다. 이때, 두 도시를 연결하는 경로 상에서 가장 짧은 도로의 길이와 가장 긴 도로의 길이를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N이 주어진다. (2 ≤ N ≤ 100,000)

다음 N-1개 줄에는 도로를 나타내는 세 정수 A, B, C가 주어진다.
A와 B사이에 길이가 C인 도로가 있다는 뜻이다.
도로의 길이는 1,000,000보다 작거나 같은 양의 정수이다.

다음 줄에는 K가 주어진다. (1 ≤ K ≤ 100,000)
다음 K개 줄에는 서로 다른 두 자연수 D와 E가 주어진다.
D와 E를 연결하는 경로에서 가장 짧은 도로의 길이와 가장 긴 도로의 길이를 구해서 출력하면 된다.

출력
총 K개 줄에 D와 E를 연결하는 경로에서 가장 짧은 도로의 길이와 가장 긴 도로의 길이를 출력한다.
*/