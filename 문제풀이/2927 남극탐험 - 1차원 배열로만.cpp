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

문제
상근이는 "얼음을 꿈꾸다" 여행사의 사장이다. 이 여행사는 남극 근처의 섬 N개를 구매해 당일치기 여행을 제공하고 있다.
관광객들에게 가장 인기 있는 동물은 황제 펭귄으로 섬에서 쉽게 찾을 수 있다.
여행사는 점점 인기를 얻게 되었고, 이제 보트를 이용하는 것이 효율적이지 않은 상황까지 이르렀다.
상근이는 섬 사이에 다리를 건설해 관광객을 버스로 이동시키려고 한다.
상근이는 컴퓨터 프로그램을 이용해서 다리를 건설하는 과정을 관리하려고 한다.
섬은 1번부터 N번까지 번호가 매겨져 있다. 가장 처음에는 아무 다리도 없으며, 각 섬에 펭귄이 몇 마리 살고있는지는 모두 알고있다.
펭귄의 수는 변할 수 있다. 하지만, 항상 0보다 크거나 같고, 1000보다 작거나 같다.
상근이의 프로그램은 다음과 같은 세 가지 명령을 수행할 수 있어야 한다.

"bridge A B" - 섬 A와 B사이에 다리를 건설하는 명령이다. (A와 B는 다르다)
이전까지 지어진 다리를 이용해서 이동할 수 없는 경우에만 다리를 지어야 한다.
다리를 지어야 하면 "yes", 지을 필요가 없이 이미 이동할 수 있으면 "no"를 출력한다.
"penguins A X" - 섬 A에 살고있는 펭귄의 수를 다시 세보니 X마리가 되었다는 명령이다. 아무것도 출력할 필요가 없다.
"excursion A B" - 관광객들이 섬 A에서 시작해 B에서 끝나는 여행 경로를 이용하는 명령이다.
A에서 B로 갈 수 있는 경우에는 이동하는 섬에 있는 모든 펭귄의 수를 구해 출력한다. (A와 B 포함)
이동할 수 없는 경우에는 "impossible"를 출력한다.
상근이의 프로그램을 작성하시오.

입력
첫째 줄에 섬의 수 N (1 ≤ N ≤ 30,000)이 주어진다.
둘째 줄에는 각 섬에 있는 펭귄의 수가 주어진다.
셋째 줄에는 명령의 개수 Q (1 ≤ Q ≤ 300,000)가 주어진다.
다음 Q개 줄에는 문제에서 주어진 명령 중 하나가 주어진다.

출력
"bridge"나 "excursion" 명령이 주어질 때 마다 출력한다.
*/