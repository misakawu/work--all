#include<iostream>
#include<queue>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<fstream>
#include <windows.h>　
using namespace std;
#define FOR(a,x,y) for(int a=x;a<=y;a++)
#define debug(a) cout<<#a<<": "<<a;


vector<vector<pair<int,int>>> product(11,vector<pair<int,int>>());
int W ; int n;

bool qwe(pair<int, int> a, pair<int, int> b) { return a.second*1.0/a.first > b.second*1.0/b.first; }
void random_make() {
	FOR(i, 1, 10) {
		product[i].push_back({0,0});
		int r = 100, l = 10;
		int w, v;
		FOR(j, 1, n) {
			w = (rand() % (r - l)) + l;
			v = (rand() % (r - l)) + l;
			product[i].push_back({w,v});
		}
		//sort(product[i].begin(), product[i].end(), qwe);
	//	cout << "测试数据集" << i << "为（重量-价值）:";
	//	FOR(j, 1, n) 
	//		cout << product[i][j].first << "-" << product[i][j].second << ' ';
	//	cout << endl;
	}
	W = n * 50;
	//cout << "W =" << W<< endl;
}

void force() {
	FOR(j, 1, 10) {
		long long loop_num = 1 << n;
		loop_num--;
		int mx = 0;
		while (loop_num >= 0) {
			int weight = 0, value = 0;
			FOR(i, 0, n - 1) {
				if (loop_num >> i & 1) {
					weight += product[j][i].first;
					value += product[j][i].second;
				}
			}
			if (weight <= W) value = max(value, mx);
			loop_num--;
		}
		cout << "暴力法第" << j << "次测试完成\n";
	}
}

void DP() {
	FOR(i, 1, 10) {
		vector<int> dp( W+1, 0);
		FOR(x, 1, n) {
			for (int y = W; y >= 0; y--) 
				if (y - product[i][x].first >= 0)
					dp[y] = max(dp[y], dp[y - product[i][x].first] + product[i][x].second);
		}
		cout << "DP第" << i << "次测试完成\n";
	}
}

int bw=0, bv=0;
int best_v = 0;
int branch(int x, int i) {
	int left_w = W - bw;
	int cur_v = bv;
	while (i <= n && left_w > 0) {
		left_w -= product[x][i].first;
		cur_v += product[x][i].second;
		i++;
	}
	if (i <= n&&left_w>0)
		cur_v += product[x][i].second / product[x][i].first * left_w;
	return cur_v;
}
int turn;
void backtrack(int x, int round) {
	if (round > n) {
		best_v = max(best_v, bv);
		return;
	}
	if (bw + product[x][round].first <= W) {
		bw += product[x][round].first;
		bv += product[x][round].second;
		backtrack(x, round + 1);
		bw -= product[x][round].first;
		bv -= product[x][round].second;
	}
	if (branch(x, round + 1) > best_v)
		backtrack(x, round + 1);
	else turn++;
}

void recall() {
	FOR(i, 1, 10) {
		turn = 0;
		backtrack(i,1);
		bw = 0, bv = 0;
		best_v = 0;
		cout << "回溯第" << i << "次测试完成，剪枝"<<turn<<"次\n";
	}
}

int main() {
	cout << "输入测试样本容量,最好不超过30\n";
	cin >> n;
	cout << "数据已按单位价值降序排列" << endl;
	random_make();
	cout << "生成10*"<<n<<"的测试样例\n";
	LARGE_INTEGER t1, t2, tc;
	double time;

	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	DP();
	QueryPerformanceCounter(&t2);
	time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	printf("DP平均运行时间为%.7fs\n", time / 10);

	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	recall();
	QueryPerformanceCounter(&t2);
	time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	printf("回溯平均运行时间为%.7fs\n", time / 10);
	
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	force();
	QueryPerformanceCounter(&t2);
	time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	printf("暴力法平均运行时间为%.7fs\n", time / 10);
}