#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef struct jw {
	int m;
	ll v;
}jw;
vector<jw> j;
multiset<int> c;
int n, k, w;
int main()
{
	scanf("%d%d", &n, &k);
	j.resize(n);
	for (int i = 0; i < n; i++)
		scanf("%d%lld", &j[i].m, &j[i].v);
	sort(j.begin(), j.end(), [&](jw a, jw b) {return a.v > b.v; });
	for (int i = 0; i < k; i++)
		scanf("%d", &w), c.insert(w);
	ll res = 0;
	for (int i = 0; i < n && !c.empty(); i++) {
		auto it = c.lower_bound(j[i].m);
		if (it != c.end()) res += j[i].v, c.erase(it);
	}
	printf("%lld", res);
	return 0;
}
/*
3 2
5 150
10 200
6 199
10
5
문제
세계적인 도둑 상덕이는 보석점을 털기로 결심했다.
상덕이가 털 보석점에는 보석이 총 N개 있다. 
각 보석은 무게 Mi와 가격 Vi를 가지고 있다. 
상덕이는 가방을 K개 가지고 있고, 각 가방에 담을 수 있는 최대 무게는 Ci이다.
가방에는 최대 한 개의 보석만 넣을 수 있다.
상덕이가 훔칠 수 있는 보석의 최대 가격을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N과 K가 주어진다. (1 ≤ N, K ≤ 300,000)
다음 N개 줄에는 각 보석의 정보 Mi와 Vi가 주어진다. (0 ≤ Mi, Vi ≤ 1,000,000)
다음 K개 줄에는 가방에 담을 수 있는 최대 무게 Ci가 주어진다. (1 ≤ Ci ≤ 100,000,000)
모든 숫자는 양의 정수이다.

출력
첫째 줄에 상덕이가 훔칠 수 있는 보석 가격의 합의 최댓값을 출력한다.
*/