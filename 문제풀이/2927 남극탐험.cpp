#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 30001
#define MAXK 300000
using namespace std;

int n, k, sz;
char qc[MAXK];
int qa[MAXK], qb[MAXK], set_par[MAXN], set_hv[MAXN], heavy[MAXN], tree_idx[MAXN], idx[MAXN], weights[MAXN], start[MAXN], par[MAXN];
vector<vector<int>> segtrees, divtrees, adj;
void maketree(int cur, int bef) {
	for (int i : adj[cur])
		if (bef^i) maketree(i, cur), heavy[cur] += heavy[i];
	par[cur] = bef;
	heavy[cur]++;
}
void HLD(int cur, int bef, int tidx) {
	int high = 0;
	for (int i : adj[cur])
		if (i^bef && heavy[i] > heavy[high])
			high = i;
	for (int i : adj[cur])
		if (i^bef && i^high) start[i] = i, HLD(i, cur, sz++);
	if (high) start[high] = start[cur], HLD(high, cur, tidx);
	idx[cur] = divtrees[tidx].size();
	tree_idx[cur] = tidx;
	divtrees[tidx].push_back(cur);
}
int seg(int l, int r, int idx, int tree_idx) {
	if (l == r)
		return segtrees[tree_idx][idx] = weights[divtrees[tree_idx][l]];
	return segtrees[tree_idx][idx] = seg(l, (l + r) / 2, idx * 2, tree_idx) + seg((l + r) / 2 + 1, r, idx * 2 + 1, tree_idx);
}
void make_segtree() {
	for (int i = 0; i < sz; i++) {
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
	return segtrees[tree_idx][cur] =
		update(st, (st + ed) / 2, idx, change, cur * 2, tree_idx) + update((st + ed) / 2 + 1, ed, idx, change, cur * 2 + 1, tree_idx);
}
int small_query(int st, int ed, int l, int r, int cur, int tree_idx) {
	if (r < st || l > ed)
		return 0;
	if (l >= st && r <= ed)
		return segtrees[tree_idx][cur];
	return small_query(st, ed, l, (l + r) / 2, cur * 2, tree_idx) + small_query(st, ed, (l + r) / 2 + 1, r, cur * 2 + 1, tree_idx);
}
int query(int st, int ed) {
	int ret = 0;
	while (start[st] ^ start[ed]) {
		if (heavy[start[st]] > heavy[start[ed]]) swap(st, ed);
		ret += small_query(idx[st], idx[start[st]], 1, idx[start[st]], 1, tree_idx[st]);
		st = par[start[st]];
	}
	if (heavy[st] > heavy[ed]) swap(st, ed);
	return ret + small_query(idx[st], idx[ed], 1, divtrees[tree_idx[st]].size() - 1, 1, tree_idx[st]);
}
void build() {
	for (int i = 1; i <= n; i++)
		if (!idx[i]) start[i] = par[i] = i, maketree(i, i), HLD(i, i, sz++);
	make_segtree();
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
int main()
{
	scanf("%d", &n);
	adj.resize(n + 1), segtrees.resize(n + 1), divtrees.assign(n + 1, { 0 });
	for (int i = 1; i <= n; i++)
		scanf("%d", weights + i);
	scanf("%d", &k);
	set_init();
	char buf[10];
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
			update(1, divtrees[tree_idx[qa[i]]].size() - 1, idx[qa[i]], qb[i], 1, tree_idx[qa[i]]);
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