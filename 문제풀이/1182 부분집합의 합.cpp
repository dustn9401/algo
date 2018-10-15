#include <cstdio>
int n, s, arr[21], res;
int main()
{
	scanf("%d%d", &n, &s);
	int bit = 1 << n;
	for (int i = 1; i <= n; i++)
		scanf("%d", arr + i);
	for (int i = 1; i < bit; i++) {
		int num = 0;
		for (int j = 0; j < n; j++)
			if ((i >> j) % 2) num += arr[j + 1];
		if (num == s) res++;
	}
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