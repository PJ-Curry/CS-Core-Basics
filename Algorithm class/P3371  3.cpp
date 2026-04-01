//Dijkstra算法
#include<bits/stdc++.h>
using namespace std;

// 题目要求的不可达距离：2^31 - 1
const int INF = 2147483647;

struct Edge {
    int to;
    int weight;
};

struct Node {
    int d, u;
    // 小根堆排序：距离小的优先
    bool operator>(const Node& other) const {
        return d > other.d;
    }
};

int main() {
    // 基础加速
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, s;
    cin >> n >> m >> s;

    // 1. 存图：邻接表
    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    // 2. 初始化：所有点设为 INF，起点设为 0
    vector<int> dist(n + 1, INF);
    dist[s] = 0;

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({0, s}); // 发动机启动：起点入队

    // 3. 核心 while 循环
    while (!pq.empty()) {
        Node top = pq.top();
        pq.pop();

        int d = top.d;
        int u = top.u;

        // 验货：如果这个情报比记录的还差，直接扔掉
        if (d > dist[u]) continue;

        // 扫描：看看 u 的邻居们
        for (auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;
            // 松弛操作：如果 经过 u 到 v 更近
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v}); // 发现更优路径，把邻居 v 扔进队列
            }
        }
    }

    // 4. 按格式输出
    for (int i = 1; i <= n; ++i) {
        cout << dist[i] << (i == n ? "" : " ");
    }
    cout << endl;

    return 0;
}