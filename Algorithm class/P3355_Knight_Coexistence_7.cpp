#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

/*
【骑士共存问题：Dinic 算法版】
 
 1. 核心公式：最大独立集 = 总空格数 - 最大匹配数
 2. 为什么要用 Dinic：
    - 匈牙利算法复杂度 O(VE)，在 N=200 且数据刁钻时会 TLE。
    - Dinic 在二分图下复杂度为 O(E*sqrt(V))，处理 4 万个点稳如泰血。
*/

const int MAXN = 40005;   // 总点数 N*N + 源汇点
const int MAXM = 1000005; // 边数：源点连黑、白连汇、马跳8方向，所以要开到百万级
const int INF = 1e9;      // 代表流量无限大

// --- 链式前向星：一种极其高效的存图方式 ---
// 它用数组模拟邻接表，比 vector 快得多，且内存连续，对 CPU 缓存友好
int head[MAXN], nxt[MAXM], to[MAXM], cap[MAXM], edge_cnt = 1;

// 加边函数：网络流需要加“反向边”，所以一次加两条
void add_edge(int u, int v, int c) {
    // 正向边：容量为 c
    to[++edge_cnt] = v; cap[edge_cnt] = c; nxt[edge_cnt] = head[u]; head[u] = edge_cnt;
    // 反向边：容量为 0（网络流用来“反悔”的机制）
    to[++edge_cnt] = u; cap[edge_cnt] = 0; nxt[edge_cnt] = head[v]; head[v] = edge_cnt;
}

int level[MAXN]; // BFS 分层数组
int cur[MAXN];   // 当前弧优化：记录每个点搜到了哪根管子
int n, m, S, T;
bool obstacle[205][205];

int dx[] = {-1, -2, -2, -1, 1, 2, 2, 1};
int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};

inline int get_id(int r, int c) { return (r - 1) * n + c; }

// 【第一步：BFS 分层】
// 作用：确定每个点到源点的距离，防止 DFS 乱撞
bool bfs() {
    memset(level, -1, sizeof(level));
    level[S] = 0;
    queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = nxt[i]) {
            // 如果管子没满，且对方还没分层
            if (cap[i] > 0 && level[to[i]] == -1) {
                level[to[i]] = level[u] + 1;
                q.push(to[i]);
            }
        }
    }
    return level[T] != -1; // 如果水能流到汇点，说明还没满，继续
}

// 【第二步：DFS 找增广路】
// 作用：沿着层级，真正地把水往汇点推
int dfs(int u, int flow) {
    if (u == T || flow == 0) return flow;
    int out = 0; // 实际流出的水量
    
    // 注意 &i = cur[u]，这是【当前弧优化】
    // 下次再经过 u 时，i 会从上次断掉的地方继续，不重算前面灌满的管子
    for (int &i = cur[u]; i; i = nxt[i]) {
        int v = to[i];
        if (level[v] == level[u] + 1 && cap[i] > 0) {
            int res = dfs(v, min(flow - out, cap[i]));
            cap[i] -= res;     // 正向边减流量
            cap[i ^ 1] += res; // 反向边加流量（提供反悔机会）
            out += res;
            if (out == flow) break; // 水流光了，直接停
        }
    }
    return out;
}

int dinic() {
    int max_flow = 0;
    while (bfs()) { // 只要还能分层，说明还能流
        for (int i = S; i <= T; i++) cur[i] = head[i]; // 重置当前弧
        max_flow += dfs(S, INF);
    }
    return max_flow;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int r, c; cin >> r >> c;
        obstacle[r][c] = true;
    }

    S = 0, T = n * n + 1; // 定义超级源点和超级汇点
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (obstacle[i][j]) continue;
            int id = get_id(i, j);
            
            if ((i + j) % 2 == 0) { // 又是咱们熟悉的【黑白染色】逻辑
                // 所有的黑格连接源点 S
                add_edge(S, id, 1);
                // 黑格向周围 8 个方向的白格连边（冲突边）
                for (int k = 0; k < 8; k++) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && !obstacle[nx][ny]) {
                        add_edge(id, get_id(nx, ny), INF); // 冲突是绝对的，设为无限
                    }
                }
            } else {
                // 所有的白格连接汇点 T
                add_edge(id, T, 1);
            }
        }
    }

    // 结果 = 可放空格总数 - 最大冲突流量
    cout << (n * n - m) - dinic() << endl;
    return 0;
}