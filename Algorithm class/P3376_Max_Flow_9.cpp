#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

// 定义边结构体
struct Edge {
    int to;         // 该边的终点
    long long cap;  // 该边的剩余容量
    int rev;        // 反向边在邻接表 G[to] 中的下标，方便 O(1) 寻找
};

vector<vector<Edge>> G; // 邻接表表示的残量网络
vector<int> level;      // 存储每个节点的层级（s 到该点的最短距离）
vector<int> iter;       // 当前弧优化：记录每个点 DFS 搜索到了第几条边

// BFS 函数：构建分层图
// 作用：限制 DFS 只能往下一层走，防止出现循环或无效路径
bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1); // 初始化所有层级为 -1
    level[s] = 0; // 源点层级为 0
    queue<int> que;
    que.push(s);
    while (!que.empty()) {
        int v = que.front(); que.pop();
        for (auto &e : G[v]) {
            // 如果边还有余量且目标点未被分层
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
    // 返回是否能到达汇点 t
    return level[t] != -1;
}

// DFS 函数：在分层图中寻找增广路
// v: 当前节点, t: 汇点, f: 当前路径上的瓶颈流量限制
long long dfs(int v, int t, long long f) {
    if (v == t) return f; // 到达汇点，返回当前搜到的流量

    // i 从 iter[v] 开始，即“当前弧优化”
    // 之前已经确认无法增广的边，在本次 BFS 分层内不再扫描
    for (int &i = iter[v]; i < G[v].size(); ++i) {
        Edge &e = G[v][i];
        // 只有边有容量且目标点在下一层时才进行增广
        if (e.cap > 0 && level[v] < level[e.to]) {
            long long d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;             // 正向边减去流量
                G[e.to][e.rev].cap += d; // 反向边加上流量（用于后期“反悔”）
                return d;
            }
        }
    }
    return 0; // 无法增广
}

int main() {
    int n, m, s, t;
    if (!(cin >> n >> m >> s >> t)) return 0;
    
    // 初始化容器大小
    G.resize(n + 1);
    level.resize(n + 1);
    iter.resize(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        // 添加正向边
        G[u].push_back({v, w, (int)G[v].size()});
        // 添加反向边：初始容量为 0，rev 指向 G[u] 刚才插入的那条边
        G[v].push_back({u, 0, (int)G[u].size() - 1});
    }

    long long max_flow = 0;
    // 只要能构建分层图，就不断进行多路增广
    while (bfs(s, t)) {
        fill(iter.begin(), iter.end(), 0); // 每个 BFS 阶段重置当前弧
        long long f;
        // 在当前分层图中寻找所有可能的增广路径
        while ((f = dfs(s, t, INF)) > 0) {
            max_flow += f;
        }
    }

    cout << max_flow << endl;
    return 0;
}