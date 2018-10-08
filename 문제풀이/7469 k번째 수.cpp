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
문제
현정이는 자료 구조 프로젝트를 하고 있다. 다른 학생들은 프로젝트 주제로 스택, 큐와 같은 기본 자료 구조를 구현하는 주제를 선택했다. 
하지만, 현정이는 새로운 자료 구조를 만들었다.
현정이가 만든 자료구조는 배열을 응용하는 것이다. 
배열 a[1...n]에는 서로 다른 수가 n개 저장되어 있다. 현정이는 여기에 Q(i,j,k)라는 함수를 구현해 모두를 놀라게 할 것이다.
Q(i,j,k): 배열 a[i...j]를 정렬했을 때, k번째 수를 리턴하는 함수
예를 들어, a = (1,5,2,6,3,7,4)인 경우 Q(2,5,3)의 답을 구하는 과정을 살펴보자.
a[2...5]는 (5,2,6,3)이고, 이 배열을 정렬하면 (2,3,5,6)이 된다. 정렬한 배열에서 3번째 수는 5이다. 따라서 Q(2,5,3)의 리턴값은 5이다.
배열 a가 주어지고, Q함수를 호출한 횟수가 주어졌을 때, 각 함수의 리턴값을 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 배열의 크기 n과 함수 Q를 호출한 횟수 m이 주어진다. (1 ≤ n ≤ 100,000, 1 ≤ m ≤ 5,000)
둘째 줄에는 배열에 포함된 정수가 순서대로 주어진다. 각 정수는 절대값이 109를 넘지 않는 정수이다.
다음 m개 줄에는 Q(i,j,k)를 호출할 때 사용한 인자 i,j,k가 주어진다. (1 ≤ i ≤ j ≤ n, 1 ≤ k ≤ j-i+1)

출력
Q함수를 호출할 때마다 그 함수의 리턴값을 한 줄에 하나씩 출력한다.
*/