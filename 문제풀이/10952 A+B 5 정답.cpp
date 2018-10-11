#include <cstdio>
int main()
{
	int a, b;
	while (true) {
		scanf("%d%d", &a, &b);
		if (a&&b) printf("%d\n", a + b);
		else break;
	}
	return 0;
}