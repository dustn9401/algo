#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
int n, m, divtree_size = 1;
int starts[100001], parents[100001], idx[100001], divtrees[100001], lower, upper;
long st, ed;
vector<int> u(100001), v(100001), w(100001), level(100001), heavy(100001), cw(100001), sw, cwi(100001);
vector<vector<int>> adj(100001), segtree(400000);
void compress() {
	sort(sw.begin(), sw.end());
	for (int i = 1; i <= n; i++) {
		cw[i] = distance(sw.begin(), lower_bound(sw.begin(), sw.end(), w[i]));
		cwi[cw[i]] = i;
	}
}
void tree_init(int s, int e, int i) {
	if (s == e) {
		segtree[i].push_back(cw[divtrees[s]]);
		return;
	}
	int l = i * 2, r = i * 2 + 1;
	tree_init(s, (s + e) / 2, l);
	tree_init((s + e) / 2 + 1, e, r);
	auto lt = segtree[l].begin(), rt = segtree[r].begin(), le = segtree[l].end(), re = segtree[r].end();
	while (lt != le || rt != re) {
		if (rt == re)
			segtree[i].push_back(*lt), lt++;
		else if (lt == le)
			segtree[i].push_back(*rt), rt++;
		else {
			if (*lt < *rt)
				segtree[i].push_back(*lt), lt++;
			else
				segtree[i].push_back(*rt), rt++;
		}
	}
}
void maketree(int cur, int bef) {
	level[cur] = level[bef] + 1;
	for (int i : adj[cur])
		if(i^bef) maketree(i, cur), heavy[cur] += heavy[i];
	parents[cur] = bef;
	heavy[cur]++;
}
void HLD(int cur, int bef) {
	int high = 0;
	for (int i : adj[cur])
		if (i^bef && heavy[i] > heavy[high])
			high = i;
	for (int i : adj[cur])
		if (i^bef && i^high)
			starts[i] = i, HLD(i, cur);
	if (high)
		starts[high] = starts[cur], HLD(high, cur);
	divtrees[divtree_size] = cur;
	idx[cur] = divtree_size++;
}
void very_small_query(int s, int e, int l, int r, int idx, int x)
{
	if (r < s || e < l)
		return;
	if (l >= s && r <= e) {
		lower += distance(segtree[idx].begin(), lower_bound(segtree[idx].begin(), segtree[idx].end(), x));
		upper += distance(segtree[idx].begin(), upper_bound(segtree[idx].begin(), segtree[idx].end(), x));
		return;
	}
	very_small_query(s, e, l, (l+r)/2, idx * 2, x);
	very_small_query(s, e, (l+r)/2+1, r, idx * 2 + 1, x);
}
void small_query(int s, int e, int k) {
	while (starts[s]^starts[e]) {
		if (heavy[starts[s]] > heavy[starts[e]])
			swap(s, e);
		very_small_query(idx[s], idx[starts[s]], 1, divtree_size - 1, 1, k);
		s = parents[starts[s]];
	}
	if (heavy[s] > heavy[e]) swap(s, e);
	very_small_query(idx[s], idx[e], 1, divtree_size - 1, 1, k);
}
int query(int s, int e, int k) {
	long long ret, lo = 0, hi = n;
	while (true) {
		lower = upper = 0;
		if (lo + hi < 0)
			ret = (lo + hi - 1) / 2;
		else
			ret = (lo + hi) / 2;
		small_query(s, e, ret);
		if (lower < k && upper >= k)
			break;
		lower < k ? lo = ret : hi = ret;
	}
	return ret;
}
void build() {
	compress();
	maketree(1, 0);
	HLD(1, 0);
	tree_init(1, divtree_size - 1, 1);
}
int main()
{
	scanf("%d%d", &n, &m);
	starts[0] = starts[1] = parents[0] = parents[1] = 1;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &w[i]);
		sw.push_back(w[i]);
	}
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &u[i], &v[i]);
		adj[v[i]].push_back(u[i]);
		adj[u[i]].push_back(v[i]);
	}
	build();
	for (int i = 0; i < m; i++) {
		int x, y, k;
		scanf("%d%d%d", &x, &y, &k);
		printf("%d\n", w[cwi[query(x, y, k)]]);
	}
	return 0;
}
/*
13 100
1 2 3 4 5 6 7 8 9 10 11 12 13
1 2
1 11
2 3
2 7
11 12
11 13
3 4
3 5
7 8
7 9
5 6
8 10
����
1������ N������ ��ȣ�� �ٿ��� N���� ������ N-1���� �������� ������ Ʈ���� �ִ�.
Ʈ���� �� �������� ����ġ�� �ִ�. �̶� M���� ������ ���� ������ ������ �����ؾ� �Ѵ�.
���� X Y K : ���� X�� Y�� �մ� ��� �󿡼� K��°�� ���� ����ġ�� ����Ѵ�.

�Է�
ù° �ٿ��� �� ���� ���� ���� N�� M�� �־�����. (1 �� N, M �� 100,000)
��° �ٿ��� �� ������ ����ġ�� ��Ÿ���� N���� ������ �־�����. i��° ������ i�� ������ ����ġ�̴�. 
�� ����ġ�� ��� ���� �ٸ� �����̸� int �����̴�.
���� N-1���� �� �ٿ��� Ʈ���� ���� (X, Y)�� ��Ÿ���� �� ���� X�� Y�� �־�����.
���� M���� �� �ٿ��� ������ ��Ÿ���� �� ���� ���� X Y K�� �־�����. X, Y�� 1 �̻��̰� N �����̴�.
K�� 1 �̻��̰� X�� Y�� �մ� ��� ���� ������ ���� �����̴�. X�� Y�� ���ٸ�, ��� ���� ������ ������ 1���� �����Ѵ�.

���
M���� �ٿ� ���ļ� �� ���꿡 �ش��ϴ� ���� ����Ѵ�.
*/