#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 5;
int L[MAXN],R[MAXN];
int n;

long long cntPre = 0,cntIn = 0,cntPost = 0;//记录打印了多少个数字 为了打空格

void Pre(int u)
{
    if(u==0) return;
    if(cntPre++) cout<<' ';
    cout<<u;
    Pre(L[u]);
    Pre(R[u]);
}

void In(int u)
{
    if(u==0) return;
    In(L[u]);
    if(cntIn++) cout<<' ';
    cout<<u;
    In(R[u]);
}


void post(int u)
{
    if(u==0) return;
    post(L[u]);
    post(R[u]);
    if(cntPost++) cout<<' ';
    cout<<u;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>L[i]>>R[i];
    }

    int root = 1;
    Pre(root); cout<<'\n';
    In(root); cout<<'\n';
    post(root); cout<<'\n';
    return 0;
}