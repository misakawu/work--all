#include <iostream>
#include <vector>
using namespace std;
// 二分查找范围[a, b]内的元素，并返回这些元素的下标范围
pair<int, int> binarySearchRange(const vector<int>& arr, int a, int b) {
    int low = 0;
    int high = arr.size() - 1;

    // 查找左边界
    int left = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] >= a) {
            high = mid - 1;
            left = mid;
        }
        else {
            low = mid + 1;
        }
    }

    // 查找右边界
    int right = -1;
    low = 0;
    high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] <= b) {
            low = mid + 1;
            right = mid;
        }
        else {
            high = mid - 1;
        }
    }

    return { left, right };
}

int main() {
    vector<int> arr = { 1, 3, 5, 7, 9, 11, 13 };
    int a = 2;
    int b = 8;

    pair<int, int> result = binarySearchRange(arr, a, b);

    if (result.first != -1 && result.second != -1) {
        cout << "有元素 [" << a << ", " << b << "] are: ";
        for (int i = result.first; i <= result.second; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    else {
        cout << "没有 [" << a << ", " << b << "]." << endl;
    }
    return 0;
}