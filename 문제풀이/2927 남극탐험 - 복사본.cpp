#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#define MAXN 30001
using namespace std;
int qa[MAXN], qb[MAXN], parent[MAXN], num[MAXN];
char qc[MAXN];
int n, k, sz = 1;
vector<vector<int>> adj(MAXN);
vector<int> tree(MAXN * 4), w(MAXN);
vector<int> segs(MAXN), hv(MAXN, 0), par(MAXN, 1), st(MAXN, 1), idx(MAXN, 0);
void calc(int c, int b) {
	if (hv[c]) return;
	for (int i : adj[c])
		if (i^b) calc(i, c), hv[c] += hv[i];
	par[c] = b, hv[c]++;
}
void HLD(int c, int b) {
	if (idx[c]) return;
	int hi = 0;
	for (int i : adj[c])
		if (i^b && hv[hi] < hv[i]) hi = i;
	for (int i : adj[c])
		if (i^b && i^hi) st[i] = i, HLD(i, c);
	if (hi) st[hi] = st[c], HLD(hi, c);
	segs[sz] = c;
	idx[c] = sz++;
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
		ret += small_query(1, sz - 1, idx[s], idx[st[s]], 1);
		s = par[st[s]];
	}
	if (hv[s] > hv[e]) swap(s, e);
	return ret += small_query(1, sz - 1, idx[s], idx[e], 1);
}
int find(int vertex) {
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p); s = i;
	for (i = vertex; (p = parent[i]) >= 0; i = p) parent[i] = s;
	return s;
}
void merge(int s1, int s2) {
	if (num[s1] > num[s2])
		parent[s1] = s2, num[s2] += num[s1];
	else
		parent[s2] = s1, num[s1] += num[s2];
}
void build() {
	for (int i = 1; i <= n; i++)
		calc(i, i), HLD(i, i);
	init(1, sz - 1, 1);
}
int main()
{
	FILE *fp = fopen("C:\\input2927.txt", "r");
	fscanf(fp, "%d", &n);
	memset(parent, -1, sizeof(parent));
	memset(num, -1, sizeof(num));

	for (int i = 1; i <= n; i++)
		fscanf(fp, "%d", &w[i]);
	fscanf(fp, "%d", &k);
	char buf[20];
	for (int i = 0; i < k; i++) {
		fscanf(fp, "%s%d%d", buf, qa + i, qb + i);
		qc[i] = buf[0];
		if (qc[i] == 'b') {
			if (find(qa[i]) ^ find(qb[i])) {
				adj[qa[i]].push_back(qb[i]);
				adj[qb[i]].push_back(qa[i]);
				merge(qa[i], qb[i]);
			}
		}
	}
	fclose(fp);
	build();
	memset(parent, -1, sizeof(parent));
	memset(num, -1, sizeof(num));
	fp = fopen("C:\\output2927.txt", "r");
	for (int i = 0; i < k; i++) {
		if (qc[i] == 'p') {
			update(1, sz - 1, idx[qa[i]], qb[i], 1);
		}
		else if (qc[i] == 'b') {
			fscanf(fp, "%s", buf);
			if (find(qa[i]) ^ find(qb[i])) {
				merge(qa[i], qb[i]);
				if (buf[0] == 'y') printf("O");
				else printf("X");
			}
			else {
				if (buf[0] == 'n') printf("O");
				else printf("X");
			}
		}
		else {
			if (find(qa[i]) ^ find(qb[i])) {
				fscanf(fp, "%s", buf);
				if (buf[0] == 'i') printf("O");
				else printf("X");
			}
			else {
				int res;
				fscanf(fp, "%d", &res);
				if (query(qa[i], qb[i]) == res) printf("O");
				else printf("X");
			}
		}
	}
	fclose(fp);
	return 0;
}
/*
5
4 2 4 5 6
9
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