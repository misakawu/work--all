#include<algorithm>
#include <iostream>
#include<queue>
using namespace std;
int main()
{
	int n; cin >> n;
	priority_queue<int,vector<int>,greater<int>> p;
	for (int i = 0; i < n; i++)
	{
		int x; cin >> x;
		p.push(x);
	}
	while (p.size() > 1) {
		int a = p.top(); p.pop();
		int b = p.top(); p.pop();
		cout << "合并长度为" << a << ' ' << b << "的字符串\n";
		p.push(a + b);
	}
	int ans = p.top();
	cout << "最小代价为" << ans;
}
