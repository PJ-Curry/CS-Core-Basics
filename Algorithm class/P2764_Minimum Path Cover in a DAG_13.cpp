#include <bits/stdc++.h>
using namespace std;

const int MAXN = 155;

int n, m;

// g[u] 存的是原 DAG 中从 u 出发能到达的点
// 同时也可以看成二分图中“左部 u”连向“右部 v”
vector<int> g[MAXN];

int matchR[MAXN];   // matchR[v] = u，表示右部点 v 当前匹配了左部点 u
bool vis[MAXN];

int pre[MAXN];      // pre[v] 表示路径中 v 的前一个点
int nxt[MAXN];      // nxt[u] 表示路径中 u 的后一个点

// 匈牙利算法寻找增广路
// 尝试给左部点 u 找一个可以匹配的右部点
bool dfs(int u) {
    for (int i = 0; i < (int)g[u].size(); i++) {
        int v = g[u][i];

        if (vis[v]) continue;
        vis[v] = true;

        // 如果右部点 v 没被匹配，直接匹配
        // 如果已经被匹配，就尝试让原来匹配它的点换一个位置
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

        // 原图中的有向边 u -> v
        // 转换成二分图中的左部 u 连右部 v
        g[u].push_back(v);
    }

    int maxMatch = 0;

    // 枚举每个左部点，尝试加入匹配
    for (int i = 1; i <= n; i++) {
        memset(vis, false, sizeof(vis));

        if (dfs(i)) {
            maxMatch++;
        }
    }

    // 根据匹配关系恢复路径中的前后连接
    // 如果右部 v 匹配了左部 u，说明路径里可以接成 u -> v
    for (int v = 1; v <= n; v++) {
        if (matchR[v] != 0) {
            int u = matchR[v];
            nxt[u] = v;
            pre[v] = u;
        }
    }

    int pathCount = 0;

    // 没有前驱的点，就是某一条路径的起点
    for (int i = 1; i <= n; i++) {
        if (pre[i] == 0) {
            pathCount++;

            int now = i;
            bool first = true;

            // 顺着 nxt 数组一直输出整条路径
            while (now != 0) {
                if (!first) cout << " ";
                cout << now;
                first = false;

                now = nxt[now];
            }

            cout << endl;
        }
    }

    // 最小路径覆盖数 = n - 最大匹配数
    // 这里 pathCount 和 n - maxMatch 是一样的
    cout << pathCount << endl;

    return 0;
}