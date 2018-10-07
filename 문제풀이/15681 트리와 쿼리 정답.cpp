#include <iostream>
#include <vector>
using namespace std;
int n, r, q, u, v;
vector<int> h;
vector<vector<int>> adj;
void build(int cur, int bef) {
	for (int i : adj[cur])
		if (bef^i) 
			build(i, cur), h[cur]+=h[i];
	h[cur]++;
}
int main()
{
	scanf("%d%d%d", &n, &r, &q);
	adj.resize(n + 1);
	h.assign(n + 1, 0);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &u, &v);
		adj[u].push_back(v), adj[v].push_back(u);
	}
	build(r, 0);
	for (int i = 0; i < q; i++) {
		scanf("%d", &u);
		printf("%d\n", h[u]);
	}
	return 0;
}
/*
����
������ ����ġ�� ���⼺�� ���� ������ ��Ʈ �ִ� Ʈ���� �־����� ��, �Ʒ��� ������ ���غ����� ����.
���� U�� ��Ʈ�� �ϴ� ����Ʈ���� ���� ������ ���� ����Ѵ�.
���� �� ������ �ذ��ϴ� ���� ������� �ִٸ�, �ϴ��� ��Ʈ�� ÷���� ������ ��������.

�Է�
Ʈ���� ������ �� N�� ��Ʈ�� ��ȣ R, ������ �� Q�� �־�����. (2 �� N �� 105, 1 �� R �� N, 1 �� Q �� 105)
�̾� N-1�ٿ� ����, U V�� ���·� Ʈ���� ���� ������ ������ �־�����. (1 �� U, V �� N, U �� V)
�̴� U�� V�� �� �������� �ϴ� ������ Ʈ���� ������ �ǹ��Ѵ�.
�̾� Q�ٿ� ����, ������ ������ U�� �ϳ��� �־�����. (1 �� U �� N)
�Է����� �־����� Ʈ���� �׻� �ùٸ� Ʈ������ ����ȴ�.

���
Q�ٿ� ���� �� ������ ���� ���� �ϳ��� ����Ѵ�.
*/