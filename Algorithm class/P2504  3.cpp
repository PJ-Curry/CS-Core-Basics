#include<bits/stdc++.h>
using namespace std;

//树的坐标结构
struct Point{
    int x, y;
};

//边结构
struct Edge{
    int u, v;
    double w;
};

bool compareEdges(const Edge& a, const Edge& b){
    return a.w < b.w;
}

int parent[1005];//并查集数组

int find(int i){
    if(parent[i] == i) return i;
    return parent[i] = find(parent[i]);
}

double getDist(Point a, Point b){
   return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main(){
    //1.读入猴子数据
    int m;
    cin >> m;
    vector<int> monkey_jumps(m);
    for(int i = 0; i < m; i++){
        cin >> monkey_jumps[i];
    }

    //2.读入树的数据
    int n;
    cin >> n;
    vector<Point> trees(n);
    for(int i = 0; i < n; i++){
        cin >> trees[i].x >> trees[i].y;
    }

    //3.构建所有可能的边
    vector<Edge> all_edges;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            all_edges.push_back({i, j, getDist(trees[i], trees[j])});
        }
    }

    //4.Kruskal最小生成树
    sort(all_edges.begin(), all_edges.end(), compareEdges);
    for(int i = 1; i < n; i++) parent[i] = i;//初始化
    double max_mst_edge = 0;
    int edge_count = 0;//连通的边的数量
    for(auto& edge : all_edges){
        int rootU = find(edge.u);
        int rootV = find(edge.v);
        if(rootU != rootV){
            parent[rootU] = rootV;
            max_mst_edge = max(max_mst_edge, edge.w);
            edge_count++;

            if(edge_count == n - 1) break;
        }
    }

    //5.最后和猴子的能力做比较
    int ans = 0;
    for(int jump : monkey_jumps){
        if((double)jump >= max_mst_edge){
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}