#include <string>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
int nums[1001];
list<int> l;
string solution(vector<int> numbers) {
	string answer = "";
	for (int i : numbers) {
		string is = to_string(i);
		if (!answer.length()) {
			answer += is;
			l.push_back(0);
			l.push_back(answer.length());
		}
		else {
			for (int idx : l) {
				string s = answer.insert(idx, is);

			}
		}
	}
	return answer;
}
/*
999->99->9->98->989
���� ����
0 �Ǵ� ���� ������ �־����� ��, ������ �̾� �ٿ� ���� �� �ִ� ���� ū ���� �˾Ƴ� �ּ���.
���� ���, �־��� ������ [6, 10, 2]��� [6102, 6210, 1062, 1026, 2610, 2106]�� ���� �� �ְ�, ���� ���� ū ���� 6210�Դϴ�.
0 �Ǵ� ���� ������ ��� �迭 numbers�� �Ű������� �־��� ��, ������ ���ġ�Ͽ� ���� �� �ִ� ���� ū ���� ���ڿ��� �ٲپ� return �ϵ��� solution �Լ��� �ۼ����ּ���.

���� ����
numbers�� ���̴� 1 �̻� 100,000 �����Դϴ�.
numbers�� ���Ҵ� 0 �̻� 1,000 �����Դϴ�.
������ �ʹ� Ŭ �� ������ ���ڿ��� �ٲپ� return �մϴ�.
����� ��
numbers	return
[6, 10, 2]	6210
[3, 30, 34, 5, 9]	9534330
*/