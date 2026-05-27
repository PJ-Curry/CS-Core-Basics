//Kruskal最小生成树变体 让连通分量个数恰巧=k（即选N-K条边） 代价还要最小
//还用到了并查集
#include<bits/stdc++.h>
using namespace std;
struct Edge{
    int u, v, w;
};

bool compareEdges(const Edge& a, const Edge& b){
    return a.w < b.w;
}

//并查集数组
int parent[1005];

//并查集查找
int find(int i){
    if (parent[i] == i) return i;         //如果上级是我自己，我就是老大
    return parent[i] = find(parent[i]);   //路径压缩 认最终老大当上级
}

int main(){
    int n, m, k;
    if(!(cin >> n >> m >> k)) return 0;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    //1.排序 贪心选择代价最小的边
    sort(edges.begin(), edges.end(), compareEdges);

    //2.初始化并查集
    for (int i = 1; i <= n; i++) parent[i] = i;

    int total_cost = 0;//总代价
    int edge_count = 0;//记录成功合并的次数（裁掉了多少个分支）
    int target = n - k;//需要合并n-k次 来达到k个分量

    //3.Kruskal过程
    for (int i = 0; i < m; i++){
        if (edge_count == target) break;//达到目标

        int rootU = find(edges[i].u);//找到u所在家族老大
        int rootV = find(edges[i].v);//找到v所在家族老大

        if (rootU != rootV){//两个老大不是一个人
            parent[rootU] = rootV;//合并
            total_cost += edges[i].w;
            edge_count++;
        }
    }

    //4.判断是否成功达到目标
    if (edge_count == target){
        cout << total_cost << endl;
    }
    else{
        cout << "No Answer" << endl;
    }
    return 0;
}