/*
����
�� ���� ȸ�ǽ��� �ִµ� �̸� ����ϰ��� �ϴ� N���� ȸ�ǵ鿡 ���Ͽ� ȸ�ǽ� ���ǥ�� ������� �Ѵ�. 
�� ȸ�� I�� ���� ���۽ð��� ������ �ð��� �־��� �ְ�, �� ȸ�ǰ� ��ġ�� �ʰ� �ϸ鼭 ȸ�ǽ��� ����� �� �ִ� �ִ���� ȸ�Ǹ� ã�ƶ�.
��, ȸ�Ǵ� �ѹ� �����ϸ� �߰��� �ߴܵ� �� ������ �� ȸ�ǰ� ������ �Ͱ� ���ÿ� ���� ȸ�ǰ� ���۵� �� �ִ�.
ȸ���� ���۽ð��� ������ �ð��� ���� ���� �ִ�. �� ��쿡�� �������ڸ��� ������ ������ �����ϸ� �ȴ�.

�Է�
ù° �ٿ� ȸ���� �� N(1 �� N �� 100,000)�� �־�����. 
��° �ٺ��� N+1 �ٱ��� �� ȸ���� ������ �־����µ� �̰��� ������ ���̿� �ΰ� ȸ���� ���۽ð��� ������ �ð��� �־�����.
���� �ð��� ������ �ð��� 2^31-1���� �۰ų� ���� �ڿ��� �Ǵ� 0�̴�.

���
ù° �ٿ� �ִ� ����� �� �ִ� ȸ�� ���� ����Ͽ���.
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef struct {
	int s, e;
}ii;
vector<ii> v, res;
int n;
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int s, e;
		scanf("%d%d", &s, &e);
		v.push_back({ s,e });
	}
	sort(v.begin(), v.end(), [&](ii a, ii b) {return a.s < b.s; });
	for (auto i : v) {
		if (res.empty())
			res.push_back(i);
		else if (i.e < res.back().e)
			res.pop_back(), res.push_back(i);
		else if (i.s >= res.back().e)
			res.push_back(i);
	}
	printf("%d\n", res.size());
	return 0;
}