#include <cstdio>
#include <cstring>
using namespace std;
char str[50][51], res[51];
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%s", str + i);
	strcpy(res, str[0]);
	for (int i = 1; i < n; i++)
		for (int j = 0; str[i][j]; j++)
			if (res[j] ^ str[i][j]) res[j] = '?';
	printf("%s", res);
	return 0;
}