#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int rev;
    int cap;
    long long cost;
};

vector<vector<Edge>> g;

void addEdge(int u, int v, int cap, long long cost) {
    Edge a{v, (int)g[v].size(), cap, cost};
    Edge b{u, (int)g[u].size(), 0, -cost};
    g[u].push_back(a);
    g[v].push_back(b);
}

pair<int, long long> maxCostMaxFlow(int S, int T, int need) {
    int n = g.size();
    int flow = 0;
    long long cost = 0;

    const long long NEG = LLONG_MIN / 4;

    while (flow < need) {
        vector<long long> dist(n, NEG);
        vector<int> preV(n, -1);
        vector<int> preE(n, -1);
        vector<int> inq(n, 0);

        queue<int> q;
        dist[S] = 0;
        q.push(S);
        inq[S] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;

            for (int i = 0; i < (int)g[u].size(); i++) {
                Edge &e = g[u][i];

                if (e.cap > 0 && dist[e.to] < dist[u] + e.cost) {
                    dist[e.to] = dist[u] + e.cost;
                    preV[e.to] = u;
                    preE[e.to] = i;

                    if (!inq[e.to]) {
                        inq[e.to] = 1;
                        q.push(e.to);
                    }
                }
            }
        }

        if (dist[T] == NEG) {
            break;
        }

        int add = need - flow;

        for (int v = T; v != S; v = preV[v]) {
            add = min(add, g[preV[v]][preE[v]].cap);
        }

        for (int v = T; v != S; v = preV[v]) {
            Edge &e = g[preV[v]][preE[v]];
            e.cap -= add;
            g[v][e.rev].cap += add;
        }

        flow += add;
        cost += 1LL * add * dist[T];
    }

    return {flow, cost};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    int P, Q;
    cin >> P >> Q;

    int pointCnt = (P + 1) * (Q + 1);
    int S = pointCnt;
    int T = pointCnt + 1;

    g.assign(pointCnt + 2, {});

    auto id = [&](int x, int y) {
        return x * (Q + 1) + y;
    };

    const int INF = 1000000000;

    /*
        前 P + 1 行，每行 Q 个数：
        第 i 行第 j 个表示 (i, j) -> (i, j + 1)
    */
    for (int i = 0; i <= P; i++) {
        for (int j = 0; j < Q; j++) {
            long long w;
            cin >> w;

            addEdge(id(i, j), id(i, j + 1), 1, w);
            addEdge(id(i, j), id(i, j + 1), INF, 0);
        }
    }

    /*
        后 Q + 1 行，每行 P 个数：
        第 i 行第 j 个表示 (j, i) -> (j + 1, i)
    */
    for (int i = 0; i <= Q; i++) {
        for (int j = 0; j < P; j++) {
            long long w;
            cin >> w;

            addEdge(id(j, i), id(j + 1, i), 1, w);
            addEdge(id(j, i), id(j + 1, i), INF, 0);
        }
    }

    int totalRobot = 0;

    for (int i = 0; i < a; i++) {
        int k, x, y;
        cin >> k >> x >> y;

        addEdge(S, id(x, y), k, 0);
        totalRobot += k;
    }

    for (int i = 0; i < b; i++) {
        int r, x, y;
        cin >> r >> x >> y;

        addEdge(id(x, y), T, r, 0);
    }

    pair<int, long long> ans = maxCostMaxFlow(S, T, totalRobot);

    cout << ans.second << '\n';

    return 0;
}