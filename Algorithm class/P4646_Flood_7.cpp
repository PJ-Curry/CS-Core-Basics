#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <map>

using namespace std;

typedef long long ll;

const int MAXN = 100005;
const int MAXW = 200005;

struct Point {
    int x, y;
} p[MAXN];

struct Edge {
    int to, wall_id, angle; // angle: 0->右, 1->上, 2->左, 3->下
};

// 获取墙的方向（题目说了只有水平和垂直的墙）
int get_dir(int u, int v) {
    if (p[v].x > p[u].x) return 0; // Right
    if (p[v].y > p[u].y) return 1; // Up
    if (p[v].x < p[u].x) return 2; // Left
    if (p[v].y < p[u].y) return 3; // Down
    return -1;
}

vector<Edge> adj[MAXN];
// face_id_of_edge[u][i] 对应 adj[u][i] 这条有向边属于哪个面
vector<int> face_id_of_edge[MAXN]; 

int wall_u[MAXW], wall_v[MAXW];
ll face_area[MAXW * 2];
int face_dist[MAXW * 2];
int edge_faces[MAXW][2]; // 墙 ID 对应的两个面 ID

int main() {
    // 1. 输入优化（处理 10^5 级别数据必加）
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; i++) cin >> p[i].x >> p[i].y;

    int w;
    cin >> w;
    for (int i = 1; i <= w; i++) {
        cin >> wall_u[i] >> wall_v[i];
        int u = wall_u[i], v = wall_v[i];
        // 建立双向边，并计算极角
        adj[u].push_back({v, i, get_dir(u, v)});
        adj[v].push_back({u, i, get_dir(v, u)});
        // 初始化面 ID 为 0
        face_id_of_edge[u].push_back(0);
        face_id_of_edge[v].push_back(0);
    }

    // 2. 极角排序（逆时针顺序：右、上、左、下）
    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end(), [](const Edge &a, const Edge &b) {
            return a.angle < b.angle;
        });
    }

    // 3. 寻找面 (使用左转算法 Left-turn Traversal)
    int total_faces = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (int)adj[i].size(); j++) {
            if (face_id_of_edge[i][j] != 0) continue; // 已经处理过的边跳过

            total_faces++;
            int curr = i;
            int edge_idx = j;
            ll area = 0;

            // 沿着面转一圈
            while (face_id_of_edge[curr][edge_idx] == 0) {
                face_id_of_edge[curr][edge_idx] = total_faces;
                int v = adj[curr][edge_idx].to;
                int wid = adj[curr][edge_idx].wall_id;
                
                // 记录这面墙两侧分别属于哪个面
                if (wall_u[wid] == curr) edge_faces[wid][0] = total_faces;
                else edge_faces[wid][1] = total_faces;

                // 叉积计算面积
                area += (ll)p[curr].x * p[v].y - (ll)p[v].x * p[curr].y;

                // 寻找“左转”的第一条边：
                // 即反向边 (v, curr) 在 adj[v] 排序中的前一条边
                int rev_dir = (adj[curr][edge_idx].angle + 2) % 4;
                curr = v;
                int pos = -1;
                // 在 adj[v] 中找到反向边的位置（可以用二分优化，这里顺序查找也够了）
                for (int k = 0; k < (int)adj[v].size(); k++) {
                    if (adj[v][k].angle == rev_dir) {
                        pos = k;
                        break;
                    }
                }
                // 顺时针方向的前一条就是我们要的左转边
                edge_idx = (pos + (int)adj[v].size() - 1) % (int)adj[v].size();
            }
            face_area[total_faces] = area;
        }
    }

    // 4. BFS 对偶图 (模拟洪水蔓延)
    queue<int> q;
    memset(face_dist, -1, sizeof(face_dist));
    vector<vector<int>> dual_adj(total_faces + 1);

    for (int i = 1; i <= w; i++) {
        int f1 = edge_faces[i][0];
        int f2 = edge_faces[i][1];
        dual_adj[f1].push_back(f2);
        dual_adj[f2].push_back(f1);
    }

    // 面积为负的面就是“外部区域”，洪水从这里开始
    for (int i = 1; i <= total_faces; i++) {
        if (face_area[i] < 0) {
            face_dist[i] = 0;
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : dual_adj[u]) {
            if (face_dist[v] == -1) {
                face_dist[v] = face_dist[u] + 1;
                q.push(v);
            }
        }
    }

    // 5. 最终判定：如果墙两侧的面在同一小时被淹没，墙就留下来了
    vector<int> survived;
    for (int i = 1; i <= w; i++) {
        if (face_dist[edge_faces[i][0]] == face_dist[edge_faces[i][1]]) {
            survived.push_back(i);
        }
    }

    // 6. 输出结果
    cout << survived.size() << "\n";
    for (int id : survived) cout << id << "\n";

    return 0;
}