//高精度加法
#include<iostream>
#include<string>
#include<algorithm>
#define maxn 520
using namespace std;
int a[maxn],b[maxn],c[maxn];
int main()
{
    string s1,s2;
    cin>>s1;
    cin>>s2;
    int len = max(s1.length(),s2.length());
    for(int i = s1.length() - 1,j = 1;i >= 0;i--,j++)
    {
        a[j] = s1[i] - '0';
    }
    for(int i = s2.length() - 1,j = 1;i >= 0;i--,j++)
    {
        b[j] = s2[i] - '0';//倒序
    }
    for(int i=1;i<=len;i++)
    {
        c[i] += a[i] + b[i];
        c[i+1] += c[i] / 10;
        c[i] %= 10;
    }
    if(c[len+1]) len++;//考虑进位
    for(int i=len;i>=1;i--)
    {
        cout<<c[i];
    }
    return 0;
}