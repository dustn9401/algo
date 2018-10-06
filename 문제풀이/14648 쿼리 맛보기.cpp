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
문제
어떤 문제에 비슷한 형태의 질문이 여러 개 주어지는 문제를 쿼리 문제라고 부른다. 
쿼리 문제는 쿼리가 주어진 순서대로 실행해서 해결할 수도 있지만, 그것이 불가능하거나 조건이 맞는 경우에는
쿼리의 순서를 임의로 바꿔서 더 편하게 해결할 수도 있다. 
우리는 예선 문제에 쿼리에 대한 설명이 등장했기 때문에 본선 문제에 쿼리 문제가 나올 것이라는 예상을 쉽게 해볼 수 있다.

이 문제에서는 길이 n의 수열과 q개의 쿼리가 주어진다. 주어지는 쿼리의 종류는 다음과 같다.

1 a b : [a, b] 구간의 합을 구해서 출력하고, a번째 숫자와 b번째 숫자를 서로 스왑(swap) 한다.
2 a b c d : [a, b] 구간의 합에서 [c, d] 구간의 합을 뺀 값을 출력한다.
[a, b] 구간의 합이란, 수열의 a~b번째 숫자를 모두 더한 값을 의미한다.

입력
첫째 줄에 수열의 길이를 뜻하는 n(1≤n≤1,000)과 쿼리의 개수를 뜻하는 q(1≤q≤10,000)가 주어진다.
둘째 줄에 길이 n의 수열이 하나의 공백을 사이에 두고 주어진다. 수열의 각 숫자들은 모두 int형 범위 이내이다. 
이후 셋째 줄 부터 q개의 줄에 걸쳐 쿼리가 주어진다. 
쿼리의 형식은 “1 a b” 또는 “2 a b c d”이다. a, b, c, d는 n보다 작거나 같은 자연수이며, a≤b, c≤d임이 보장된다.

출력
주어진 쿼리의 출력값을 q개의 줄에 걸쳐 출력한다.
*/