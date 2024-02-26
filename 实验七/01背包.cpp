#include<random>
#include<vector>
#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)

vector<pair<int, int>> item;//firstΪ������secondΪ��ֵ

void random_make(int n) {
	item.push_back({ 0,0 });
	int r = 10, l = 1;
	FOR(i, 1, n) {
		int a = (rand() % (r - l + 1)) + l;
		int b = (rand() % (r - l + 1)) + l;
		item.push_back({ a,b });
	}
}

void solve(int m,int n) {
	vector<vector<int>> dp(m+1, vector<int>(2,0));
	FOR(i, 1, n) {
		for (int j = m; j > 0; j--)
		{
			dp[j][0] = max(dp[j - 1][0],dp[j-1][1]);
			if (j - item[i].first > 0)
				dp[j][1] = max(dp[j - item[i].first][1], dp[j - item[i].first][0])+item[i].second;
			else
				dp[j][1]= max(dp[j - 1][0], dp[j - 1][1]);
		}
	}
	cout<<"����ֵΪ"<< max(dp[m][0], dp[m][1])<<endl;
}

int main() {
	cout << "��������������:";
	int n; cin >> n;
	random_make(n);
	FOR(i, 1, n)
		printf("��%d����Ʒ������%d ��ֵ %d\n", i, item[i].first, item[i].second);
	cout << "���뱳������";
	int m; cin >> m;
	solve(m,n);
	system("pause");
	return 0;
}