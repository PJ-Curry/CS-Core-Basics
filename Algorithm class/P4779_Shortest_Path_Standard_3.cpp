#include<bits/stdc++.h>
using namespace std;

// 使用 long long 防止距离相加时溢出
typedef long long ll;
const ll INF = 1e18; 

// 定义一个结构体存边：到哪个点，权值是多少
struct Edge {
    int to;
    int weight;
};

// 定义队列里的元素：{距离, 点的编号}
struct Node {
    ll d;
    int u;
    // 重载大于号，让优先队列变成“小根堆”（小的排在最前面）
    bool operator>(const Node& other) const {
        return d > other.d;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, s;
    cin >> n >> m >> s;

    // 邻接表：adj[i] 存的是从点 i 出发的所有边
    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    // 1. 初始化 初始化为最大值
    vector<ll> dist(n + 1, INF);
    dist[s] = 0;

    // 优先队列：每次能自动弹出当前 dist 最小的点
    priority_queue<Node, vector<Node>, greater<Node>> pq;//pq存的不是整张地图 是值得试一试的其他的路
    pq.push({0, s});

    // 2. 核心循环
    while (!pq.empty()) {
        Node top = pq.top();
        pq.pop();

        ll d = top.d;    //从起点到该点的距离
        int u = top.u;   //点的编号 最近的点u

        // 关键：如果弹出的距离已经不是最新的了，说明已经找到过更短的路，跳过
        if (d > dist[u]) continue;

        // 3. 遍历 u 的所有邻居 v
        for (auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;
            // 如果通过 u 走到 v 更近，就更新它
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});//新的距离 新的编号
            }
        }
    }

    // 4. 输出结果
    for (int i = 1; i <= n; ++i) {
        cout << dist[i] << (i == n ? "" : " ");
    }
    cout << endl;

    return 0;
}