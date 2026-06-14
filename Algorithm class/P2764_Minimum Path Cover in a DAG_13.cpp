#include <bits/stdc++.h>
using namespace std;

const int MAXN = 155;

int n, m;
vector<int> g[MAXN];

int matchR[MAXN];   // matchR[v] = u，表示右部点 v 匹配了左部点 u
bool vis[MAXN];

int pre[MAXN];      // pre[v] = u，表示路径中 u 在 v 前面
int nxt[MAXN];      // nxt[u] = v，表示路径中 v 在 u 后面

bool dfs(int u) {
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];

        if (vis[v]) continue;
        vis[v] = true;

        if (matchR[v] == 0 || dfs(matchR[v])) {
            matchR[v] = u;
            return true;
        }
    }

    return false;
}

int main() {
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    int maxMatch = 0;

    for (int i = 1; i <= n; i++) {
        memset(vis, false, sizeof(vis));

        if (dfs(i)) {
            maxMatch++;
        }
    }

    for (int v = 1; v <= n; v++) {
        if (matchR[v] != 0) {
            int u = matchR[v];
            nxt[u] = v;
            pre[v] = u;
        }
    }

    int pathCount = 0;

    for (int i = 1; i <= n; i++) {
        if (pre[i] == 0) {
            pathCount++;

            int now = i;
            bool first = true;

            while (now != 0) {
                if (!first) cout << " ";
                cout << now;
                first = false;

                now = nxt[now];
            }

            cout << endl;
        }
    }

    cout << pathCount << endl;

    return 0;
}