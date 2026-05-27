#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge {
        int to, rev, cap;
    };

    vector<vector<Edge>> g;
    vector<int> level, it;

    void ensure(int v) {
        if (v >= (int)g.size()) g.resize(v + 1);
    }

    void addEdge(int u, int v, int cap) {
        ensure(max(u, v));
        Edge a{v, (int)g[v].size(), cap};
        Edge b{u, (int)g[u].size(), 0};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    bool bfs(int s, int t) {
        level.assign(g.size(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const Edge &e : g[u]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }

        return level[t] != -1;
    }

    int dfs(int u, int t, int f) {
        if (u == t) return f;
        for (int &i = it[u]; i < (int)g[u].size(); ++i) {
            Edge &e = g[u][i];
            if (e.cap <= 0 || level[e.to] != level[u] + 1) continue;

            int ret = dfs(e.to, t, min(f, e.cap));
            if (ret > 0) {
                e.cap -= ret;
                g[e.to][e.rev].cap += ret;
                return ret;
            }
        }
        return 0;
    }

    int maxflow(int s, int t, int limit) {
        int flow = 0;
        while (flow < limit && bfs(s, t)) {
            it.assign(g.size(), 0);
            while (flow < limit) {
                int pushed = dfs(s, t, limit - flow);
                if (!pushed) break;
                flow += pushed;
            }
        }
        return flow;
    }
};

struct DSU {
    vector<int> fa;

    DSU(int n) : fa(n) {
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) fa[a] = b;
    }
};

struct Ship {
    int cap;
    vector<int> route;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    const int EARTH = 0;
    const int MOON = n + 1;
    const int PLACES = n + 2;

    auto convert = [&](int x) {
        return x == -1 ? MOON : x;
    };

    vector<Ship> ships(m);
    DSU dsu(PLACES);

    for (int i = 0; i < m; ++i) {
        int r;
        cin >> ships[i].cap >> r;
        ships[i].route.resize(r);

        for (int j = 0; j < r; ++j) {
            int x;
            cin >> x;
            ships[i].route[j] = convert(x);
        }

        // 同一艘船周期经过的站点，长期看彼此可达，用并查集判断是否有解。
        for (int j = 1; j < r; ++j) {
            dsu.unite(ships[i].route[0], ships[i].route[j]);
        }
    }

    if (dsu.find(EARTH) != dsu.find(MOON)) {
        cout << 0 << '\n';
        return 0;
    }

    const int S = 0;
    const int T = 1;
    const int INF = 1e9;

    auto node = [&](int day, int place) {
        // 0 和 1 留给超级源点、超级汇点。
        return 2 + day * PLACES + place;
    };

    Dinic dinic;
    dinic.addEdge(S, node(0, EARTH), k);

    int arrived = 0;
    for (int day = 1;; ++day) {
        // 人可以在任意站点等待一天。
        for (int place = 0; place < PLACES; ++place) {
            dinic.addEdge(node(day - 1, place), node(day, place), INF);
        }

        // 第 day 天，飞船从上一停靠点开到下一停靠点。
        for (const Ship &ship : ships) {
            int r = (int)ship.route.size();
            int from = ship.route[(day - 1) % r];
            int to = ship.route[day % r];
            dinic.addEdge(node(day - 1, from), node(day, to), ship.cap);
        }

        // 到达这一层月球的人，统一连到汇点统计。
        dinic.addEdge(node(day, MOON), T, INF);

        arrived += dinic.maxflow(S, T, k - arrived);
        if (arrived >= k) {
            cout << day << '\n';
            return 0;
        }
    }
}
