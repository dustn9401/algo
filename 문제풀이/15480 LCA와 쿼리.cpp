#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
int n, m, u[100001], v[100001], parent[100001][20], level[100001];
vector<list<int>> adj(100001);
void maketree(int cur, int bef) {
	level[cur] = level[bef] + 1;
	for (int i : adj[cur])
		if (bef ^ i) 
			maketree(i, cur);
	parent[cur][0] = bef;
}
void preproc() {
	for (int j = 1; j < 20; j++)
		for (int i = 1; i <= n; i++)
			parent[i][j] = parent[parent[i][j - 1]][j - 1];
}
int LCA(int a, int b) {
	if(level[a] < level[b]) 
		swap(a, b);
	int i;
	while (level[a] != level[b]) {
		i = -1;
		while (level[parent[a][i + 1]] >= level[b])
			++i;
		a = parent[a][i];
	}
	while (a != b) {
		i = 0;
		while (parent[a][i + 1] != parent[b][i + 1])
			++i;
		a = parent[a][i], b = parent[b][i];
	}
	return a;
}
int query(int a, int b, int c) {
	int ret = LCA(a, b), lca2 = LCA(b, c), lca3 = LCA(c, a);
	if (level[ret] < level[lca2]) ret = lca2;
	if (level[ret] < level[lca3]) ret = lca3;
	return ret;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", u + i, v + i);
		adj[v[i]].push_back(u[i]), adj[u[i]].push_back(v[i]);
	}
	maketree(1, 0);
	preproc();
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		printf("%d\n", query(a,b,c));
	}
	return 0;
}
/*
����
N���� �������� �̷���� �ִ� Ʈ�� T�� �־����� ��, ���� ������ �����ϴ� ���α׷��� �ۼ��Ͻÿ�.
r u v: T�� ��Ʈ�� r�̶�� ���� ��, u�� v�� LCA�� ����Ѵ�.

�Է�
ù° �ٿ� ������ ���� N(1 �� N �� 100,000)�� �־�����.
��° �ٺ��� N-1���� �ٿ��� Ʈ�� T�� ���� ���� u�� v�� �־�����.
u�� v�� Ʈ���� ������ ��Ÿ���� �� �����̴�.

���� �ٿ��� ������ ���� M(1 �� M �� 100,000)�� �־�����.
���� M���� �ٿ��� ������ ��Ÿ���� r, u, v�� �־�����.

���
������ �������� �� �ٿ� �ϳ��� ����� ����Ѵ�.
*/