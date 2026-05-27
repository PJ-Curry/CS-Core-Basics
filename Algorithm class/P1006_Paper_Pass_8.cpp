#include<bits/stdc++.h>
using namespace std;

// f[k][i][j] 表示两个人都走了 k 步，第一人在第 i 行，第二人在第 j 行
int f[105][55][55];
int g[55][55];
int m, n;

int main() {
    // 1. 输入矩阵大小
    if (!(cin >> m >> n)) return 0;

    // 2. 读入好感度
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> g[i][j];
        }
    }

    // 3. 动态规划过程
    // k 代表坐标之和 (r + c)，从起点 (1,1) 的和 2 开始，到终点 (m,n) 的和 m+n
    for (int k = 2; k <= m + n; k++) {
        // 第一人的行号 i
        for (int i = 1; i <= m; i++) {
            // 第二人的行号 j
            for (int j = 1; j <= m; j++) {
                int c1 = k - i; // 第一人的列号
                int c2 = k - j; // 第二人的列号

                // 检查坐标是否在矩阵范围内
                if (c1 >= 1 && c1 <= n && c2 >= 1 && c2 <= n) {
                    
                    // 当前两个位置的好感度之和
                    int current_val = g[i][c1];
                    if (i != j) current_val += g[j][c2]; // 如果不重合，加上两人的值

                    // 从上一时刻的 4 种状态转移而来
                    int &res = f[k][i][j];
                    res = max({
                        f[k - 1][i - 1][j - 1], // 两人都向下走
                        f[k - 1][i][j - 1],     // 1向右，2向下
                        f[k - 1][i - 1][j],     // 1向下，2向右
                        f[k - 1][i][j]          // 两人都向右走
                    }) + current_val;
                }
            }
        }
    }

    // 4. 输出终点位置的最大值
    // 虽然起点和终点是 0，但 DP 会一路推导到这里
    cout << f[m + n][m][m] << endl;

    return 0;
}