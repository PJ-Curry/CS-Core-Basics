#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 505;
const int INF = 0x3f3f3f3f;

bool adj[MAXN][MAXN]; // 邻接矩阵，adj[u][v] 表示 u 可一站直达 v
int dist[MAXN];       // 存储从起点到各站的最少乘车次数

void solve() {
    int M, N;
    if (!(cin >> M >> N)) return;

    string line;
    getline(cin, line); // 读取第一行后的回车符

    // 1. 建图
    for (int i = 0; i < M; ++i) {
        getline(cin, line);
        stringstream ss(line);
        vector<int> route;
        int station;
        while (ss >> station) {
            route.push_back(station);
        }

        // 同一条线路中，前面的站可以直达后面的所有站 例如 ABCD 建立AB有向边 AC有向边 AD有向边即可 都算作乘一次车
        for (int j = 0; j < route.size(); ++j) {
            for (int k = j + 1; k < route.size(); ++k) {
                adj[route[j]][route[k]] = true;
            }
        }
    }

    // 2. BFS 求最短乘车次数
    fill(dist, dist + MAXN, -1);
    queue<int> q;

    q.push(1);
    dist[1] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == N) break;

        for (int v = 1; v <= N; ++v) {
            if (adj[u][v] && dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    // 3. 输出结果
    if (dist[N] == -1) {
        cout << "NO" << endl;
    } else {
        // 换车次数 = 乘车次数 - 1
        // 特殊情况：如果起点即终点，换车次数为0。本题约定 N > 1，故 dist[N]-1 始终有效。
        cout << max(0, dist[N] - 1) << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}