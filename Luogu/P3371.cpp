#include<bits/stdc++.h>
using namespace std;

const int INF = 2147483647;

// 定义边的结构体
struct Edge {
    int to;
    int weight;
};

// 定义优先队列中存储的元素类型：pair<距离, 节点编号>
// 使用 pair 是因为它可以自然比较大小，first 为距离，second 为节点 ID
typedef pair<int, int> pii;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, s;
    if (!(cin >> n >> m >> s)) return 0;

    // 使用邻接表存储图
    // n 的最大值为 10000，vector 开稍微大一点
    vector<vector<Edge>> adj(n + 1);

    for (int i = 0; i < m; ++i) 
    {
        int u, v, w;
        cin >> u >> v >> w;
        // 有向图，直接添加
        adj[u].push_back({v, w});
    }

    // dist 数组存储最短路结果，初始化为 INF
    vector<int> dist(n + 1, INF);
    // visited 数组标记节点是否已经确定了最短路
    vector<bool> visited(n + 1, false);

    // 小根堆：距离更小的排在前面
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    // 初始化起点
    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) 
    {
        // 取出当前距离起点最近的节点
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // 如果该节点已经被处理过（说明之前有更短的路径已经将其弹出并处理了），则跳过
        // 这是堆优化 Dijkstra 的关键剪枝
        if (visited[u]) continue;
        visited[u] = true;

        // 遍历所有从 u 出发的边
        for (const auto& edge : adj[u]) 
        {
            int v = edge.to;
            int w = edge.weight;

            // 松弛操作：如果通过 u 到 v 更近
            if (dist[u] + w < dist[v]) 
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    // 输出结果
    for (int i = 1; i <= n; ++i) 
    {
        cout << dist[i] << (i == n ? "" : " ");
    }
    cout << endl;

    return 0;
}