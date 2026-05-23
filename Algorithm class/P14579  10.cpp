#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXE = 400005;
const long long INF = 4e18;

int n, m, s, t;
int S, T;
int cnt = 1;

int head[MAXN], to[MAXE], nxt[MAXE];
int dep[MAXN], cur[MAXN];

long long cap[MAXE];
long long d[MAXN];

// 加边：正向边容量为 c，反向边初始容量为 0
int addEdge(int u, int v, long long c) {
    int p = ++cnt;

    to[p] = v;
    cap[p] = c;
    nxt[p] = head[u];
    head[u] = p;

    to[++cnt] = u;
    cap[cnt] = 0;
    nxt[cnt] = head[v];
    head[v] = cnt;

    return p;
}

// BFS 分层
bool bfs() {
    memset(dep, -1, sizeof(dep));

    queue<int> q;
    dep[S] = 0;
    q.push(S);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];

            if (cap[i] > 0 && dep[v] == -1) {
                dep[v] = dep[u] + 1;
                q.push(v);
            }
        }
    }

    return dep[T] != -1;
}

// DFS 推流
long long dfs(int u, long long flow) {
    if (u == T || flow == 0) {
        return flow;
    }

    long long used = 0;

    for (int &i = cur[u]; i; i = nxt[i]) {
        int v = to[i];

        if (cap[i] > 0 && dep[v] == dep[u] + 1) {
            long long f = dfs(v, min(flow - used, cap[i]));

            if (f == 0) {
                continue;
            }

            cap[i] -= f;
            cap[i ^ 1] += f;
            used += f;

            if (used == flow) {
                break;
            }
        }
    }

    return used;
}

// Dinic 最大流
long long dinic() {
    long long ans = 0;

    while (bfs()) {
        for (int i = 0; i <= n + 1; i++) {
            cur[i] = head[i];
        }

        ans += dfs(S, INF);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s >> t;

    int SS = 0;
    int TT = n + 1;

    for (int i = 1; i <= m; i++) {
        int u, v;
        long long l, r;
        cin >> u >> v >> l >> r;

        // 原边要求 l <= flow <= r
        // 先满足下界 l，剩余可调整容量为 r - l
        addEdge(u, v, r - l);

        // 记录下界流量造成的点不平衡
        d[u] -= l;
        d[v] += l;
    }

    // 关键：加一条 t -> s 的人工边，把 s-t 流变成循环流
    int backEdge = addEdge(t, s, INF);

    long long need = 0;

    for (int i = 1; i <= n; i++) {
        if (d[i] > 0) {
            // 该点下界流入偏多，需要通过残量网络送出去
            addEdge(SS, i, d[i]);
            need += d[i];
        } else if (d[i] < 0) {
            // 该点下界流出偏多，需要补回来
            addEdge(i, TT, -d[i]);
        }
    }

    // 第一次 Dinic：判断是否存在满足上下界的可行 s-t 流
    S = SS;
    T = TT;

    if (dinic() != need) {
        cout << "N\n";
        return 0;
    }

    // 人工边 t -> s 上已经流过的量，就是当前可行流的流量
    long long ans = cap[backEdge ^ 1];

    // 删除人工边，避免第二次最大流时继续走这条假边
    cap[backEdge] = 0;
    cap[backEdge ^ 1] = 0;

    // 第二次 Dinic：在当前残量网络中继续从 s 到 t 增广
    S = s;
    T = t;

    ans += dinic();

    cout << ans << "\n";

    return 0;
}