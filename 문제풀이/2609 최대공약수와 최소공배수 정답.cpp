#include <cstdio>
#include <algorithm>
using namespace std;
int GCD(int a, int b) {
	if (a < b) swap(a, b);
	while (b) {
		a %= b;
		if (a < b) swap(a, b);
	}
	return a;
}
int LCM(int a, int b) {
	return (a*b) / GCD(a, b);
}
int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	printf("%d\n%d\n", GCD(a, b), LCM(a, b));
	return 0;
}