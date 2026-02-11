#include<bits/stdc++.h>
using namespace std;
int main()
{
    int prev[100005],next[100005];
    bool removed[100005];
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;

    //初始化 head=1
    int head=1;

    for(int i=2;i<=n;i++)
    {
        int k,p;
        cin>>k>>p;

        if(p==0)//0表示插在第k号同学左边
        {
            int pk=prev[k];//pk=k左边的同学

            //建立新的i与前后之间的链接 这两行
            next[i]=k;//i在k左边儿 所以i的右边是k
            prev[i]=pk;//i的左边是原来k的左边 因为是往里插的

            //这里是原先的两个节点和新节点建立连接 一个是k的pre 一个是pk的next 合理！！！
            prev[k]=i;//现在k的左边是i 类比链表中的断链 插入 然后再缝合的过程
            if(pk!=0) next[pk]=i;
            else head=i;
        }
        else
        {
            int nk=next[k];

            prev[i]=k;
            next[i]=nk;

            next[k]=i;
            if(nk!=0) prev[nk]=i;
        }
    }

    int m;
    cin>>m;
    while(m--)
    {
        int x;
        cin>>x;
        removed[x]=true;//只做标记不断链 最后输出只要输出没标记到的就可以了
    }

    for(int i=head;i!=0;i=next[i])
    {
        if(!removed[i]) cout<<i<<" ";
    }
    return 0;
}