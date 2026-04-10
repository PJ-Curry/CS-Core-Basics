#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9; // 定义无穷大

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    // Prim 算法相关变量
    vector<int> minDist(n, INF); // 到生成树的最短距离
    vector<bool> visited(n, false); // 是否已加入生成树
    int totalLength = 0;

    minDist[0] = 0; // 从第一个农场开始

    for (int i = 0; i < n; ++i) { // 大循环 确保每一个农场都被拉进网络 Prim算法一次只选一个农场
        int u = -1;
        // 找到未访问点中距离树最近的点
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (u == -1 || minDist[j] < minDist[u])) {
                u = j;
            }
        }

        // 将该点加入生成树
        visited[u] = true;
        totalLength += minDist[u];

        // 更新其他点到生成树的距离 更新周围的候选距离
        // 新农场u加入了网络 可能导致连接变短 需要更新
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && graph[u][v] < minDist[v]) {
                minDist[v] = graph[u][v];
                //minDist[v]不是从起点到v的距离，而是从"已经通网的所有农场集体"到v的最短距离
            }
        }
    }

    cout << totalLength << endl;

    return 0;
}