#include <bits/stdc++.h>
using namespace std;

const int MAXN = 120;
const int MAXE = 10000;
const long long INF = (1LL << 60);

struct Edge {
    int to, next;
    long long cap;
};

Edge edge[MAXE];
int head[MAXN], cur[MAXN], dep[MAXN];
int tot = 1;

int m, n;
int S, T;
long long p[55], c[55];
bool vis[MAXN];

// Dinic 加边，正向边有容量，反向边初始容量为 0
void addEdge(int u, int v, long long w) {
    edge[++tot].to = v;
    edge[tot].cap = w;
    edge[tot].next = head[u];
    head[u] = tot;

    edge[++tot].to = u;
    edge[tot].cap = 0;
    edge[tot].next = head[v];
    head[v] = tot;
}

// BFS 建立分层图
// dep[x] 表示点 x 在分层图中的层数
bool bfs() {
    memset(dep, 0, sizeof(dep));
    queue<int> q;

    dep[S] = 1;
    q.push(S);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = head[u]; i; i = edge[i].next) {
            int v = edge[i].to;

            // 只有还有容量的边才能走
            if (edge[i].cap > 0 && dep[v] == 0) {
                dep[v] = dep[u] + 1;
                q.push(v);
            }
        }
    }

    return dep[T] != 0;
}

// 在分层图上 DFS 增广
long long dfs(int u, long long flow) {
    if (u == T) return flow;

    long long used = 0;

    // cur[u] 是当前弧优化，避免重复扫描无用边
    for (int &i = cur[u]; i; i = edge[i].next) {
        int v = edge[i].to;

        if (edge[i].cap > 0 && dep[v] == dep[u] + 1) {
            long long f = dfs(v, min(flow - used, edge[i].cap));

            if (f > 0) {
                edge[i].cap -= f;
                edge[i ^ 1].cap += f;
                used += f;

                if (used == flow) return used;
            }
        }
    }

    return used;
}

// Dinic 求最大流，也就是这个模型中的最小割
long long dinic() {
    long long maxflow = 0;

    while (bfs()) {
        for (int i = 0; i <= T; i++) {
            cur[i] = head[i];
        }

        while (true) {
            long long f = dfs(S, INF);
            if (f == 0) break;
            maxflow += f;
        }
    }

    return maxflow;
}

// 最大流结束后，在残量网络中从源点还能走到的点
// 就是最终被选择的实验和仪器
void findChoose(int u) {
    vis[u] = true;

    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;

        if (edge[i].cap > 0 && !vis[v]) {
            findChoose(v);
        }
    }
}

int main() {
    cin >> m >> n;

    S = 0;
    T = m + n + 1;

    long long sumProfit = 0;

    for (int i = 1; i <= m; i++) {
        cin >> p[i];
        sumProfit += p[i];

        // 源点连实验，容量为实验收益
        // 如果割掉这条边，相当于放弃这个实验的收益
        addEdge(S, i, p[i]);

        string line;
        getline(cin, line);

        stringstream ss(line);
        int tool;

        // 实验连它需要的仪器，容量为 INF
        // 意思是：选了实验，就必须选择对应仪器
        while (ss >> tool) {
            addEdge(i, m + tool, INF);
        }
    }

    for (int i = 1; i <= n; i++) {
        cin >> c[i];

        // 仪器连汇点，容量为仪器费用
        // 如果割掉这条边，相当于支付这个仪器的配置费用
        addEdge(m + i, T, c[i]);
    }

    // 最小割 = 损失的收益 + 支付的费用
    long long minCut = dinic();

    // 最大净收益 = 所有实验收益 - 最小割
    long long ans = sumProfit - minCut;

    // 找出最终选择的实验和仪器
    findChoose(S);

    bool first = true;

    // 输出被选择的实验编号
    for (int i = 1; i <= m; i++) {
        if (vis[i]) {
            if (!first) cout << " ";
            cout << i;
            first = false;
        }
    }
    cout << endl;

    first = true;

    // 输出被选择的仪器编号
    for (int i = 1; i <= n; i++) {
        if (vis[m + i]) {
            if (!first) cout << " ";
            cout << i;
            first = false;
        }
    }
    cout << endl;

    cout << ans << endl;

    return 0;
}