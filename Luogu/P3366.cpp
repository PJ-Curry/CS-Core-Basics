//最小生成树Prim算法(点)
#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> PII;//{距离，点的编号} 点的编号是目的地，要占领的那个新的节点

struct Edge
{
    int to;//目标节点
    int weight;//长度
};

//用邻接表存图
vector<Edge> adj[5005];
bool visited[5005];//记录这个点已经进入了最小生成树
int n,m;

int prim()//小顶堆的优先队列
{
    priority_queue<PII,vector<PII>,greater<PII>>pq;//<类型，容器，比较方式>

    //起点：距离为0 从1号开始
    pq.push({0,1});

    int totalweight=0;
    int count=0;

    while(!pq.empty())
    {
        //1.取出堆顶
        auto[d,u]=pq.top();//结构化绑定
        pq.pop();

        //2.若这个点已经在树里了，跳过
        if(visited[u]) continue;

        //3.标记为已访问，累加权值，计数+1
        visited[u]=true;
        totalweight+=d;
        count++;

        //4.考察这个点的所有邻居，把边扔进堆里
        for(auto& edge:adj[u])//adj[u]中的元素都叫做edge
        {
            int v=edge.to;
            int w=edge.weight;
            if(!visited[v])
            {
                pq.push({w,v});
            }
        }
    }

    if(count==n) return totalweight;
    else return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>n>>m;

    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        //无向图 存双向边
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    int result=prim();
    if(result==-1)
    {
        cout<<"orz"<<endl;
    }
    else
    {
        cout<<result<<endl;
    }
    return 0;
}