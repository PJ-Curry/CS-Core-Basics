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

long long cap[MAXE];   // 残量网络中的剩余容量
long long d[MAXN];     // 每个点因为下界造成的流量不平衡量

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

        // 原边流量范围是 l <= flow <= r
        // 先强制满足下界 l，剩下可调整容量为 r - l
        addEdge(u, v, r - l);

        // 下界 l 会造成点的流量不平衡
        d[u] -= l;
        d[v] += l;
    }

    // 加一条假边 t -> s，把 s 到 t 的流变成循环流
    int backEdge = addEdge(t, s, INF);

    long long need = 0;

    for (int i = 1; i <= n; i++) {
        if (d[i] > 0) {
            // 流入偏多的点，由超级源点连向它
            addEdge(SS, i, d[i]);
            need += d[i];
        } else if (d[i] < 0) {
            // 流出偏多的点，连向超级汇点
            addEdge(i, TT, -d[i]);
        }
    }

    // 第一次跑最大流：判断是否存在满足上下界的可行流
    S = SS;
    T = TT;

    if (dinic() != need) {
        cout << "N\n";
        return 0;
    }

    // 假边 t -> s 上流过的量，就是当前这组可行 s-t 流的流量
    long long ans = cap[backEdge ^ 1];

    // 删除假边，防止后面退流时直接走这条人工边
    cap[backEdge] = 0;
    cap[backEdge ^ 1] = 0;

    // 最小流：从 t 到 s 跑最大流，能退多少就退多少
    S = t;
    T = s;

    ans -= dinic();

    cout << ans << "\n";

    return 0;
}