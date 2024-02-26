#include<iostream>
#define FLAG 0x80000000 
#define N 1000

using namespace std;

int main()
{
	int r[N], length, i, j;
	cout << "请输入要去除重复元素的数组长度：";
	cin >> length;
	cout << "请输入要去除重复元素的数组元素：";
	for (i = 0; i < length; i++)
		cin >> r[i];
	for (i = 0; i < length - 1; i++)
	{
		if (r[i] != FLAG)
		{
			for (j = i + 1; j < length; j++)
				if (r[j] == r[i]) r[j] = FLAG;
		}
	}
	for (i = 0; r[i] != FLAG; i++); /*找到第一个特殊标记*/
	for (j = i + 1; j < length;) /*删除数列中的特殊标记*/
	{
		if (r[j] != FLAG) r[i++] = r[j++];
		else j++;
	}
	length = i; /*修改删除重复值后的数列的长度*/
	for (i = 0; i < length; i++)
		printf("%-2d", r[i]);

	return 0;
}