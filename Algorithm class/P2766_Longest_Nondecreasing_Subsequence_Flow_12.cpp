#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;      // 这条边指向的点
    int rev;     // 反向边在对方邻接表里的位置
    int cap;     // 剩余容量
};

class Dinic {
public:
    int n;
    vector<vector<Edge>> g;
    vector<int> level, iter;

    Dinic(int n) {
        this->n = n;
        g.assign(n, vector<Edge>());
        level.assign(n, 0);
        iter.assign(n, 0);
    }

    // 加一条从 from 到 to，容量为 cap 的边
    void addEdge(int from, int to, int cap) {
        Edge a = {to, (int)g[to].size(), cap};
        Edge b = {from, (int)g[from].size(), 0};
        g[from].push_back(a);
        g[to].push_back(b);
    }

    // BFS 分层图
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (auto &e : g[v]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }

        return level[t] != -1;
    }

    // DFS 找增广路
    int dfs(int v, int t, int f) {
        if (v == t) return f;

        for (int &i = iter[v]; i < (int)g[v].size(); i++) {
            Edge &e = g[v][i];

            if (e.cap > 0 && level[v] + 1 == level[e.to]) {
                int ret = dfs(e.to, t, min(f, e.cap));

                if (ret > 0) {
                    e.cap -= ret;
                    g[e.to][e.rev].cap += ret;
                    return ret;
                }
            }
        }

        return 0;
    }

    // 求最大流
    int maxFlow(int s, int t) {
        int flow = 0;
        const int INF = 1e9;

        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);

            int f;
            while ((f = dfs(s, t, INF)) > 0) {
                flow += f;
            }
        }

        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 第一问：DP 求最长不下降子序列长度
    vector<int> dp(n + 1, 1);
    int longest = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            // 不下降：前面的数 <= 后面的数
            if (a[j] <= a[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        longest = max(longest, dp[i]);
    }

    cout << longest << '\n';

    // 特判：如果最长长度是 1，每个单独元素都是一个最长子序列
    // 即使 x1 和 xn 可以重复用，也不能重复算同一个下标序列
    if (longest == 1) {
        cout << n << '\n';
        cout << n << '\n';
        return 0;
    }

    auto solveFlow = [&](bool allowFirstLastRepeat) {
        const int INF = 1e9;

        int S = 0;
        int T = 2 * n + 1;
        Dinic dinic(2 * n + 2);

        auto inNode = [&](int i) {
            return i;
        };

        auto outNode = [&](int i) {
            return i + n;
        };

        for (int i = 1; i <= n; i++) {
            int cap = 1;

            // 第三问：第一个元素和最后一个元素可以重复使用
            if (allowFirstLastRepeat && (i == 1 || i == n)) {
                cap = INF;
            }

            // 拆点边，限制每个元素能被使用几次
            dinic.addEdge(inNode(i), outNode(i), cap);

            // 可以作为最长子序列的起点
            if (dp[i] == 1) {
                int startCap = 1;
                if (allowFirstLastRepeat && (i == 1 || i == n)) {
                    startCap = INF;
                }
                dinic.addEdge(S, inNode(i), startCap);
            }

            // 可以作为最长子序列的终点
            if (dp[i] == longest) {
                int endCap = 1;
                if (allowFirstLastRepeat && (i == 1 || i == n)) {
                    endCap = INF;
                }
                dinic.addEdge(outNode(i), T, endCap);
            }
        }

        // 建立子序列中的前后连接关系
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                // i 可以接到 j，且长度正好加 1
                if (a[i] <= a[j] && dp[j] == dp[i] + 1) {
                    // 容量设为 1，防止同一条具体下标路径被重复算
                    dinic.addEdge(outNode(i), inNode(j), 1);
                }
            }
        }

        return dinic.maxFlow(S, T);
    };

    // 第二问：所有元素都只能用一次
    int ans2 = solveFlow(false);

    // 第三问：x1 和 xn 可以重复使用
    int ans3 = solveFlow(true);

    cout << ans2 << '\n';
    cout << ans3 << '\n';

    return 0;
}