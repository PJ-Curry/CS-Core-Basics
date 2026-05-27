#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    long long cap;  // 容量
    long long cost; // 单位流量费用
    int rev;        // 反向边索引
};

vector<vector<Edge>> G;
vector<long long> dist; // 记录源点到各点的最小单位费用
vector<int> edge_from;  // 记录路径：当前点是从哪个点来的
vector<int> edge_idx;   // 记录路径：当前点是通过哪条边来的

// 使用 SPFA 寻找费用最短路（即单位费用总和最小的增广路）
bool spfa(int s, int t, long long &flow, long long &cost) {
    dist.assign(G.size(), INF);
    vector<bool> in_que(G.size(), false);
    vector<long long> min_cap(G.size(), INF); // 记录路径上的瓶颈容量

    dist[s] = 0;
    queue<int> que;
    que.push(s);
    in_que[s] = true;

    while (!que.empty()) {
        int u = que.front(); que.pop();
        in_que[u] = false;

        for (int i = 0; i < G[u].size(); ++i) {
            Edge &e = G[u][i];
            // 如果还有容量，且能通过这条边缩短费用总和（松弛操作）
            if (e.cap > 0 && dist[e.to] > dist[u] + e.cost) {
                dist[e.to] = dist[u] + e.cost;
                edge_from[e.to] = u;
                edge_idx[e.to] = i;
                min_cap[e.to] = min(min_cap[u], e.cap);
                if (!in_que[e.to]) {
                    que.push(e.to);
                    in_que[e.to] = true;
                }
            }
        }
    }

    if (dist[t] == INF) return false; // 找不到增广路了

    // 找到一条增广路，更新流量和总费用
    flow += min_cap[t];
    cost += min_cap[t] * dist[t];

    // 顺着路径回溯，更新残量网络
    int curr = t;
    while (curr != s) {
        int prev = edge_from[curr];
        int idx = edge_idx[curr];
        G[prev][idx].cap -= min_cap[t];
        G[curr][G[prev][idx].rev].cap += min_cap[t];
        curr = prev;
    }

    return true;
}

int main() {
    int n, m, s, t;
    if (!(cin >> n >> m >> s >> t)) return 0;

    G.resize(n + 1);
    edge_from.resize(n + 1);
    edge_idx.resize(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w, c;
        cin >> u >> v >> w >> c;
        // 正向边：容量 w，费用 c
        G[u].push_back({v, w, c, (int)G[v].size()});
        // 反向边：容量 0，费用 -c (退费机制)
        G[v].push_back({u, 0, -c, (int)G[u].size() - 1});
    }

    long long max_flow = 0;
    long long min_cost = 0;

    // 只要还能找到最短费用路径，就一直增广
    while (spfa(s, t, max_flow, min_cost));

    cout << max_flow << " " << min_cost << endl;

    return 0;
}