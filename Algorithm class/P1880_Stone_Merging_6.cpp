#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 0x3f3f3f3f 是个神奇的数字，用来代表“无穷大”，不容易相加溢出
const int INF = 0x3f3f3f3f;

int a[205];         // 存原始石子数量
int sum[205];       // 存前缀和，用来快速求区间石子总数
int f1[205][205];   // 最小得分表：f1[i][j] 表示合并第 i 堆到第 j 堆的最小分数
int f2[205][205];   // 最大得分表：f2[i][j] 表示合并第 i 堆到第 j 堆的最大分数

int main() {
    int n;
    if (!(cin >> n)) return 0;

    // --- 第一部分：破环成链 ---
    // 因为操场是圆的，我们把数组复制一遍接在后面
    // 比如 4 5 9 4 变成 4 5 9 4 4 5 9 4
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i]; 
    }

    // --- 第二部分：预计算前缀和 ---
    // sum[i] = a[1] + a[2] + ... + a[i]
    for (int i = 1; i <= 2 * n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }

    // --- 第三部分：区间 DP 核心 ---
    // 我们要“从小到大”拼积木：先算长度为 2 的合并，再算 3 的...最后算 n 的
    for (int len = 2; len <= n; len++) { 
        // 枚举区间的起点 i
        for (int i = 1; i <= 2 * n - len + 1; i++) {
            int j = i + len - 1; // 根据起点和长度，算出终点 j
            
            f1[i][j] = INF; // 求最小，先设为无穷大
            f2[i][j] = 0;   // 求最大，先设为 0

            // 【核心决策】：枚举分割点 k，把 [i, j] 拆成 [i, k] 和 [k+1, j] 两大团
            for (int k = i; k < j; k++) {
                // 合并这两大团产生的得分 = 左边得分 + 右边得分 + 这两团合体的总重量
                // 这两团合体的总重量就是 sum[j] - sum[i-1]（前缀和派上用场了！）
                int score = sum[j] - sum[i - 1];
                
                f1[i][j] = min(f1[i][j], f1[i][k] + f1[k + 1][j] + score);
                f2[i][j] = max(f2[i][j], f2[i][k] + f2[k + 1][j] + score);
            }
        }
    }

    // --- 第四部分：找最终答案 ---
    // 因为我们是破环成链，所以长度为 n 的区间有很多个
    // [1,n], [2,n+1], [3,n+2] ... [n, 2n-1] 都是合法的环形合并结果
    int min_ans = INF, max_ans = 0;
    for (int i = 1; i <= n; i++) {
        min_ans = min(min_ans, f1[i][i + n - 1]);
        max_ans = max(max_ans, f2[i][i + n - 1]);
    }

    // 输出结果
    cout << min_ans << endl << max_ans << endl;

    return 0;
}