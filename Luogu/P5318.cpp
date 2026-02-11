#include<bits/stdc++.h>
using namespace std;

const int MAXN=100005;

vector<int> adj[MAXN];

bool visited[MAXN];
int n,m;

//DFS 深度优先
void dfs(int u)
{
    visited[u]=true;//标记为已访问过
    cout<<u<<" ";

    for(int v:adj[u])
    {
        if(!visited[v])
        {
            dfs(v);//递归深入
        }
    }
}

//BFS 广度优先
void bfs(int start)
{
    memset(visited,0,sizeof(visited));//清空visited数组 因为DFS用过了
    //用队列
    queue<int> q;
    q.push(start);
    visited[start]=true;

    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        cout<<u<<" ";

        for(int v:adj[u])
        {
            if(!visited[v])
            {
                visited[v]=true;
                q.push(v);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>n>>m;

    for(int i=0;i<m;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);//有向图 u指向v
    }

    //排序 编号较小的优先
    for(int i=1;i<=n;i++)
    {
        sort(adj[i].begin(),adj[i].end());
    }

    //执行DFS
    memset(visited,0,sizeof(visited));//初始化
    dfs(1);
    cout<<endl;

    bfs(1);
    cout<<endl;

    return 0;
}