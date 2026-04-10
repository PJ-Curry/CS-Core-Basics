//Kruskal算法 并查集的应用
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 定义边的结构体
struct Edge {
    int u, v, w;
};

// 排序规则：按权值从小到大排序
bool compareEdges(const Edge& a, const Edge& b) {
    return a.w < b.w;
}

// 并查集结构
struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]); // 路径压缩
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

int main() {
    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<Edge> edges(k);
    long long totalWeight = 0;
    for (int i = 0; i < k; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        totalWeight += edges[i].w; // 累计总权重
    }

    // 1. 按权重升序排列
    sort(edges.begin(), edges.end(), compareEdges);

    // 2. 运行 Kruskal 算法求最小生成森林的权重
    DSU dsu(n);
    long long mstWeight = 0;
    for (int i = 0; i < k; ++i) {
        // 如果连接成功，说明这条边是 MST 的一部分
        if (dsu.unite(edges[i].u, edges[i].v)) {
            mstWeight += edges[i].w;
        }
    }

    // 3. 结果 = 总权重 - 留下来的最小权重
    cout << totalWeight - mstWeight << endl;

    return 0;
}