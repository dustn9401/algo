#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100001
using namespace std;
int n, k, j;
int par[MAXN], sing[MAXN], hv[MAXN], w[MAXN];
vector<vector<int>> adj(MAXN);
typedef struct dat {
	int t, p, s;
}dat;
vector<dat> v;
vector<vector<dat>> lazy(MAXN);
void build(int c) {	
	for (int i : adj[c])
		build(i), hv[c] += hv[i];
	hv[c]++;
}
vector<int> solve() {
	vector<int> ans(MAXN);
	int l = 1, r = 1000000000, mid = 0;
	while (l != r) {
		mid = (l + r) / 2;
	}
}
int main()
{
	scanf("%d%d%d", &n, &k, &j);
	v.resize(k);
	for (int i = 2; i <= n; i++) {
		scanf("%d", par + i);
		adj[par[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++)
		scanf("%d", sing + i);
	for (int i = 0; i < k; i++)
		scanf("%d%d%d", &v[i].t, &v[i].p, &v[i].s);
	sort(v.begin(), v.end(), [](dat a, dat b)->bool {return a.t < b.t; });
	vector<int> l(k, 0), r(k, k);
	while (true) {
		for (int i = 1; i <= n; i++) {

		}
	}
	return 0;
}
/*
어떻게 풀지>??
1. 일단 가중치 부여를 시간순으로 정렬하는 건 맞다.
2. 이후에 시간별로 가중치를 루트부터 모든 자식에게 더하면서 점수가 넘으면 결과 저장 => 100% 시간초과
3. 전처리가 필요한데, 어떻게??
4. 알고 있는 정보: 트리의 구조, 무게, 가수 별 곡 수.
5. 모든 가수의 각 시간 별 점수 저장 => 100,000 * 100,000 메모리 초과
10/23
결과값은 '시간' 이며, 범위는 1 ~ 1,000,000,000
데이터는 시간 순서로 정렬되어 있고, 최대 10만 개
시간초과를 피하려면 모든 데이터에 대해 모든 노드를 갱신하면 안됨. => 방법이 있는가?
어떤 데이터로부터 가중치를 갱신하였을 때, 목표 점수를 넘을 가능성이 있는 경우만 갱신?
	=> 예를 들어, 노드가 100개인 트리의 루트에 100점을 부여하고, 목표 점수는 5점이라 하면 ? 80점이라 하면? -> 모두 넘는것이 가능!
	=> 범위가 너무 넓음...


입력
입력의 첫째 줄에는 세 정수로, 곡의 수 N(2 ≤ N ≤ 100,000), 추천 알고리즘의 결과 데이터의 수 K(1 ≤ K ≤ 100,000),
목표 점수 J(10 ≤ J ≤ 10^8)가 주어진다. 각각의 곡은 1번부터 N번까지 번호가 붙어 있다.
다음 줄에 N-1개의 곡 번호가 주어지는데, 이는 2번 곡부터 해당 곡의 부모 노드가 되는 곡의 번호이다. 1번 곡은 부모 노드가 없다.
다음 줄에 N개의 수가 주어지는데, 이는 1번 곡부터 해당 곡을 부른 가수의 번호이다. 가수의 번호는 1 이상 N 이하의 자연수이다.
다음 K개의 줄에 추천 알고리즘의 결과 데이터가 하나씩 주어진다. 결과 데이터는 T, P, S의 세 값으로 주어진다.
T는 데이터가 계산된 시간으로, 1 이상 10^9 이하의 자연수이다. 
P는 점수가 부여되는 서브트리의 루트가 되는 곡의 번호이다.
S는 서브트리에 부여할 가중치로, 1 이상 10^9 이하의 자연수이다.

출력
출력은 N개의 줄로 이루어진다. 1번 곡부터 해당 곡을 부른 가수의 평균 점수가 J를 넘게 되는 시간을 출력한다.
점수가 J를 넘는 일이 없는 경우 -1을 출력한다. 같은 가수가 부른 곡은 같은 값을 가지게 될 것이다.

3 3 52
1 1
1 1 3
1 1 90
2 2 100
3 1 30
*/