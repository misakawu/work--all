#include <iostream>
#include <algorithm>
using namespace std;
int vis[3][45] = { 0 }, c[20] = { 0 }, tot = 0, n; //c[i]表示在i行皇后放置的列的值j，主要为了打印结果;vis[3][]是用来判断的数组，tot存放答案

void pr_cur() {
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < c[i]; j++) cout << '.';
        cout << '#';
        for (int j = c[i] + 1; j < n; j++) cout << '.';
        cout << endl;
     }
    cout << endl;
}

void dfs(int r)
{
    if (r == n) {
        tot++;  //递归边界，走到最后一行说明方案可行，tot++
        pr_cur();
    }
    else for (int i = 0; i < n; i++) {   //在r行逐列尝试放皇后
        if (!vis[0][i] && !vis[1][r + i] && !vis[2][r - i + n]) { //如果(r,i)格子的三个方向都没有皇后
            c[r] = i; //在i列放置皇后，如果不用打印解，可以省略整个c[]
            vis[0][i] = vis[1][r + i] = vis[2][r - i + n] = 1; //标记
            dfs(r + 1);  //向下一行尝试
            vis[0][i] = vis[1][r + i] = vis[2][r - i + n] = 0; //取消标记
        }
    }
}

int main()
{
    cin >> n;
    dfs(0);
    cout << tot << endl;

    return 0;
}
