#include <bits/stdc++.h>
using namespace std;

const int MAXV = 250;
const int MAXE = 30000;
const long long INF = (1LL << 60);

int m, n;
long long a[105], b[105], c[105][105];

int head[MAXV], to[MAXE], nxt[MAXE], pre[MAXV];
long long cap[MAXE], cost[MAXE], dista[MAXV];
bool inq[MAXV];

int tot;
int S, T, V;

void initGraph() {
    memset(head, 0, sizeof(head));
    tot = 1;
}

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

bool spfa() {
    for (int i = 0; i <= V; i++) {
        dista[i] = INF;
        inq[i] = false;
        pre[i] = 0;
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

long long minCostMaxFlow() {
    long long ans = 0;

    while (spfa()) {
        long long flow = INF;

        for (int e = pre[T]; e != 0; e = pre[to[e ^ 1]]) {
            flow = min(flow, cap[e]);
        }

        for (int e = pre[T]; e != 0; e = pre[to[e ^ 1]]) {
            cap[e] -= flow;
            cap[e ^ 1] += flow;
            ans += flow * cost[e];
        }
    }

    return ans;
}

long long solve(int type) {
    initGraph();

    S = 0;
    T = m + n + 1;
    V = T;

    long long sum = 0;
    for (int i = 1; i <= m; i++) {
        sum += a[i];
    }

    for (int i = 1; i <= m; i++) {
        addEdge(S, i, a[i], 0);
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            addEdge(i, m + j, sum, type * c[i][j]);
        }
    }

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

    long long minAns = solve(1);
    long long maxAns = -solve(-1);

    cout << minAns << endl;
    cout << maxAns << endl;

    return 0;
}