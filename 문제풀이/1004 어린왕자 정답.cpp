#include <cstdio>
#include <vector>
using namespace std;
typedef struct {
	int x, y, r;
}c;
bool in(int x, int y, c cc) {
	int dx = x - cc.x, dy = y - cc.y;
	return dx * dx + dy * dy < cc.r*cc.r ? true : false;
}
int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int sx, sy, ex, ey, n;
		scanf("%d%d%d%d%d", &sx, &sy, &ex, &ey, &n);
		vector<c> v(n);
		for (int i = 0; i < n; i++)
			scanf("%d%d%d", &v[i].x, &v[i].y, &v[i].r);
		int res = 0;
		for (c cc : v)
			if (in(sx, sy, cc) ^ in(ex, ey, cc)) res++;
		printf("%d\n", res);
	}
	return 0;
}