#include <iostream>
#include <algorithm>
using namespace std;
int vis[3][45] = { 0 }, c[20] = { 0 }, tot = 0, n; //c[i]��ʾ��i�лʺ���õ��е�ֵj����ҪΪ�˴�ӡ���;vis[3][]�������жϵ����飬tot��Ŵ�

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
        tot++;  //�ݹ�߽磬�ߵ����һ��˵���������У�tot++
        pr_cur();
    }
    else for (int i = 0; i < n; i++) {   //��r�����г��ԷŻʺ�
        if (!vis[0][i] && !vis[1][r + i] && !vis[2][r - i + n]) { //���(r,i)���ӵ���������û�лʺ�
            c[r] = i; //��i�з��ûʺ�������ô�ӡ�⣬����ʡ������c[]
            vis[0][i] = vis[1][r + i] = vis[2][r - i + n] = 1; //���
            dfs(r + 1);  //����һ�г���
            vis[0][i] = vis[1][r + i] = vis[2][r - i + n] = 0; //ȡ�����
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
