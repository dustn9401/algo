#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int arr[100001], lower, upper, n, m;
vector<int> v;
vector<vector<int>> tree;

void tree_init(int s, int e, int i) {
	if (s == e) {
		tree[i].push_back(arr[s]);
		return;
	}
	int l = i * 2, r = i * 2 + 1;
	tree_init(s, (s + e) / 2, l);
	tree_init((s + e) / 2 + 1, e, r);
	auto lt = tree[l].begin(), rt = tree[r].begin(), le = tree[l].end(), re = tree[r].end();
	while (lt != le || rt != re) {
		if (rt == re)
			tree[i].push_back(*lt), lt++;
		else if (lt == le)
			tree[i].push_back(*rt), rt++;
		else {
			if (*lt < *rt)
				tree[i].push_back(*lt), lt++;
			else
				tree[i].push_back(*rt), rt++;
		}
	}
}
void small_query(int s, int e, int l, int r, int idx, int x)
{
	if (s > r || e < l)
		return;
	if (s >= l && e <= r) {
		lower += distance(tree[idx].begin(), lower_bound(tree[idx].begin(), tree[idx].end(), x));
		upper += distance(tree[idx].begin(), upper_bound(tree[idx].begin(), tree[idx].end(), x));
		return;
	}
	small_query(s, (s + e) / 2, l, r, idx * 2, x);
	small_query((s + e) / 2 + 1, e, l, r, idx * 2 + 1, x);
}
int query(int l, int r, int k) {
	int ret = 0, lo = -1000000000, hi = 1000000000;
	while (true) {
		lower = upper = 0;
		if (lo + hi < 0)
			ret = (lo + hi - 1) / 2;
		else
			ret = (lo + hi) / 2;
		small_query(1, n, l, r, 1, ret);
		if (lower == k - 1 && upper == k)
			break;
		lower < k ? lo = ret : hi = ret;
	}
	return ret;
}
int main()
{
	scanf("%d%d", &n, &m);
	tree.resize(n * 4);
	for (int i = 1; i <= n; i++)
		scanf("%d", arr + i);
	tree_init(1, n, 1);
	for (int i = 0; i < m; i++) {
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		printf("%d\n", query(l, r, k));
	}
	return 0;
}
/*
4 100
-100 -10 0 10

����
�����̴� �ڷ� ���� ������Ʈ�� �ϰ� �ִ�. �ٸ� �л����� ������Ʈ ������ ����, ť�� ���� �⺻ �ڷ� ������ �����ϴ� ������ �����ߴ�.
������, �����̴� ���ο� �ڷ� ������ �������.
�����̰� ���� �ڷᱸ���� �迭�� �����ϴ� ���̴�.
�迭 a[1...n]���� ���� �ٸ� ���� n�� ����Ǿ� �ִ�. �����̴� ���⿡ Q(i,j,k)��� �Լ��� ������ ��θ� ���� �� ���̴�.
Q(i,j,k): �迭 a[i...j]�� �������� ��, k��° ���� �����ϴ� �Լ�
���� ���, a = (1,5,2,6,3,7,4)�� ��� Q(2,5,3)�� ���� ���ϴ� ������ ���캸��.
a[2...5]�� (5,2,6,3)�̰�, �� �迭�� �����ϸ� (2,3,5,6)�� �ȴ�. ������ �迭���� 3��° ���� 5�̴�. ���� Q(2,5,3)�� ���ϰ��� 5�̴�.
�迭 a�� �־�����, Q�Լ��� ȣ���� Ƚ���� �־����� ��, �� �Լ��� ���ϰ��� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù° �ٿ� �迭�� ũ�� n�� �Լ� Q�� ȣ���� Ƚ�� m�� �־�����. (1 �� n �� 100,000, 1 �� m �� 5,000)
��° �ٿ��� �迭�� ���Ե� ������ ������� �־�����. �� ������ ���밪�� 109�� ���� �ʴ� �����̴�.
���� m�� �ٿ��� Q(i,j,k)�� ȣ���� �� ����� ���� i,j,k�� �־�����. (1 �� i �� j �� n, 1 �� k �� j-i+1)

���
Q�Լ��� ȣ���� ������ �� �Լ��� ���ϰ��� �� �ٿ� �ϳ��� ����Ѵ�.
*/