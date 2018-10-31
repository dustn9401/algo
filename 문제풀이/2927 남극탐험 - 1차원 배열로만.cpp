#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#define MAXN 30001
#define MAXK 300000
using namespace std;
int n, k, sz = 1;
vector<vector<int>> adj(MAXN);
char qc[MAXK];
int qa[MAXK], qb[MAXK], set_par[MAXN], set_hv[MAXN], tree[MAXN * 4], w[MAXN], segs[MAXN],
hv[MAXN], idx[MAXN], tree_root_idx[MAXN], par[MAXN], st[MAXN], ed[MAXN];
void calc(int c, int b) {
	for (int i : adj[c])
		if (i^b) calc(i, c), hv[c] += hv[i];
	par[c] = b, hv[c]++;
}
void HLD(int c, int b) {
	int hi = 0;
	for (int i : adj[c])
		if (i^b && hv[hi] < hv[i]) hi = i;
	for (int i : adj[c])
		if (i^b && i^hi) st[i] = i, HLD(i, c);
	if (hi) st[hi] = st[c], HLD(hi, c), ed[c] = ed[hi];
	else ed[c] = c;
	segs[sz] = c, idx[c] = sz++;
}
int init(int l, int r, int i) {
	if (l == r) return tree[i] = w[segs[l]];
	return tree[i] = init(l, (l + r) / 2, i * 2) + init((l + r) / 2 + 1, r, i * 2 + 1);
}
int update(int l, int r, int t, int d, int i) {
	if (l > t || r < t) return tree[i];
	if (l == r) return tree[i] = d;
	return tree[i] = update(l, (l + r) / 2, t, d, i * 2) + update((l + r) / 2 + 1, r, t, d, i * 2 + 1);
}
int small_query(int l, int r, int s, int e, int i) {
	if (l > e || r < s) return 0;
	if (l >= s && r <= e) return tree[i];
	return small_query(l, (l + r) / 2, s, e, i * 2) + small_query((l + r) / 2 + 1, r, s, e, i * 2 + 1);
}
int query(int s, int e) {
	int ret = 0;
	while (st[s] ^ st[e]) {
		if (hv[st[s]] > hv[st[e]]) swap(s, e);
		ret += small_query(idx[ed[s]], idx[st[s]], idx[s], idx[st[s]], tree_root_idx[s]);
		s = par[st[s]];
	}
	if (hv[s] > hv[e]) swap(s, e);
	return ret += small_query(idx[ed[s]], idx[st[s]], idx[s], idx[e], tree_root_idx[s]);
}
void set_init() {
	for (int i = 0; i <= n; i++)
		set_par[i] = i, set_hv[i] = 1;
}
int find(int vtx) {
	if (vtx == set_par[vtx]) return vtx;
	return set_par[vtx] = find(set_par[vtx]);
}
void merge(int s1, int s2) {
	s1 = find(s1), s2 = find(s2);
	if (s1 == s2) return;
	if (set_hv[s1] > set_hv[s2]) swap(s1, s2);
	set_par[s1] = s2;
	if (set_hv[s1] == set_hv[s2]) set_hv[s2]++;
}
void build() {
	for (int i = 1; i <= n; i++)
		if (!idx[i]) st[i] = par[i] = i, calc(i, i), HLD(i, i);
	int s = 1, e = idx[st[segs[s]]], rt = 1;
	while (true) {
		for (int i = s; i <= e; i++) tree_root_idx[segs[i]] = rt;
		init(s, e, rt);
		rt += (e - s) * 2 + 1, s = e + 1;
		if (s < sz) e = idx[st[segs[s]]];
		else break;
	}
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", w + i);
	scanf("%d", &k);
	char buf[10];
	set_init();
	for (int i = 0; i < k; i++) {
		scanf("%s%d%d", buf, qa + i, qb + i);
		qc[i] = buf[0];
		if (qc[i] == 'b') {
			if (find(qa[i]) ^ find(qb[i])) {
				adj[qa[i]].push_back(qb[i]);
				adj[qb[i]].push_back(qa[i]);
				merge(qa[i], qb[i]);
			}}}

	build();
	set_init();
	for (int i = 0; i < k; i++) {
		if (qc[i] == 'p') {
			update(idx[ed[qa[i]]], idx[st[qa[i]]], idx[qa[i]], qb[i], tree_root_idx[qa[i]]);
		}
		else if (qc[i] == 'b') {
			if (find(qa[i]) ^ find(qb[i]))
				puts("yes"), merge(qa[i], qb[i]);
			else
				puts("no");
		}
		else {
			if (find(qa[i]) ^ find(qb[i]))
				puts("impossible");
			else
				printf("%d\n", query(qa[i], qb[i]));
		}
	}
	return 0;
}
/*
5
4 2 4 5 6
11
excursion 1 1
excursion 1 2
bridge 1 2
excursion 1 2
bridge 3 4
bridge 3 5
excursion 4 5
excursion 2 4
excursion 2 5

����
����̴� "������ �޲ٴ�" ������� �����̴�. �� ������ ���� ��ó�� �� N���� ������ ����ġ�� ������ �����ϰ� �ִ�.
�������鿡�� ���� �α� �ִ� ������ Ȳ�� ������� ������ ���� ã�� �� �ִ�.
������ ���� �α⸦ ��� �Ǿ���, ���� ��Ʈ�� �̿��ϴ� ���� ȿ�������� ���� ��Ȳ���� �̸�����.
����̴� �� ���̿� �ٸ��� �Ǽ��� �������� ������ �̵���Ű���� �Ѵ�.
����̴� ��ǻ�� ���α׷��� �̿��ؼ� �ٸ��� �Ǽ��ϴ� ������ �����Ϸ��� �Ѵ�.
���� 1������ N������ ��ȣ�� �Ű��� �ִ�. ���� ó������ �ƹ� �ٸ��� ������, �� ���� ����� �� ���� ����ִ����� ��� �˰��ִ�.
����� ���� ���� �� �ִ�. ������, �׻� 0���� ũ�ų� ����, 1000���� �۰ų� ����.
������� ���α׷��� ������ ���� �� ���� ����� ������ �� �־�� �Ѵ�.

"bridge A B" - �� A�� B���̿� �ٸ��� �Ǽ��ϴ� ����̴�. (A�� B�� �ٸ���)
�������� ������ �ٸ��� �̿��ؼ� �̵��� �� ���� ��쿡�� �ٸ��� ����� �Ѵ�.
�ٸ��� ����� �ϸ� "yes", ���� �ʿ䰡 ���� �̹� �̵��� �� ������ "no"�� ����Ѵ�.
"penguins A X" - �� A�� ����ִ� ����� ���� �ٽ� ������ X������ �Ǿ��ٴ� ����̴�. �ƹ��͵� ����� �ʿ䰡 ����.
"excursion A B" - ���������� �� A���� ������ B���� ������ ���� ��θ� �̿��ϴ� ����̴�.
A���� B�� �� �� �ִ� ��쿡�� �̵��ϴ� ���� �ִ� ��� ����� ���� ���� ����Ѵ�. (A�� B ����)
�̵��� �� ���� ��쿡�� "impossible"�� ����Ѵ�.
������� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù° �ٿ� ���� �� N (1 �� N �� 30,000)�� �־�����.
��° �ٿ��� �� ���� �ִ� ����� ���� �־�����.
��° �ٿ��� ����� ���� Q (1 �� Q �� 300,000)�� �־�����.
���� Q�� �ٿ��� �������� �־��� ��� �� �ϳ��� �־�����.

���
"bridge"�� "excursion" ����� �־��� �� ���� ����Ѵ�.
*/