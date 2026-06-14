#include <bits/stdc++.h>
using namespace std;

const int MAXV = 250;
const int MAXE = 30000;
const long long INF = (1LL << 60);

int m, n;
long long a[105], b[105], c[105][105];

// 链式前向星存图
int head[MAXV], to[MAXE], nxt[MAXE], pre[MAXV];
long long cap[MAXE], cost[MAXE], dista[MAXV];
bool inq[MAXV];

int tot;
int S, T, V;

// 每次求最小费用或最大费用前，都要重新建图
void initGraph() {
    memset(head, 0, sizeof(head));
    tot = 1;
}

// 添加一条容量为 w、费用为 z 的边
// 同时添加一条反向边，用于后续退流
void addEdge(int u, int v, long long w, long long z) {
    to[++tot] = v;
    cap[tot] = w;
    cost[tot] = z;
    nxt[tot] = head[u];
    head[u] = tot;

    to[++tot] = u;
    cap[tot] = 0;
    cost[tot] = -z;
    nxt[tot] = head[v];
    head[v] = tot;
}

// 用 SPFA 在残量网络中寻找一条费用最小的增广路
bool spfa() {
    for (int i = 0; i <= V; i++) {
        dista[i] = INF;
        inq[i] = false;
        pre[i] = 0;      // pre[v] 记录到达 v 的边
    }

    queue<int> q;
    dista[S] = 0;
    q.push(S);
    inq[S] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;

        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];

            // 只有剩余容量大于 0 的边才能走
            if (cap[e] > 0 && dista[v] > dista[u] + cost[e]) {
                dista[v] = dista[u] + cost[e];
                pre[v] = e;

                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }

    return pre[T] != 0;
}

// 不断找最短费用增广路，直到不能再增广
long long minCostMaxFlow() {
    long long ans = 0;

    while (spfa()) {
        long long flow = INF;

        // 先沿着 pre 数组回溯，找这条路上的最小剩余容量
        for (int e = pre[T]; e != 0; e = pre[to[e ^ 1]]) {
            flow = min(flow, cap[e]);
        }

        // 再真正进行增广，并累加费用
        for (int e = pre[T]; e != 0; e = pre[to[e ^ 1]]) {
            cap[e] -= flow;
            cap[e ^ 1] += flow;
            ans += flow * cost[e];
        }
    }

    return ans;
}

// type = 1 时求最小费用
// type = -1 时把费用取反，相当于求最大费用
long long solve(int type) {
    initGraph();

    S = 0;
    T = m + n + 1;
    V = T;

    long long sum = 0;
    for (int i = 1; i <= m; i++) {
        sum += a[i];
    }

    // 源点连每个仓库，容量是仓库的供货量
    for (int i = 1; i <= m; i++) {
        addEdge(S, i, a[i], 0);
    }

    // 每个仓库连每个商店，容量给足够大，费用是单位运输费用
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            addEdge(i, m + j, sum, type * c[i][j]);
        }
    }

    // 每个商店连汇点，容量是商店需求量
    for (int j = 1; j <= n; j++) {
        addEdge(m + j, T, b[j], 0);
    }

    return minCostMaxFlow();
}

int main() {
    cin >> m >> n;

    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }

    for (int j = 1; j <= n; j++) {
        cin >> b[j];
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> c[i][j];
        }
    }

    // 正常费用求最小运输费用
    long long minAns = solve(1);

    // 费用取反后求出来的是“负的最大费用”，所以最后再取反
    long long maxAns = -solve(-1);

    cout << minAns << endl;
    cout << maxAns << endl;

    return 0;
}