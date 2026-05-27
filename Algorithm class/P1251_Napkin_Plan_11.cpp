#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct MinCostMaxFlow {
    struct Edge {
        int to, rev;
        ll cap, cost;
    };

    int n;
    vector<vector<Edge>> g;

    MinCostMaxFlow(int n) : n(n), g(n + 1) {}

    void addEdge(int u, int v, ll cap, ll cost) {
        Edge a{v, (int)g[v].size(), cap, cost};
        Edge b{u, (int)g[u].size(), 0, -cost};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    pair<ll, ll> solve(int s, int t, ll need) {
        const ll INF = LLONG_MAX / 4;
        ll flow = 0, cost = 0;
        vector<ll> h(n + 1, 0), dist(n + 1);
        vector<int> pv(n + 1), pe(n + 1);

        while (flow < need) {
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
            pq.push({0, s});

            while (!pq.empty()) {
                pair<ll, int> cur = pq.top();
                pq.pop();
                ll d = cur.first;
                int u = cur.second;
                if (d != dist[u]) continue;

                for (int i = 0; i < (int)g[u].size(); ++i) {
                    Edge &e = g[u][i];
                    if (e.cap <= 0) continue;

                    // 用势能维护非负边权，这样即使有反向边也能跑 Dijkstra。
                    ll nd = d + e.cost + h[u] - h[e.to];
                    if (nd < dist[e.to]) {
                        dist[e.to] = nd;
                        pv[e.to] = u;
                        pe[e.to] = i;
                        pq.push({nd, e.to});
                    }
                }
            }

            if (dist[t] == INF) break;
            for (int i = 1; i <= n; ++i) {
                if (dist[i] < INF) h[i] += dist[i];
            }

            ll aug = need - flow;
            for (int v = t; v != s; v = pv[v]) {
                aug = min(aug, g[pv[v]][pe[v]].cap);
            }
            for (int v = t; v != s; v = pv[v]) {
                Edge &e = g[pv[v]][pe[v]];
                e.cap -= aug;
                g[v][e.rev].cap += aug;
            }

            flow += aug;
            cost += aug * h[t];
        }

        return {flow, cost};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<ll> r(N + 1);
    ll totalNeed = 0;
    for (int i = 1; i <= N; ++i) {
        cin >> r[i];
        totalNeed += r[i];
    }

    ll p, f, s;
    int m, slowDays;
    cin >> p >> m >> f >> slowDays >> s;

    auto dirty = [&](int day) { return day; };
    auto clean = [&](int day) { return N + day; };

    int S = 2 * N + 1;
    int T = 2 * N + 2;
    MinCostMaxFlow mf(T);

    const ll INF_CAP = (ll)4e18;

    for (int i = 1; i <= N; ++i) {
        // 第 i 天结束后，最多会产生 r[i] 条脏餐巾。
        mf.addEdge(S, dirty(i), r[i], 0);

        // 第 i 天必须拿到 r[i] 条干净餐巾。
        mf.addEdge(clean(i), T, r[i], 0);

        // 直接购买新餐巾，花费为 p。
        mf.addEdge(S, clean(i), INF_CAP, p);

        // 脏餐巾可以先存着，留到后面再洗。
        if (i < N) mf.addEdge(dirty(i), dirty(i + 1), INF_CAP, 0);

        // 快洗：第 i 天送洗，第 i + m 天可用。
        if (i + m <= N) mf.addEdge(dirty(i), clean(i + m), INF_CAP, f);

        // 慢洗：第 i 天送洗，第 i + slowDays 天可用。
        if (i + slowDays <= N) mf.addEdge(dirty(i), clean(i + slowDays), INF_CAP, s);
    }

    cout << mf.solve(S, T, totalNeed).second << '\n';
    return 0;
}
