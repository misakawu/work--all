#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
using namespace std;
#define FOR(x,a,b) for(int x=a;x<=b;x++)

vector<int> a;
int TOPk(int l, int r) {
	if (l == r)return a[l];
	else if (l + 1 == r)return max(a[l], a[r]);
	else return max(TOPk(l, l + r >> 1), TOPk(l + r >> 1, r));
}

int main() {
	int n;
	cin >> n;
	a.assign(n + 1, 0);
	FOR(i, 1, n)cin >> a[i];
	cout << TOPk(1, n);
}