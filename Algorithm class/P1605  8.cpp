#include<bits/stdc++.h>
using namespace std;

int n, m, t;
int sx, sy, fx, fy;
bool vis[10][10]; // 记录该点是否被访问过，或者是障碍
int ans = 0;

// 方向数组：上下左右
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dfs(int x, int y) {
    // 1. 到达终点
    if (x == fx && y == fy) {
        ans++;
        return;
    }

    // 2. 尝试向四个方向移动
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // 检查边界、障碍以及是否访问过
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !vis[nx][ny]) {
            // 【标记】进入该点
            vis[nx][ny] = true;
            
            dfs(nx, ny);
            
            // 【回溯】离开该点，清除标记，允许其他路径再次进入
            vis[nx][ny] = false;
        }
    }
}

int main() {
    // 输入地图大小和障碍数
    if (!(cin >> n >> m >> t)) return 0;
    
    // 输入起点和终点
    cin >> sx >> sy >> fx >> fy;

    // 输入障碍点并标记为已访问
    for (int i = 0; i < t; i++) {
        int tx, ty;
        cin >> tx >> ty;
        vis[tx][ty] = true;
    }

    // 起点本身要标记为已访问，防止绕回来
    vis[sx][sy] = true;

    // 开始搜索
    dfs(sx, sy);

    // 输出总方案数
    cout << ans << endl;

    return 0;
}

/*
【 2x2 迷宫 DFS 递归深度拆解示例 】
 起点: (1,1) -> 终点: (2,2)

 第一层：dfs(1,1)
 ├── 1. 标记当前点：vis[1][1] = true (插旗)
 ├── 2. 决策：尝试往右走
 └── 3. 动作：调用 第二层：dfs(1,2)
      │
      第二层：dfs(1,2)
      ├── 1. 标记当前点：vis[1][2] = true (插旗)
      ├── 2. 决策：尝试往下走
      └── 3. 动作：调用 第三层：dfs(2,2)
           │
           第三层：dfs(2,2)
           ├── 1. 检查：到达终点 (2,2)！
           ├── 2. 结算：方案数 ans++ (变成1)
           └── 3. 返回：执行 return，分身消失，回到第二层
      │
      第二层：dfs(1,2) —— (续)
      ├── 4. 回溯：vis[1][2] = false (拔旗，清理现场)
      ├── 5. 探索：尝试往左、往上走，发现越界或已走过
      └── 6. 结束：该点所有方向尝试完毕，return 回到第一层
 │
 第一层：dfs(1,1) —— (续)
 ├── 4. 回溯：vis[1][1] = false (拔旗)
 ├── 5. 决策：尝试往下走，调用新的分支 dfs(2,1)
 └── ...以此类推，直到所有分支探索完毕...

 总结：递归像“深挖”，回溯像“填坑”。
*/