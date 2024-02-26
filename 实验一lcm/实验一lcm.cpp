// 实验一lcm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<stdio.h>
#include<Windows.h>
using namespace std;

int GCD1(int a, int b) {
    if (b == 0)return a;
    else return GCD1(b, a % b);
}
int GCD2(int a, int b) {
    if (b == 0)return a;
    else {
        while (a - b >= 0)a -= b;
        return GCD2(b, a);
    }
}
int GCD3(int a, int b) {
    for (int i = 2; i <= min(a, b); i++)
        if (a % i == 0 && b % i == 0)
            return i;
}

int main() {
    int a, b;
    cout << "输入两个整数：";
    cin >> a >> b;
    LARGE_INTEGER t1, t2,t;

    QueryPerformanceFrequency(&t);

    QueryPerformanceCounter(&t1);
    int c1 =GCD1(max(a, b), min(a, b));
    QueryPerformanceCounter(&t2);

    cout << a << "和" << b << "的最大公约数\n";
    cout <<"除余法递推法:" << c1 << endl;
    cout << "运行时间：" << (t2.QuadPart - t1.QuadPart)/(double)t.QuadPart*1000<<"ms" << endl;

    
    QueryPerformanceCounter(&t1);
    int c2 = GCD2(max(a, b), min(a, b));
    QueryPerformanceCounter(&t2);
    cout <<"相减法递推法:" << c2 << endl;
    cout << "运行时间：" << (t2.QuadPart - t1.QuadPart) / (double)t.QuadPart * 1000 << "ms" << endl;

    QueryPerformanceCounter(&t1);
    int c3 = GCD3(max(a, b), min(a, b));
    QueryPerformanceCounter(&t2);
    cout <<"穷举法:" << c3 << endl;
    cout<<"运行时间："<< (t2.QuadPart - t1.QuadPart) / (double)t.QuadPart * 1000 << "ms" << endl;
}   
