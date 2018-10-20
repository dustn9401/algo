#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#define INF 1000000000
#define MAXN 1000000
using namespace std;
int note[MAXN];

int solution(int N, int number) {
	int answer = 0;
	for (int i = 0; i < MAXN; i++) note[i] = INF;
	note[N] = 1;
	for (int i = 1; i <= number; i++) {
		
	}
	if (note[number] >= 8) answer = -1;
	else answer = note[number];
	return answer;
}
int main()
{
	printf("%d", solution(5, 12));
	return 0;
}
/*
���� ����
�Ʒ��� ���� 5�� ��Ģ���길���� 12�� ǥ���� �� �ֽ��ϴ�.

12 = 5 + 5 + (5 / 5) + (5 / 5)
12 = 55 / 5 + 5 / 5
12 = (55 + 5) / 5

5�� ����� Ƚ���� ���� 6,5,4 �Դϴ�. �׸��� ���� ���� ���� ���� 4�Դϴ�.
��ó�� ���� N�� number�� �־��� ��, N�� ��Ģ���길 ����ؼ� ǥ�� �� �� �ִ� ��� �� N ���Ƚ���� �ּڰ��� return �ϵ��� solution �Լ��� �ۼ��ϼ���.

���ѻ���
N�� 1 �̻� 9 �����Դϴ�.
number�� 1 �̻� 32,000 �����Դϴ�.
���Ŀ��� ��ȣ�� ��Ģ���길 �����ϸ� ������ ���꿡�� �������� �����մϴ�.
�ּڰ��� 8���� ũ�� -1�� return �մϴ�.
����� ��
N	number	return
5	12	4
2	11  3
*/