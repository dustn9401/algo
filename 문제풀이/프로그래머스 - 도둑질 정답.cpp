/*
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
int n, note[1000000];
int memo(int idx, int bef, int ed, const vector<int>& m) {
	if (idx >= ed) return 0;
	if (note[idx] != -1) return note[idx];
	note[idx] = max(note[idx], m[idx] + memo(idx + 2, 1, ed, m));
	note[idx] = max(note[idx], memo(idx + 1, 0, ed, m));
	return note[idx];
}
int solution(vector<int> money) {
	int answer = 0;
	n = money.size();
	memset(note, -1, sizeof(note));
	answer = memo(1, 0, n, money);
	memset(note, -1, sizeof(note));
	answer = max(answer, memo(0, 0, n - 1, money));
	return answer;
}
*/
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
int n, note[1000000];
int memo(int idx, int bef, int ed, const vector<int>& m) {
	if (!idx) memset(note, 0, sizeof(note));
	if (idx >= ed) return 0;
	if (note[idx]) return note[idx];
	note[idx] = max(note[idx], m[idx] + memo(idx + 2, 1, ed, m));
	note[idx] = max(note[idx], memo(idx + 1, 0, ed, m));
	return note[idx];
}
int solution(vector<int> money) {
	n = money.size();
	return max(memo(1, 0, n, money), memo(0, 0, n - 1, money));
}