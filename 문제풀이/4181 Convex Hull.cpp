#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
typedef long long ll;
int n;
typedef struct point {
	ll x, y;
}point;
vector<point> v;
int main()
{
	scanf("%d", &n);
	int x, y, c, lo = 0;
	for (int i = 0; i < n; i++) {
		scanf("%lld%lld%c", x, y, c);
		if (c == 'Y') {
			v.push_back({ x,y });
			if (v[lo].x > v[i].x) lo = i;
			else if (v[lo].x == v[i].x && v[lo].y > v[i].y) lo = i;
		}
	}
	sort(v.begin(), v.end(), [&](point a, point b) { return v[lo].x*a.y - v[lo].y - a.x < v[lo].x*b.y - v[lo].y - b.x; });
	for (auto i : v) {
		
	}
}
/*
문제

때때로 주어진 점들 사이에서 볼록 껍질(Convex Hull)을 찾아내는 기술은 요긴하게 쓰인다.
ACM 월드파이널에서 볼록 껍질을 응용해야 하는 문제가 출제되다 보니, 이걸 할 줄 아는 것은 참가자의 소양이 되었다.
이 작업은 크게 두 단계의 과정으로 이루어진다. 
첫 번째 단계는 볼록 껍질을 이루는 점들을 찾아내는 것이고, 두 번째 단계는 이 점들을 반시계 방향으로 순서를 매기는 것이다.
첫 번째 단계는 이미 완료되었다고 할 때, 두 번째 단계를 수행하는 프로그램을 작성하시오.

입력
첫 번째 줄에는 점의 개수 n이 주어진다. (3 <= n <= 100,000)
두 번째 줄부터 n개의 줄에 걸쳐 각 점에 대한 정보 x, y, c가 주어진다.
x, y는 정수이며 절댓값이 1,000,000,000을 넘지 않고, c는 Y 또는 N인 문자이다.
Y는 이 점이 볼록 껍질에 속해있음을, N이면 아님을 의미한다.
중복되는 점은 없으며, 모든 점이 한 직선 위에 있는 경우도 없다.

출력
첫 번째 줄에 볼록 껍질을 이루는 점의 개수를 출력한다.
이어서 한 줄에 하나씩 그 점들의 좌표를 x y 형태로 출력하는데, 이 점들은 반시계 방향으로 순서를 이루어야 한다.
첫 번째 좌표는 x좌표가 가장 작은 점이어야 하며, 만약 그런 좌표가 여러 개라면 그 중에서 y좌표가 가장 작은 점을 선택한다.
*/