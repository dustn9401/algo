#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#define MAXN 30001
using namespace std;
typedef pair<int, int> ii;
typedef struct {
	char str[20];
	int a, b;
}qry;
int n, k, sz = 1;
vector<qry> v;
vector<vector<int>> adj(MAXN);
vector<int> tree(MAXN * 4), w(MAXN), roots(MAXN), r(MAXN, 0);
vector<int> segs(MAXN), hv(MAXN, 0), par(MAXN, 1), st(MAXN, 1), idx(MAXN, 0);
long time_s, time_e;
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
	else if (l >= s && r <= e) return tree[i];
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
void build() {
	for (int i = 1; i <= n; i++)
		calc(i, i), HLD(i, i);
	init(1, sz - 1, 1);
}
void set_init() {
	for (int i = 1; i <= n; i++)
		roots[i] = i;
	r.assign(MAXN, 0);
}
int find(int idx) {
	if (idx == roots[idx]) return idx;
	return roots[idx] = find(roots[idx]);
}
void merge(int u, int v) {
	u = find(u), v = find(v);
	if (u == v)return;
	if (r[u] > r[v]) swap(u, v);
	roots[u] = v;
	if (r[u] == r[v]) ++r[v];
}
int main()
{
	FILE *fp = fopen("C:\\input2927.txt", "r");
	fscanf(fp, "%d", &n);
	//scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		//scanf("%d", &w[i]);
		fscanf(fp, "%d", &w[i]);
	//scanf("%d", &k);
	fscanf(fp, "%d", &k);
	v.resize(k);
	set_init();
	for (int i = 0; i < k; i++) {
		//scanf("%s%d%d", v[i].str, &v[i].a, &v[i].b);
		fscanf(fp, "%s%d%d", v[i].str, &v[i].a, &v[i].b);
		if (v[i].str[0] == 'b') {
			if (find(v[i].a) ^ find(v[i].b)) {
				adj[v[i].a].push_back(v[i].b);
				adj[v[i].b].push_back(v[i].a);
				merge(v[i].a, v[i].b);
			}
		}
	}
	fclose(fp);
	build();
	time_s = clock();
	fp = fopen("C:\\output2927.txt", "r");
	set_init();
	for (int i = 0; i < k; i++) {
		char buf[80];
		if (v[i].str[0] == 'p') {
			update(1, sz - 1, idx[v[i].a], v[i].b, 1);
		}
		if (v[i].str[0] == 'b') {
			fgets(buf, 80, fp);
			if (find(v[i].a) ^ find(v[i].b)) {
				//if (buf[0] == 'y') printf("O");
				//else printf("X");
				merge(v[i].a, v[i].b);
			}
			else {
				//if (buf[0] == 'n') printf("O");
				//else printf("X");
			}
		}
		if (v[i].str[0] == 'e') {
			fgets(buf, 80, fp);
			if (find(v[i].a) ^ find(v[i].b)) {
				//if (buf[0] == 'i') printf("O");
				//else printf("X");
			}
			else {
				query(v[i].a, v[i].b);
				//string ans = to_string(query(v[i].a, v[i].b));
				//if (strncmp(buf, ans.c_str(), ans.length()) == 0) printf("O");
				//else printf("X");
			}
		}
	}
	time_e = clock();
	printf("time = %.3lf\n", (time_e-time_s) / (double)CLOCKS_PER_SEC);
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