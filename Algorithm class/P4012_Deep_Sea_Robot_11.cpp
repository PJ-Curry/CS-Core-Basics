#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct MaxCostMaxFlow {
    struct Edge {
        int to, rev;
        ll cap, cost;
    };

    int n;
    vector<vector<Edge>> g;

    MaxCostMaxFlow(int n) : n(n), g(n) {}

    void addEdge(int u, int v, ll cap, ll cost) {
        Edge a{v, (int)g[v].size(), cap, cost};
        Edge b{u, (int)g[u].size(), 0, -cost};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    pair<ll, ll> solve(int s, int t) {
        const ll NEG = LLONG_MIN / 4;
        ll flow = 0, cost = 0;
        vector<ll> dist(n);
        vector<int> inq(n), pv(n), pe(n);

        while (true) {
            fill(dist.begin(), dist.end(), NEG);
            fill(inq.begin(), inq.end(), 0);
            queue<int> q;
            dist[s] = 0;
            q.push(s);
            inq[s] = 1;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                inq[u] = 0;

                for (int i = 0; i < (int)g[u].size(); ++i) {
                    Edge &e = g[u][i];
                    if (e.cap <= 0) continue;
                    if (dist[e.to] < dist[u] + e.cost) {
                        dist[e.to] = dist[u] + e.cost;
                        pv[e.to] = u;
                        pe[e.to] = i;
                        if (!inq[e.to]) {
                            inq[e.to] = 1;
                            q.push(e.to);
                        }
                    }
                }
            }

            if (dist[t] == NEG) break;

            ll aug = LLONG_MAX / 4;
            for (int v = t; v != s; v = pv[v]) {
                aug = min(aug, g[pv[v]][pe[v]].cap);
            }
            for (int v = t; v != s; v = pv[v]) {
                Edge &e = g[pv[v]][pe[v]];
                e.cap -= aug;
                g[v][e.rev].cap += aug;
            }

            flow += aug;
            cost += aug * dist[t];
        }

        return {flow, cost};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    int P, Q;
    cin >> P >> Q;

    auto id = [&](int y, int x) {
        return y * (Q + 1) + x;
    };

    int nodeCount = (P + 1) * (Q + 1);
    int S = nodeCount;
    int T = nodeCount + 1;
    MaxCostMaxFlow mf(nodeCount + 2);

    const ll INF = (ll)4e18;

    // 向东走的边：(x, y) -> (x + 1, y)。
    for (int y = 0; y <= P; ++y) {
        for (int x = 0; x < Q; ++x) {
            ll w;
            cin >> w;

            // 第一台经过这条边的机器人可以采到标本，获得价值 w。
            mf.addEdge(id(y, x), id(y, x + 1), 1, w);
            // 后面的机器人仍然可以通过，但标本已经被采走，收益为 0。
            mf.addEdge(id(y, x), id(y, x + 1), INF, 0);
        }
    }

    // 向北走的边：(x, y) -> (x, y + 1)。
    for (int x = 0; x <= Q; ++x) {
        for (int y = 0; y < P; ++y) {
            ll w;
            cin >> w;
            mf.addEdge(id(y, x), id(y + 1, x), 1, w);
            mf.addEdge(id(y, x), id(y + 1, x), INF, 0);
        }
    }

    for (int i = 0; i < a; ++i) {
        ll k;
        int x, y;
        cin >> k >> x >> y;
        mf.addEdge(S, id(y, x), k, 0);
    }

    for (int i = 0; i < b; ++i) {
        ll r;
        int x, y;
        cin >> r >> x >> y;
        mf.addEdge(id(y, x), T, r, 0);
    }

    cout << mf.solve(S, T).second << '\n';
    return 0;
}
