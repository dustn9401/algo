#include <cstdio>
char s[100001];
int res, h;
int main()
{
	scanf("%s", s);
	for (int i = 0; s[i]; i++) {
		if (s[i] == '(')
			h++;
		else
			h--, res += (s[i - 1] == '(' ? h : 1);
	}
	printf("%d\n", res);
	return 0;
}