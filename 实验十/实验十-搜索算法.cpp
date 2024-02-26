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

vector<vector<pair<int,int>>> product(11,vector<pair<int,int>>());
int W ; int n;

bool qwe(pair<int, int> a, pair<int, int> b) { return a.second * 1.0 / a.first > b.second * 1.0 / b.first; }
void random_make() {
	FOR(i, 1, 10) {
		product[i].push_back({ 0,0 });
		//srand(time(0));
		int r =10, l = 5;
		int w, v;
		FOR(j, 1, n) {
			w = (rand() % (r - l)) + l;
			v = (rand() % (r - l)) + l;
			product[i].push_back({ w,v });
		}
		sort(product[i].begin(), product[i].end(), qwe);
		//cout << "测试数据集" << i << "为（重量-价值）:";
		//FOR(j, 1, n)
		//	cout << product[i][j].first << "-" << product[i][j].second << ' ';
		//cout << endl;
	}
	W = n*7 ;
	//cout << "W =" << W << endl;
}


int bw = 0, bv = 0;
int best_v = 0;
int branch(int x, int i) {
	int left_w = W - bw;
	int cur_v = bv;
	while (i <= n && left_w > 0) {
		left_w -= product[x][i].first;
		cur_v += product[x][i].second;
		i++;
	}
	if (i <= n)
		cur_v += product[x][i].second*1.0 / product[x][i].first * left_w;
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
		backtrack(i, 1);
		cout << "回溯第" << i << "次测试完成，剪枝" << turn << "次,答案为"<<best_v<<'\n';
		bw = 0, bv = 0;
		best_v = 0;
	}
}


double branch_try(int q,int i,int w) {
	int left_w = W - w;
	double value_mx = 0;
	value_mx += left_w * (product[q][i].second*1.0 / product[q][i].first);
	return value_mx;
}
int q; 
void knapsack(int round){
	stack<int> Bag;
	int MX = 0;
	int weight = 0;
	int value = 0;
	int i;
	int cnt = 0;
	
	for (i = 1; ; i++)
	{
		if (branch_try(round, i, weight) + value > MX)//剪枝
		{
			if (weight + product[round][i].first <= W) {
				Bag.push(i);
				weight += product[round][i].first;
				value += product[round][i].second;
			}
		}
		else cnt++;
		
		//当从第一个物品考虑到了最后一个物品时，就确定了一个可以满足条件的装包方法（一个方法就是确定了一个规定每一个物品是否装进包里的策略）
		if (i == n){
			MX = max(MX, value);

			//此时取出最后装进包里的一件物品并对其下一件物品进行考虑（这就是算法的重点：回溯的过程！）
			if (Bag.size()) {
				i = Bag.top();//取出上一件装入的东西（这就是回溯的过程）
				Bag.pop();
				weight -= product[round][i].first;
				value -= product[round][i].second;
			}

			if (i == n){//如果最后装进包里的物品本来在就是编号最大的物品，那么它后面就没有其他物品了，循环必定终止
				if (Bag.empty())break;//当所有物品都被从包中拿出来后，这是说明已经遍历完所有情况，查找结束（相当于解空间树中最右边的子树已经走完了）
				i = Bag.top();//取出上一件装入的东西（这就是回溯的过程）
				Bag.pop();
				weight -= product[round][i].first;
				value -= product[round][i].second;
			}
		}
	}
	printf("第%d次测试，剪枝%d次，答案为%d\n", round, cnt, MX);
}



int main()
{
	cout << "输入测试样本容量,最好不超过30\n";
	cin >> n;
	cout << "数据已按单位价值降序排列" << endl;
	random_make();
	cout << "生成10*" << n << "的测试样例\n";
	LARGE_INTEGER t1, t2, tc;
	double time;

	//QueryPerformanceFrequency(&tc);
	//QueryPerformanceCounter(&t1);
	//recall();
	//QueryPerformanceCounter(&t2);
	//time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	//cout << "回溯递归法平均运行时间为" << time / 10 << 's' << endl;

	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	FOR(i,1,10)
		knapsack(i);
	QueryPerformanceCounter(&t2);
	time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "回溯迭代法平均运行时间为" << time / 10 << 's' << endl;
	
}