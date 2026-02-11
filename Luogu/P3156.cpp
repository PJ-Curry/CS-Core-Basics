#include<iostream>
#include<vector>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);  // 关闭 iostream 与 stdio 的同步
    cin.tie(nullptr);             // 解除 cin 与 cout 的绑定，加快输入输出
    int n,m;
    cin>>n>>m;
    vector<int>xuehao(n);
    vector<int>xunwen(m);
    for(int i=1;i<=n;i++)
    {
        cin>>xuehao[i];
    }
    for(int j=1;j<=m;j++)
    {
        cin>>xunwen[j];
    }
    for(int k=1;k<=m;k++)
    {
        cout<<xuehao[xunwen[k]]<<endl;
    }
}