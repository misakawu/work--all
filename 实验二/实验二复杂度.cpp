#include <iostream>
#include<stdio.h>
#include<Windows.h>
#include<vector>
#include<random>
using namespace std;

#define debug(x) cout<<#x<<"的值为："<<x<<endl;

LARGE_INTEGER t1, t2, tc;

vector<vector<int>> random_data(int k, int m) {
	vector<vector<int>> ans;
	for (int i = 0; i < k; i++)
	{
		vector<int> tem;
		for (int j = 0; j < m; j++)
			tem.push_back(rand());
		ans.push_back(tem);
	}
	return ans;
}

vector<double> sort1(vector<vector<int>> a) {
	int n = a.size();
	int m = a[0].size();
	QueryPerformanceFrequency(&tc);
	vector<double> rt;
	for (int i = 0; i < n; i++){
		QueryPerformanceCounter(&t1);
		for (int j = 0; j < m; j++){
			int max = 0;
			for (int k = j; k < m - j; k++)
				if (a[i][k] > a[i][max])
					max = k;
				swap(a[i][j], a[i][max]);
				
		}
		QueryPerformanceCounter(&t2);
		double times = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
		rt.push_back(times);
		printf("第%d次冒泡排序耗时%f\n",i + 1, times);
	}
	return rt;
}


void qsort(vector<int>& arr, int left, int right) {
	int i = left, j = right;
	int pivot = arr[(left + right) / 2];

	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	};

	if (left < j)
		qsort(arr, left, j);
	if (i < right)
		qsort(arr, i, right);
}
vector<double> sort2(vector<vector<int>> a) {
	int k = a.size();
	int m = a[0].size();
	vector<double> rt;
	QueryPerformanceFrequency(&tc);

	for (int i = 0; i < k; i++) {
		QueryPerformanceCounter(&t1);
		qsort(a[i], 0, m - 1);
		QueryPerformanceCounter(&t2);
		rt.push_back((double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart);
	}

	return rt;
}

void adjust(vector<int>& nums, int i, int n) {
	// i为待调整的节点，n为nums数组元素的个数，从上往下调整
	int j = 2 * i + 1; // 左子节点
	while (j < n) {
		if (j + 1 < n && nums[j + 1] > nums[j]) j++;  // 比较左右孩子谁更大
		if (nums[j] < nums[i])   break;  // 都比父节点小就停止
		else {
			swap(nums[i], nums[j]);
			i = j;   // 继续往下调整
			j = 2 * i + 1;
		}
	}
}

void hsort(vector<int>& nums) {
	int n = nums.size();
	for (int i = n / 2 - 1; i >= 0; i--) {  // 从第一个非叶子节点开始（从下往上看第一个）
		adjust(nums, i, n);
	}
	for (int i = n - 1; i >= 1; i--) {
		swap(nums[0], nums[i]);   // 交换堆顶和最末一个元素
		adjust(nums, 0, i);  // 将最末一个元素去除，再进行调整
	}
}

vector<double> sort3(vector<vector<int>> a) {
	int n = a.size();
	int m = a[0].size();
	vector<double> rt;
	QueryPerformanceFrequency(&tc);
	for (int i = 0; i < n; i++) {
		QueryPerformanceCounter(&t1);
		hsort(a[i]);
		QueryPerformanceCounter(&t2);
		rt.push_back((double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart);
	}
	return rt;
}

int main() {
	vector<vector<int>> data;
	int k = 5, m = 5000;
	double time = 0;
	data = random_data(k, m);//生成k*m数组
	cout << "数据生成完毕，测试数据为" << k << '*' << m << "的数组\n";

	vector<double> d1, d2, d3;
	d1 = sort2(data);//快速排序
	double sum = 0;
	for (double i : d1)
		sum += i;
	sum /= d1.size();
	printf("快排平均时间%f \n", sum);
	sum = 0;

	d2 = sort3(data);//堆排序
	for (double i : d2)
		sum += i;
	sum /= d1.size();
	printf("堆排平均时间%f \n", sum);
	sum = 0;

	d3 = sort1(data);//冒泡
	for (double i : d3)
		sum += i;
	sum /= d1.size();
	printf("冒泡平均时间%f \n", sum);
	sum = 0;

	return 0;
}