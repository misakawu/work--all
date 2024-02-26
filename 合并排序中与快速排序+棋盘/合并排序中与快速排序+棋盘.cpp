#include<iostream>
#include<queue>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<stack>
#include<fstream>
#include <windows.h>　
#include<stdlib.h>
using namespace std;
#define FOR(a,x,y) for(int a=x;a<=y;a++)
#define debug(a) cout<<#a<<": "<<a;

// 重写合并排序算法
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int>  L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// 重写快速排序算法
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int tile=1;
const int MAX_SIZE = 100;
//tr: 棋盘左上角的行坐标
//tc: 棋盘左上角的列坐标
// dr : 特殊方格的行坐标
//dc : 特殊方格的列坐标
//size : 棋盘的大小
//board : 二维数组，表示棋盘的布局
void chessBoardCover(int tr, int tc, int dr, int dc, int size, int board[][MAX_SIZE]) {
    if (size == 1) {
        return;
    }

    int t = tile++;
    int s = size / 2;

    // 左上角区域
    if (dr < tr + s && dc < tc + s) {
        chessBoardCover(tr, tc, dr, dc, s, board);
    }
    else {
        board[tr + s - 1][tc + s - 1] = t;
        chessBoardCover(tr, tc, tr + s - 1, tc + s - 1, s, board);
    }

    // 右上角区域
    if (dr < tr + s && dc >= tc + s) {
        chessBoardCover(tr, tc + s, dr, dc, s, board);
    }
    else {
        board[tr + s - 1][tc + s] = t;
        chessBoardCover(tr, tc + s, tr + s - 1, tc + s, s, board);
    }

    // 左下角区域
    if (dr >= tr + s && dc < tc + s) {
        chessBoardCover(tr + s, tc, dr, dc, s, board);
    }
    else {
        board[tr + s][tc + s - 1] = t;
        chessBoardCover(tr + s, tc, tr + s, tc + s - 1, s, board);
    }

    // 右下角区域
    if (dr >= tr + s && dc >= tc + s) {
        chessBoardCover(tr + s, tc + s, dr, dc, s, board);
    }
    else {
        board[tr + s][tc + s] = t;
        chessBoardCover(tr + s, tc + s, tr + s, tc + s, s, board);
    }
}

int main() {
    printf("输入测试排序数组大小\n");
    int n; cin >> n;
    int l = 1, r = 100;
    int* a = new int[n]; int* b = new int[n];
    int x,y;
    FOR(i, 0, n-1) {
        x = rand();
        y = rand();
        x = (x + l) % r;
        y = (y + l) % r;
        a[i] = x; b[i] = y;
    }

    LARGE_INTEGER t1, t2, tc;
    double time;

    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    quickSort(a, 0, n);
    QueryPerformanceCounter(&t2);
    time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
    printf("快排运行时间为%.6fs\n", time / 10);
    
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    mergeSort(b, 0, n);
    QueryPerformanceCounter(&t2);
    time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
    printf("合并排序运行时间为%.8fs\n", time / 10);
    cout << endl;
    printf("输入测试棋盘大小 (nxn):");
    cin >> n;
    printf("输入测试特殊方块坐标 x y:");
    cin >>x >> y;
    int bord[100][100] = {0};
    bord[x][y] = 0;
    chessBoardCover(1, 1, x, y, n, bord);
    cout << "最佳棋盘覆盖为：(特殊方块为0，相同数字组成一个拼图)\n";
    FOR(i, 1, n) {
        FOR(j, 1, n)
            cout << bord[i][j] << ' ';
        cout << endl;
    }
}