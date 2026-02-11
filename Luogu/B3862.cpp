#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

//建立反向图的邻接表
vector<int> adj[MAXN];//反向的输入数组
int ans[MAXN];//存储到这里 最后的输出结果

//深度优先搜索
void dfs(int u,int max_node)//u当前所在节点 max_node这一轮最大开始的节点
{
    ans[u]=max_node;
    for(int v:adj[u])
    {
        if(ans[v]==0)
        {
            dfs(v,max_node);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        //建立反边
        adj[v].push_back(u);
    }

    //从最大的N点遍历到1 反向遍历
    for(int i=n;i>=1;i--)
    {
        if(ans[i]==0)
        {
            dfs(i,i);
        }
    }

    for(int i=1;i<=n;i++)
    {
        cout<<ans[i]<<" ";
    }
    return 0;
}