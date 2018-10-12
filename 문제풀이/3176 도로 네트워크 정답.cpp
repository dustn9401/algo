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
����
N���� ���ÿ� �� ���ø� �����ϴ� N-1���� ���η� �̷���� ���� ��Ʈ��ũ�� �ִ�.
��� ������ �ֿ��� �� ���ø� �����ϴ� ������ ��ΰ� �ְ�, �� ������ ���̴� �Է����� �־�����.
�� K���� ���� ���� �־�����. �̶�, �� ���ø� �����ϴ� ��� �󿡼� ���� ª�� ������ ���̿� ���� �� ������ ���̸� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù° �ٿ� N�� �־�����. (2 �� N �� 100,000)

���� N-1�� �ٿ��� ���θ� ��Ÿ���� �� ���� A, B, C�� �־�����.
A�� B���̿� ���̰� C�� ���ΰ� �ִٴ� ���̴�.
������ ���̴� 1,000,000���� �۰ų� ���� ���� �����̴�.

���� �ٿ��� K�� �־�����. (1 �� K �� 100,000)
���� K�� �ٿ��� ���� �ٸ� �� �ڿ��� D�� E�� �־�����.
D�� E�� �����ϴ� ��ο��� ���� ª�� ������ ���̿� ���� �� ������ ���̸� ���ؼ� ����ϸ� �ȴ�.

���
�� K�� �ٿ� D�� E�� �����ϴ� ��ο��� ���� ª�� ������ ���̿� ���� �� ������ ���̸� ����Ѵ�.
*/