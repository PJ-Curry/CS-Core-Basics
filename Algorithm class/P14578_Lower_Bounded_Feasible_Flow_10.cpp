#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXE = 400005;
const long long INF = 4e18;

int n, m;
int S, T;
int cnt = 1;

int head[MAXN], to[MAXE], nxt[MAXE];
int dep[MAXN], cur[MAXN], pos[MAXE];

long long cap[MAXE];   // 边的剩余容量
long long d[MAXN];     // 每个点由下界造成的流量不平衡量
long long low[MAXE];   // 原图每条边的下界

// 加边：每条正向边都要配一条反向边
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

    return p;   // 返回正向边编号，方便最后还原答案
}

// BFS 分层，判断当前残量网络中 S 是否还能到达 T
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

// DFS 沿着分层图推流
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

            cap[i] -= f;       // 正向边剩余容量减少
            cap[i ^ 1] += f;   // 反向边容量增加，表示这条边实际流过了 f
            used += f;

            if (used == flow) {
                break;
            }
        }
    }

    return used;
}

// Dinic 最大流：不断 BFS 分层，然后 DFS 推流
long long dinic() {
    long long ans = 0;

    while (bfs()) {
        // 每一轮分层后，重置当前弧
        for (int i = S; i <= T; i++) {
            cur[i] = head[i];
        }

        // 从源点尽量向汇点推流
        ans += dfs(S, INF);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    S = 0;
    T = n + 1;

    for (int i = 1; i <= m; i++) {
        int u, v;
        long long l, r;
        cin >> u >> v >> l >> r;

        // 原边要求 l <= flow <= r
        // 先强制满足下界 l，剩下可自由调整的容量就是 r - l
        low[i] = l;
        pos[i] = addEdge(u, v, r - l);

        // 记录下界 l 对两个端点造成的流量不平衡
        // u 强制流出 l，所以 d[u] 减少
        // v 强制流入 l，所以 d[v] 增加
        d[u] -= l;
        d[v] += l;
    }

    long long need = 0;

    for (int i = 1; i <= n; i++) {
        if (d[i] > 0) {
            // d[i] > 0 表示该点因下界流量导致流入偏多
            // 从超级源点连向它，用来统一检查这些不平衡量能否被调整
            addEdge(S, i, d[i]);
            need += d[i];
        } else if (d[i] < 0) {
            // d[i] < 0 表示该点因下界流量导致流出偏多
            // 从该点连向超级汇点
            addEdge(i, T, -d[i]);
        }
    }

    // 如果最大流等于需要补平的总量，说明存在满足所有上下界的可行流
    if (dinic() != need) {
        cout << "No\n";
        return 0;
    }

    cout << "Yes\n";

    for (int i = 1; i <= m; i++) {
        // 真实流量 = 下界 + 后续在残量网络中额外流过的量
        // cap[pos[i] ^ 1] 就是第 i 条原边额外流过的量
        cout << low[i] + cap[pos[i] ^ 1] << "\n";
    }

    return 0;
}