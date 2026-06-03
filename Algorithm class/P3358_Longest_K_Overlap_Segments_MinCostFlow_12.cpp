#include <bits/stdc++.h>
using namespace std;

const int INF_CAP = 1000000000;
const long long INF_COST = (1LL << 60);

// 最大流/费用流里面的一条边
struct Edge {
    int to;             // 这条边连到哪个点
    int rev;            // 反向边在对方邻接表里的编号
    int cap;            // 这条边还剩多少容量
    long long cost;     // 这条边的费用
};

// 最小费用最大流模板
struct MinCostFlow {
    int nodeCount;                    // 图里面一共有多少个点
    vector<vector<Edge> > graph;       // 邻接表，graph[u] 存从 u 出发的边

    vector<long long> dist;            // 最短路距离
    vector<int> preNode;               // 记录最短路上，每个点是从哪个点来的
    vector<int> preEdge;               // 记录最短路上，用的是前一个点的哪条边
    vector<int> inQueue;               // SPFA 用，记录点是否在队列中

    // 初始化图
    void init(int n) {
        nodeCount = n;

        graph.clear();
        graph.resize(n);

        dist.resize(n);
        preNode.resize(n);
        preEdge.resize(n);
        inQueue.resize(n);
    }

    // 加边：from -> to，容量 cap，费用 cost
    void addEdge(int from, int to, int cap, long long cost) {
        Edge forwardEdge;
        forwardEdge.to = to;
        forwardEdge.rev = graph[to].size();
        forwardEdge.cap = cap;
        forwardEdge.cost = cost;

        Edge backwardEdge;
        backwardEdge.to = from;
        backwardEdge.rev = graph[from].size();
        backwardEdge.cap = 0;
        backwardEdge.cost = -cost;

        graph[from].push_back(forwardEdge);
        graph[to].push_back(backwardEdge);
    }

    // 从 source 到 sink 发送 needFlow 的流量，返回最小费用
    long long minCostMaxFlow(int source, int sink, int needFlow) {
        int flow = 0;
        long long totalCost = 0;

        while (flow < needFlow) {
            // SPFA 求当前残量网络中的最短路
            for (int i = 0; i < nodeCount; i++) {
                dist[i] = INF_COST;
                inQueue[i] = 0;
                preNode[i] = -1;
                preEdge[i] = -1;
            }

            queue<int> q;
            dist[source] = 0;
            q.push(source);
            inQueue[source] = 1;

            while (!q.empty()) {
                int now = q.front();
                q.pop();
                inQueue[now] = 0;

                for (int i = 0; i < (int)graph[now].size(); i++) {
                    Edge &e = graph[now][i];

                    // 只有还有容量的边才能走
                    if (e.cap > 0 && dist[e.to] > dist[now] + e.cost) {
                        dist[e.to] = dist[now] + e.cost;
                        preNode[e.to] = now;
                        preEdge[e.to] = i;

                        if (!inQueue[e.to]) {
                            q.push(e.to);
                            inQueue[e.to] = 1;
                        }
                    }
                }
            }

            // 如果到不了汇点，就结束
            if (dist[sink] == INF_COST) {
                break;
            }

            // 找这条路上最多还能加多少流
            int addFlow = needFlow - flow;

            for (int v = sink; v != source; v = preNode[v]) {
                int u = preNode[v];
                int edgeIndex = preEdge[v];
                addFlow = min(addFlow, graph[u][edgeIndex].cap);
            }

            // 更新残量网络
            for (int v = sink; v != source; v = preNode[v]) {
                int u = preNode[v];
                int edgeIndex = preEdge[v];

                Edge &e = graph[u][edgeIndex];

                e.cap -= addFlow;
                graph[v][e.rev].cap += addFlow;
            }

            flow += addFlow;
            totalCost += (long long)addFlow * dist[sink];
        }

        return totalCost;
    }
};

// 线段结构体
struct Segment {
    long long x1, y1, x2, y2;
    long long len;
};

// 计算线段长度，向下取整
long long getLength(long long x1, long long y1, long long x2, long long y2) {
    long double dx = (long double)x1 - (long double)x2;
    long double dy = (long double)y1 - (long double)y2;

    long double value = sqrtl(dx * dx + dy * dy);

    return (long long)floorl(value + 1e-10L);
}

// 找某个 x 坐标在离散化数组中的编号
int getIndex(vector<long long> &xs, long long x) {
    return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<Segment> seg(n);
    vector<long long> xs;

    for (int i = 0; i < n; i++) {
        cin >> seg[i].x1 >> seg[i].y1 >> seg[i].x2 >> seg[i].y2;

        // 计算线段长度
        seg[i].len = getLength(seg[i].x1, seg[i].y1, seg[i].x2, seg[i].y2);

        // 为了方便处理，让 x1 <= x2
        if (seg[i].x1 > seg[i].x2) {
            swap(seg[i].x1, seg[i].x2);
            swap(seg[i].y1, seg[i].y2);
        }

        xs.push_back(seg[i].x1);
        xs.push_back(seg[i].x2);
    }

    // x 坐标离散化
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    int m = xs.size();

    /*
        这里稍微绕一点：

        因为题目说的是“开线段”，端点不算重叠。
        为了严谨处理，我们把 x 轴拆成两类小区域：

        1. 坐标点本身
        2. 两个相邻坐标之间的空隙

        如果有 m 个不同的 x 坐标：
        小区域数量就是 2 * m - 1。

        编号规律：
        第 i 个坐标点 xs[i] 对应区域 2 * i
        xs[i] 和 xs[i + 1] 之间的空隙对应区域 2 * i + 1
    */

    int areaCount = 2 * m - 1;       // 小区域数量
    int nodeCount = areaCount + 1;  // 边界点数量

    int source = 0;
    int sink = nodeCount - 1;

    MinCostFlow mcf;
    mcf.init(nodeCount);

    // 基础边：从左往右走，每个小区域最多允许 k 条流经过
    for (int i = 0; i < areaCount; i++) {
        mcf.addEdge(i, i + 1, k, 0);
    }

    // 给每条线段建一条“选择边”
    for (int i = 0; i < n; i++) {
        int leftIndex = getIndex(xs, seg[i].x1);
        int rightIndex = getIndex(xs, seg[i].x2);

        int fromNode, toNode;

        if (leftIndex == rightIndex) {
            // 垂直线段：只占用这个 x 坐标点
            fromNode = 2 * leftIndex;
            toNode = 2 * leftIndex + 1;
        } else {
            /*
                普通开线段：
                它不包含左右端点，只覆盖中间的空隙和中间坐标点。

                从左端点后面的区域开始：
                fromNode = 2 * leftIndex + 1

                到右端点前面结束：
                toNode = 2 * rightIndex
            */
            fromNode = 2 * leftIndex + 1;
            toNode = 2 * rightIndex;
        }

        // 费用设为 -长度
        // 因为我们求的是最小费用，负得越多，代表选的长度越大
        mcf.addEdge(fromNode, toNode, 1, -seg[i].len);
    }

    // 发送 k 条流，相当于最多允许 k 层重叠
    long long minCost = mcf.minCostMaxFlow(source, sink, k);

    // 答案是最大长度，所以取负数
    cout << -minCost << '\n';

    return 0;
}