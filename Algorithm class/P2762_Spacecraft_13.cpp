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

            if (edge[i].cap > 0 && dep[v] == 0) {
                dep[v] = dep[u] + 1;
                q.push(v);
            }
        }
    }

    return dep[T] != 0;
}

long long dfs(int u, long long flow) {
    if (u == T) return flow;

    long long used = 0;

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

        addEdge(S, i, p[i]);

        string line;
        getline(cin, line);

        stringstream ss(line);
        int tool;

        while (ss >> tool) {
            addEdge(i, m + tool, INF);
        }
    }

    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        addEdge(m + i, T, c[i]);
    }

    long long minCut = dinic();
    long long ans = sumProfit - minCut;

    findChoose(S);

    bool first = true;

    for (int i = 1; i <= m; i++) {
        if (vis[i]) {
            if (!first) cout << " ";
            cout << i;
            first = false;
        }
    }
    cout << endl;

    first = true;

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