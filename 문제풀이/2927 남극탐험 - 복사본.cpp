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