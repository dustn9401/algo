#include <cstdio>
int n, s, arr[21], res;
int solve(int st, int rem) {
	int ret = arr[st];
	if (!rem) return ret;
	for (int i = st + 1; i <= n; i++) {
		if ((ret += solve(i, rem - 1)) == s)
			res++;
	}
	return ret;
}
int main()
{
	scanf("%d%d", &n, &s);
	for (int i = 1; i <= n; i++)
		scanf("%d", arr + i);
	for (int i = 1; i <= n; i++)
		solve(0, i);
	printf("%d", res);
	return 0;
}
/*
1, 2, ..., 20
1+2, 1+3, 1+4, ..., 2+3, 2+4, ..., 19+20
1+2+3, 1+2+4, ..., 18+19+20

1 2 3 4 5
12 13 14 15 23 24 25 34 35 45
123 124 125 134 135 145 234 235 245 345
*/