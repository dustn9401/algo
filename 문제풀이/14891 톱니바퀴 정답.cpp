#include <cstdio>
int g[5];
int LS(int n) {
	int ret = (n << 1) % 256;
	return ret += (n >> 7) ? 1 : 0;
}
int RS(int n) {
	int ret = n >> 1;
	return ret += n % 2 ? 128 : 0;
}
int main()
{
	for (int i = 1; i < 5; i++) {
		char s[10];
		scanf("%s", s);
		for (int j = 0; j < 8; j++) {
			if (s[j] == '0') continue;
			g[i] += 1 << (7 - j);
		}
	}
	int k;
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		int a, b, r[5] = { 0 };
		scanf("%d%d", &a, &b);
		r[a] = b;
		for (int j = 1; j <= 3; j++) {
			int lt = a - j, rt = a + j;
			if (rt <= 4 && r[rt - 1] && (g[rt - 1] >> 5) % 2 != (g[rt] >> 1) % 2)
				r[rt] = r[rt - 1] == 1 ? -1 : 1;
			if (lt >= 1 && r[lt + 1] && (g[lt + 1] >> 1) % 2 != (g[lt] >> 5) % 2)
				r[lt] = r[lt + 1] == 1 ? -1 : 1;
		}
		for (int j = 1; j < 5; j++) {
			if (r[j] == 1) g[j] = RS(g[j]);
			if (r[j] == -1) g[j] = LS(g[j]);
		}
	}
	int res = 0;
	for (int i = 1; i <= 4; i++)
		res += (g[i]>>7) << (i-1);
	printf("%d", res);
	return 0;
}