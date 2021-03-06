#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef struct {
	int e, w;
}edge;
vector<vector<edge>> adj(100001);
int main()
{

}
/*
문제
어떤 그래프가 있다. 여기에 크루스칼이 공을 놓으려고 한다.
크루스칼의 공은 이상한 특성을 가지고 있다. 처음에는 아주 낮은 온도를 갖고 있다가 시간에 지남에 따라서 점점 온도가 올라가는 것이다.
그래프에도 이상한 특성이 있다. 크루스칼의 공이 어떤 간선을 지나서 다른 정점으로 이동할 때, 
그 간선의 고유값보다 온도가 같거나 높아야만 그 간선를 통과할 수 있다는 것이다.
당신이 궁금한 것은 x정점에 크루스칼이 공을 놓았을 때, y정점으로 갈 수 있는 최소온도와
그 때 공이 움직일 수 있는 범위안의 정점 개수를 출력하는 것이다.

입력
첫째 줄에는 그래프의 정점의 개수 n과 간선의 개수 m이 주어진다. 
그리고 두 번째 줄에서 m+1번째 줄 까지는 a b c의 형태로 a와 b를 잇는 간선의 고유값이 c라는 의미이다.
m+2번째 줄에는 알고 싶은 쿼리의 개수 Q가 주어진다. m+3번째 줄에서 m+Q+2번째 줄에는 x y가 주어진다.
(n, m, Q <= 100,000 1 <= c <= 1,000,000)

단, 어떠한 두 간선도 고유값이 같은 경우는 없다.

출력
첫 번째 줄에서 Q-1번째 줄 까지 각각의 쿼리마다 x정점에 크루스칼의 공을 놓았을 때 y정점으로 갈 수 있게 되는 최소온도 c와
이때 공이 움직일 수 있는 범위에 포함되는 정점의 개수 v를 u v의 형태로 출력한다. 만약, x에서 y로 가는 경로가 없을 때는 -1을 출력한다.
*/