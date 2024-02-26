#include<iostream>
using namespace std;

const int MAX = 100;

int rowfind(int a[], int l, int h, int key) {	//在行中查找元素
	int mid = (l + h) / 2;
	if (l == h)
		return a[l] == key;
	else if (key <= a[mid])
		return rowfind(a, l, mid, key);
	else return rowfind(a, mid + 1, h, key);
}
int find(int a[][MAX], int l, int h, int end, int key) {		//在矩阵中查找元素可能所在行
	int mid = (l + h) / 2;
	if (l == h)
		return rowfind(a[l], 0, end, key);
	else if (key >= a[l][0] && key <= a[mid][end])
		return find(a, l, mid, end, key);
	else if (key > a[mid][end] && key <= a[end][end])
		return find(a, mid + 1, h, end, key);
	else return 0;

}
int main() {

	int n = 5;
	int num[MAX][MAX] = { {1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20},{21,22,23,24,25} };
	int key;
	cout << "输入查找数字:";
	cin >> key;
	cout << (find(num, 0, n - 1, n - 1, key) ? "找到" : "未找到") << key << endl;
	key = 14;
	cout << (find(num, 0, n - 1, n - 1, key) ? "找到" : "未找到") << key << endl;
	key = 30;
	cout << (find(num, 0, n - 1, n - 1, key) ? "找到" : "未找到") << key << endl;
	return 0;
}
