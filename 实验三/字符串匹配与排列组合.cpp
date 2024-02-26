#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<vector>
#include<numeric>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ED '\n'
void BF(string a, string b) {
	int n = a.length(), m = b.length();
	int i = 0;
	int maxlen = 0;
	while (i < n) {
		int l = i,r=0;
		while (b[r] == a[l]&&r<m&&l<n) {
			r++, l++;
		}
		maxlen = max(maxlen, r);
		i++;
	}
	cout <<"BF算法：" << a << "和" << b;
	printf("的最长匹配子串长度为%d\n",maxlen);
}

vector<int> getnext(string s) {
	vector<int> next(s.length(),-1);
	int j = 0, k = -1;
	while (j < s.length() - 1) {
		if (k == -1 || s[j] == s[k]) {
			j++, k++;
			next[j] = k;
		}else{
			k=next[k];
		}
	}
	return next;
}

void KMP(string a, string b) {
	int n = a.length(), m = b.length();
	vector<int> next=getnext(b);
	int i = 0, j = 0;
	int maxlen = 0, len = 0;
	while (i < n && j < m) {
		if (j == -1 || a[i] == b[j]) {
			i++, j++;
			if(a[i]==b[j])len++;
			else len = 0;
		}
		else
		{
			len = 0;
			j = next[j];
		}
		maxlen = max(maxlen,len);
	}
	cout <<"KMP算法：" << a << "和" << b << "的匹配字符串长度为" << maxlen << ED;
}


void pr(vector<int> a) {
	if (a.size())
		for (auto i : a)cout << i << ' ';
	else
		cout << "a为空\n";
	cout << ED;
}

void permutate(vector<int> a,int cur) {
	if(cur==a.size()-1)
		pr(a);
	cur++;
	if(cur<a.size())
	FOR(i, 0, cur) {
		swap(a[i], a[cur]);
		permutate(a, cur);
		swap(a[i], a[cur]);
	}
}

void subsets(vector<int> a) {
	cout << "生成子集：空集 ";
	int n = a.size()-1;
	FOR(i, 1, 1 << n+1) {
		FOR(j, 0,  n) 
			if ((i >> j) & 1)
				cout << a[j];
		cout << ' ';
	}
	cout << ED;
}

int main() {
	string fi = "BBABABC";
	string se = "ABAB";

	BF(fi, se);
	KMP(fi, se);

	vector<int> a(5);
	iota(a.begin(), a.end(),1);
	cout << "生成排列：\n";
	permutate(a,0);
	subsets(a);

	return 0;
}