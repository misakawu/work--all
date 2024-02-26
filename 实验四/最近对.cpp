#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<vector>
#include<random>
using namespace std;
#define FOR(a,x,y) for(int a=x;a<=y;a++)
#define pii pair<int,int>



vector<pii> randpoint(int n,int a,int b) {
	vector<pii> ret;
	FOR(i, 1, n) {
		int x = (rand() % (b - a + 1)) + a;
		int y = (rand() % (b - a + 1)) + a;
		ret.push_back({ x,y });
	}
	return ret;
}

void brute(vector<pii> a) {
	int n = a.size();
	float mi = 0x3f3f3f3f3f;
	int x=1, y=1;
	FOR(i, 0, n - 1) {
		FOR(j, i+1, n - 1) {
			float dis = sqrt(pow(abs(a[i].first - a[j].first), 2) + pow(abs(a[i].second - a[j].second), 2));
			if (dis < mi) {
				x = i, y = j;
				mi = dis;
			}
		}
	}
	cout << "最小距离为" << mi << "\n";
	printf("(%d,%d) (%d,%d)\n", a[x].first, a[x].second, a[y].first, a[y].second);
}

class tem
{
public:
	int x, y;
	float dis;
	tem(int x, int y, float dis) {
		this->x = x;
		this->y= y;
		this->dis = dis;
	}
};

tem partition(vector<pii>a, int l, int r) {
	int mid = l + r >> 1;
	int len = r - l;
	if (len == 1) {
		float dis= sqrt(pow(abs(a[l].first - a[r].first), 2) + pow(abs(a[l].second - a[r].second), 2));
		tem ans(l,r,dis);
		return ans;
	}
	else if(len==2)
	{
		float d1= sqrt(pow(abs(a[l].first - a[r].first), 2) + pow(abs(a[l].second - a[r].second), 2));
		float d2= sqrt(pow(abs(a[l+1].first - a[r].first), 2) + pow(abs(a[l+1].second - a[r].second), 2));
		float d3= sqrt(pow(abs(a[l].first - a[r-1].first), 2) + pow(abs(a[l].second - a[r-1].second), 2));
		float mi = min(d1, min(d2, d3));
		if (mi == d1) {
			tem ans(l, r, d1);
			return ans;
		}
		else if (mi == d2) {
			tem ans(l + 1, r, d2);
			return ans;
		}
		else
		{
			tem ans(l, r - 1, d3);
			return ans;
		}
	}
	else {
		tem d1 = partition(a, l, mid);
		tem d2 = partition(a, mid, r);
		if (d1.dis < d2.dis)
			return d1;
		else
			return d2;
	}
		
}

int main() {
	vector<pii> a;
	cout << "输入测试样例数量\n";
	int n; cin >> n;
	a = randpoint(n, -100, 100);
	sort(a.begin(), a.end(), less <pii>());

	cout << "测试用例：(已排序,按x坐标升序)\n";
	FOR(i, 0, n - 1) 
		printf("(%d,%d) ", a[i].first, a[i].second);
	cout << endl;

	cout << "暴力法\n";
	brute(a);
	tem ans=partition(a, 0, n - 1);
	int x = ans.x, y = ans.y;
	cout << "分治法\n";
	cout << "最小距离为" << ans.dis << "\n";
	printf("(%d,%d) (%d,%d)\n", a[x].first, a[x].second, a[y].first, a[y].second);
}