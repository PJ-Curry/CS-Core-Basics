#include<bits/stdc++.h>

using namespace std;

// dp[k][i][j] 表示两人都走了 k 步，
// 第一人在第 i 行，第二人在第 j 行时的最大分值
int f[25][15][15]; 
int g[15][15];
int n;

int main() {
    cin >> n;
    int r, c, v;
    while (cin >> r >> c >> v && (r || c || v)) {
        g[r][c] = v;
    }

    // k 表示步数，从起点到终点一共要走 (n-1) + (n-1) = 2n-2 步
    // 为了方便计算坐标，我们让 k 从 2 开始（即行+列的和）
    for (int k = 2; k <= n * 2; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // 计算当前两人所在的列
                int c1 = k - i, c2 = k - j;

                // 检查坐标合法性
                if (c1 >= 1 && c1 <= n && c2 >= 1 && c2 <= n) {
                    int t = g[i][c1];
                    if (i != j) t += g[j][c2]; // 不重合，加两个数；重合，只加一个

                        // 4 种转移情况的极大值
                        f[k][i][j] = max({
                        f[k - 1][i - 1][j - 1], // 1下，2下
                        f[k - 1][i][ j - 1 ],  // 1右，2下
                        f[k - 1][i - 1][ j ],  // 1下，2右
                        f[k - 1][i][ j ]       // 1右，2右
                    }) + t;
                }
            }
        }
    }

    // 终点是 (n, n)，此时步数和 k = n + n
    cout << f[n + n][n][n] << endl;

    return 0;
}