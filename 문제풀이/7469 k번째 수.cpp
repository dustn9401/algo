#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int arr[100001], lower, upper;
vector<vector<int>> tree(400004);

vector<int> tree_init(int start, int end, int index);
void get_node(int s, int e, int l, int r, int idx, int x);
void get_lower(int x, int idx);

vector<int> tree_init(int start, int end, int index)
{
	if (start == end)
	{
		tree[index].push_back(arr[end]);
		return tree[index];
	}
	vector<int> a = tree_init(start, (start + end) / 2, index * 2);
	vector<int> b = tree_init((start + end) / 2 + 1, end, index * 2 + 1);
	int aidx = 0, bidx = 0;
	while (aidx < a.size() || bidx < b.size())
	{
		if (aidx == a.size())
			tree[index].push_back(b[bidx++]);
		else if (bidx == b.size())
			tree[index].push_back(a[aidx++]);
		else
		{
			if (a[aidx] < b[bidx])
				tree[index].push_back(a[aidx++]);
			else
				tree[index].push_back(b[bidx++]);
		}
	}
	return tree[index];
}
void get_node(int s, int e, int l, int r, int idx, int x)
{
	if (s > r || e < l)
		return;
	if (s >= l && e <= r)
	{
		get_lower(x, idx);
		return;
	}
	get_node(s, (s + e) / 2, l, r, idx * 2, x);
	get_node((s + e) / 2 + 1, e, l, r, idx * 2 + 1, x);
}
void get_lower(int x, int idx)
{
	lower += distance(tree[idx].begin(), lower_bound(tree[idx].begin(), tree[idx].end(), x));
	upper += distance(tree[idx].begin(), upper_bound(tree[idx].begin(), tree[idx].end(), x));
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", arr + i);
	tree_init(1, n, 1);
	for (int i = 0; i < m; i++)
	{
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		int left = -1000000000, right = 1000000000, pivot = 0;
		while (left < right)
		{
			lower = upper = 0;
			if (left + right >= 0) pivot = (left + right) / 2;
			else pivot = (left + right - 1) / 2;
			get_node(1, n, l, r, 1, pivot);
			if (lower <= k - 1 && upper >= k)
				break;
			else if (lower <= k - 1)
				left = pivot;
			else
				right = pivot;
		}
		printf("%d\n", pivot);
	}
	return 0;
}
/*
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