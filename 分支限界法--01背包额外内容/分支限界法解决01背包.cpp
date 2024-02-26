#include<iostream>
#include<queue>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<stack>
#include<fstream>
#include <windows.h>　
using namespace std;
#define FOR(a,x,y) for(int a=x;a<=y;a++)
#define debug(a) cout<<#a<<": "<<a;


struct State {
	int capacity; // 背包容量
	int value; // 当前的价值总和
	int index; // 当前的物品索引
	vector<int> choices; // 当前的物品选择情况
};
int cnt = 0;

// 限界函数
int bound(State state, vector<int> weights, vector<int> values, int capacity) {
	int remaining_capacity = capacity - state.capacity;
	int bound_value = state.value;
	int item_index = state.index;

	while (remaining_capacity > 0 && item_index < weights.size()) {
		if (remaining_capacity >= weights[item_index]) {
			remaining_capacity -= weights[item_index];
			bound_value += values[item_index];
		}
		else {
			bound_value += remaining_capacity * (values[item_index] / weights[item_index]);
			remaining_capacity = 0;
		}
		item_index++;
	}

	return bound_value;
}

// 目标函数
int target(State state) {
	return state.value;
}

// 优先队列的比较函数
struct Compare {
	bool operator()(const State& s1, const State& s2) {
		return target(s1) < target(s2);
	}
};

int knapsack(vector<int> weights, vector<int> values, int capacity) {
	priority_queue<State, vector<State>, Compare> pq;

	State initial_state;
	initial_state.capacity = 0;
	initial_state.value = 0;
	initial_state.index = 0;
	initial_state.choices = vector<int>(weights.size(), 0);
	pq.push(initial_state);

	int best_value = 0;

	while (!pq.empty()) {
		State current_state = pq.top();
		pq.pop();

		if (current_state.index == weights.size()) {
			best_value = max(best_value, current_state.value);
			continue;
		}

		int current_bound = bound(current_state, weights, values, capacity);
		if (current_bound < best_value) {
			cnt++;
			continue;
		}

		if (current_state.capacity + weights[current_state.index] <= capacity) {
			State include_state = current_state;
			include_state.capacity += weights[current_state.index];
			include_state.value += values[current_state.index];
			include_state.choices[current_state.index] = 1;
			include_state.index++;
			pq.push(include_state);
		}
		

		State exclude_state = current_state;
		exclude_state.index++;
		pq.push(exclude_state);
	}

	return best_value;
}

vector<int> randm_make(int n) {
	vector<int> ans;
	int r = 100, l = 10;
	FOR(i, 1, n) ans.push_back((rand() % (r - l)) + l);
	return ans;
}

bool qwe(pair<int, int> a, pair<int, int> b) { return a.second * 1.0 / a.first < b.second * 1.0 / b.first; }
void qsort(vector<int>& a,vector<int>& b) {
	int n = a.size();
	vector<pair<int, int>> x;
	FOR(i, 0, n - 1)x.push_back({ a[i],b[i] });
	sort(x.begin(), x.end(), qwe);
	FOR(i, 0, n - 1)a[i] = x[i].first, b[i] = x[i].second;
	return;
}

int main() {
	cout << "输入测试数据大小\n";
	int n; cin >> n;
	vector<int> weights = randm_make(n);
	vector<int> values = randm_make(n);
	//int n = 6;
	//vector<int> weights{ 5, 3, 2, 10, 4, 2 };
	//vector<int> values{ 11, 8, 15, 18, 12, 6};
	qsort(values, weights);
	cout << "数据生成完毕,按单位价值什序排列\n（重量-价值）";
	FOR(i, 0, n-1) cout << weights[i] << '-' << values[i] << ' ';
	int capacity = 20;

	LARGE_INTEGER t1, t2, tc;
	double time;

	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	int max_value = knapsack(weights, values, capacity);
	QueryPerformanceCounter(&t2);
	time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "答案为" << max_value << endl;
	printf("分支限界法耗时%.7f,剪枝%d次\n", time / 10,cnt);


	return 0;
}
