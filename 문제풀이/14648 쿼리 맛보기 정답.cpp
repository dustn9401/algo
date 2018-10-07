#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, q, a, b, c, d;
vector<ll> tree, arr;
ll build(int l, int r, int idx) {
	if (l == r)
		return tree[idx] = arr[l];
	return tree[idx] = build(l, (l + r) / 2, idx * 2) + build((l + r) / 2 + 1, r, idx * 2 + 1);
}
ll update(int l, int r, int t, int idx, ll c) {
	if (l > t || r < t)
		return tree[idx];
	if (l == r) 
		return tree[idx] = c;
	return tree[idx] = update(l, (l + r) / 2, t, idx * 2, c) + update((l + r) / 2 + 1, r, t, idx * 2 + 1, c);
}
ll query(int l, int r, int s, int e, int idx) {
	if (l > e || r < s)
		return 0;
	if (l >= s && r <= e)
		return tree[idx];
	return query(l, (l + r) / 2, s, e, idx * 2) + query((l + r) / 2 + 1, r, s, e, idx * 2 + 1);
}
int main()
{
	scanf("%d%d", &n, &q);
	arr.resize(n + 1), tree.resize(n * 4);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &arr[i]);
	build(1, n, 1);
	for (int i = 0; i < q; i++) {
		int num;
		scanf("%d%d%d", &num, &a, &b);
		if (num == 1) {
			printf("%lld\n", query(1, n, a, b, 1));
			update(1, n, a, 1, arr[b]), update(1, n, b, 1, arr[a]);
			swap(arr[a], arr[b]);
		}
		else {
			scanf("%d%d", &c, &d);
			printf("%lld\n", query(1, n, a, b, 1) - query(1, n, c, d, 1));
		}
	}
	return 0;
}
/*
����
� ������ ����� ������ ������ ���� �� �־����� ������ ���� ������� �θ���. 
���� ������ ������ �־��� ������� �����ؼ� �ذ��� ���� ������, �װ��� �Ұ����ϰų� ������ �´� ��쿡��
������ ������ ���Ƿ� �ٲ㼭 �� ���ϰ� �ذ��� ���� �ִ�. 
�츮�� ���� ������ ������ ���� ������ �����߱� ������ ���� ������ ���� ������ ���� ���̶�� ������ ���� �غ� �� �ִ�.

�� ���������� ���� n�� ������ q���� ������ �־�����. �־����� ������ ������ ������ ����.

1 a b : [a, b] ������ ���� ���ؼ� ����ϰ�, a��° ���ڿ� b��° ���ڸ� ���� ����(swap) �Ѵ�.
2 a b c d : [a, b] ������ �տ��� [c, d] ������ ���� �� ���� ����Ѵ�.
[a, b] ������ ���̶�, ������ a~b��° ���ڸ� ��� ���� ���� �ǹ��Ѵ�.

�Է�
ù° �ٿ� ������ ���̸� ���ϴ� n(1��n��1,000)�� ������ ������ ���ϴ� q(1��q��10,000)�� �־�����.
��° �ٿ� ���� n�� ������ �ϳ��� ������ ���̿� �ΰ� �־�����. ������ �� ���ڵ��� ��� int�� ���� �̳��̴�. 
���� ��° �� ���� q���� �ٿ� ���� ������ �־�����. 
������ ������ ��1 a b�� �Ǵ� ��2 a b c d���̴�. a, b, c, d�� n���� �۰ų� ���� �ڿ����̸�, a��b, c��d���� ����ȴ�.

���
�־��� ������ ��°��� q���� �ٿ� ���� ����Ѵ�.
*/