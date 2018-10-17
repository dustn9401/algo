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
����
�������� ���� ����̴� �������� �б�� ����ߴ�.
����̰� �� ���������� ������ �� N�� �ִ�. 
�� ������ ���� Mi�� ���� Vi�� ������ �ִ�. 
����̴� ������ K�� ������ �ְ�, �� ���濡 ���� �� �ִ� �ִ� ���Դ� Ci�̴�.
���濡�� �ִ� �� ���� ������ ���� �� �ִ�.
����̰� ��ĥ �� �ִ� ������ �ִ� ������ ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù° �ٿ� N�� K�� �־�����. (1 �� N, K �� 300,000)
���� N�� �ٿ��� �� ������ ���� Mi�� Vi�� �־�����. (0 �� Mi, Vi �� 1,000,000)
���� K�� �ٿ��� ���濡 ���� �� �ִ� �ִ� ���� Ci�� �־�����. (1 �� Ci �� 100,000,000)
��� ���ڴ� ���� �����̴�.

���
ù° �ٿ� ����̰� ��ĥ �� �ִ� ���� ������ ���� �ִ��� ����Ѵ�.
*/