#include <cstdio>
int main()
{
	int res = 0;
	char s[10][10];
	for (int i = 0; i < 8; i++) {
		scanf("%s", s[i]);
		for (int j = 0; j < 8; j++)
			if (s[i][j] == 'F' && !((i + j) % 2)) res++;
	}
	printf("%d", res);
	return 0;
}