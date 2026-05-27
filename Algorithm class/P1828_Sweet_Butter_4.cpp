#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 定义无穷大，0x3f3f3f3f 是个巧妙的数值，相加不易溢出且足够大
const int INF = 0x3f3f3f3f;

// 边的结构体
struct Edge {
    int to;     // 这条边通向哪个牧场
    int weight; // 这条边的长度（权值）
};

// 优先队列（堆）中存储的节点信息
struct Node {
    int id;    // 牧场编号
    int dist;  // 从当前起点到该牧场的已知最短距离

    // 优先队列默认是大根堆，我们需要通过重载大于号来构造小根堆
    // 这样每次 pq.top() 取出的都是当前距离最短的节点
    bool operator>(const Node& other) const {
        return dist > other.dist;
    }
};

int N, P, C;
int cow_pos[505];       // 记录每只奶牛所在的牧场编号
vector<Edge> adj[805];  // 邻接表，存储牧场间的连接关系

/**
 * Dijkstra 算法：计算从起点 start 到所有牧场的最短路径
 * 返回值：所有奶牛到达该起点的总路程
 */
int dijkstra(int start) {
    // dist 数组记录从 start 到每个牧场的最短距离
    vector<int> dist(P + 1, INF);
    // 小根堆，用于快速寻找当前距离最短的未访问节点
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    // 初始化起点
    dist[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int u = current.id;
        int d = current.dist;

        // 懒惰删除：如果从堆里取出的距离已经不是最新的最短距离，则跳过
        if (d > dist[u]) continue;

        // 遍历当前节点 u 的所有邻居 v
        for (auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;

            // 松弛操作 (Relaxation)：如果经过 u 到达 v 的路径更短，则更新
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({v, dist[v]});
            }
        }
    }

    // 统计阶段：计算所有奶牛到这个牧场（糖所在地）的总路程
    int total_dist_sum = 0;
    for (int i = 0; i < N; ++i) {
        int pos = cow_pos[i];
        // 如果发现某只牛所在的牧场根本无法到达（理论上在连通图中不会发生）
        if (dist[pos] == INF) return INF; 
        total_dist_sum += dist[pos];
    }
    
    return total_dist_sum;
}

int main() {
    // 快速输入输出（可选，但在 P=800 时有帮助）
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 读取奶牛数 N，牧场数 P，道路数 C
    if (!(cin >> N >> P >> C)) return 0;

    // 读取每只奶牛所在的牧场
    for (int i = 0; i < N; ++i) {
        cin >> cow_pos[i];
    }

    // 读取道路，构造双向图
    for (int i = 0; i < C; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        // 题目给的是双向道路，所以两边都要加
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int min_ans = INF;

    // 核心循环：尝试将糖放在每一个牧场 i（1 <= i <= P）
    for (int i = 1; i <= P; ++i) {
        // 计算如果糖放在 i，所有牛跑过来的总路程
        int result = dijkstra(i);
        // 更新全局最小值
        if (result < min_ans) {
            min_ans = result;
        }
    }

    // 输出最终找到的最小总路程
    cout << min_ans << endl;

    return 0;
}