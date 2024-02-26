#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<fstream>
using namespace std;

#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define debug(x) cout<<#x<<":"<<x<<endl;
#define ED endl

void max_heapify(vector<int> &a, int l, int r) {
	int fa = l,son=fa*2+1;
	while (son <= r) {
		if (son + 1 <= r && a[son + 1] > a[son])son++;

		if (a[fa] > a[son])return;
		else
		{
			swap(a[fa], a[son]);
			fa = son;
			son = fa * 2 + 1;
		}
	}
}


void Heap_Sort(vector<int> a) {
	int n = a.size();

	ROF(i, n / 2-1, 0) max_heapify(a, i, n-1);

	ROF(i, n-1, 1) {
		swap(a[i], a[0]);
		max_heapify(a, 0, i-1);
	}

	cout << "�����\n";
	FOR(i, 0, n-1) cout << a[i] << ' ';
	cout << endl;
}

void min_heapify(vector<int>& a, int l, int r) {
	int fa = l, son = fa * 2 + 1;
	while (son <= r) {
		if (son + 1 <= r && a[son + 1] < a[son])son++;

		if (a[fa] < a[son])return;
		else
		{
			swap(a[fa], a[son]);
			fa = son;
			son = fa * 2 + 1;
		}
	}
}

void TOPk(vector<int> a,int k) {
	int n = a.size();

	ROF(i, n / 2 - 1, 0) min_heapify(a, i, n - 1);

	ROF(i, n - 1, n-k) {
		swap(a[i], a[0]);
		min_heapify(a, 0, i - 1);
	}

	cout << "��" << k << "СԪ��Ϊa[n - k]:" << a[n - k];
}

int main() {
	cout << "�����������������";
	int n; cin >> n;
	cout << "�������������";
	vector<int> a(n);
	FOR(i, 0, n-1)cin >> a[i];

	Heap_Sort(a);

	cout << "����k :";
	int k; cin >> k;
	cout << "�����������������";
	cin >> n;
	vector<int> b(n);
	cout << "�������������\n";
	FOR(i, 0, n - 1)cin >> b[i];
	TOPk(b,k);
}