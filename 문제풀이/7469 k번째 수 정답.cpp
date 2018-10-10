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