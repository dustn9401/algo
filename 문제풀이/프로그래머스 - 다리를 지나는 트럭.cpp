#include <cstdio>
#include <string>
#include <vector>
#include <list>
using namespace std;
typedef struct truck {
	int w, d;
}truck;
int solution(int bridge_length, int weight, vector<int> truck_weights) {
	int answer = 0;
	list<truck> w;
	int cur_w = 0;
	for (int i = 0; i < truck_weights.size();) {
		if (cur_w + truck_weights[i] <= weight && w.size() < bridge_length) {
			for (auto j = w.begin(); j != w.end(); j++) (*j).d--;
			w.push_back({ truck_weights[i], bridge_length }), cur_w += truck_weights[i];
			i++, answer++;
		}
		else {
			answer += w.front().d;
			for (auto j = w.begin(); j != w.end(); j++) (*j).d-= w.front().d;
		}
		if (!w.empty() && w.front().d == 0)
			cur_w -= w.front().w, w.pop_front();
	}
	if (!w.empty()) answer += w.back().d;
	return answer;
}
int main()
{
	vector<int> t = { 7,4,5,6 };
	printf("res = %d\n", solution(2, 10, t));
	return 0;
}