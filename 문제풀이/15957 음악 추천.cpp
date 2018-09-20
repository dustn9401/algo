#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n, k, j;
int parent[100001] = { 0 };
int sing[100001] = { 0 };
typedef struct dat {
	int t, p, s;
}dat;
typedef struct node {
	int num_chld;
}node;
vector<dat> v;
int main()
{
	scanf("%d%d%d", &n, &k, &j);
	v.resize(k);
	for (int i = 2; i <= n; i++)
		scanf("%d", parent + i);
	for (int i = 1; i <= n; i++)
		scanf("%d", sing + i);
	for (int i = 0; i < k; i++)
		scanf("%d%d%d", &v[i].t, &v[i].p, &v[i].s);
	sort(v.begin(), v.end(), [&](dat a, dat b) {return a.t < b.t; });
	for (int i = 0; i < k; i++) {

	}
}
/*
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