#include<bits/stdc++.h>
using namespace std;

// 全局变量，自动初始化为 0
int dp[1005]; 

int main() {
    // 优化 C++ 输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(0);

    int h1, m1, h2, m2, n;
    char colon; // 用来“吃掉”时间中间的冒号

    // 读取时间格式 hh:mm
    if (!(cin >> h1 >> colon >> m1 >> h2 >> colon >> m2 >> n)) return 0;

    // 计算总可用时间（分钟）
    int totalTime = (h2 * 60 + m2) - (h1 * 60 + m1);

    for (int i = 0; i < n; ++i) {
        int w, v, p;
        cin >> w >> v >> p;

        if (p == 0) {
            // 情况1：完全背包（无限次）-> 正序刷
            for (int j = w; j <= totalTime; ++j) {
                dp[j] = max(dp[j], dp[j - w] + v);
            }
        } else {
            // 情况2：0/1背包或多重背包（有限次）
            // 使用二进制拆分优化：把 p 个物品拆成 1, 2, 4, 8... 堆
            int num = p;
            for (int k = 1; num > 0; k <<= 1) {
                int mul = min(k, num);
                num -= mul;
                
                int curW = mul * w;
                int curV = mul * v;
                
                // 拆出来的每一堆都看作一个整体，走 0/1 背包逻辑 -> 倒序刷
                for (int j = totalTime; j >= curW; --j) {
                    dp[j] = max(dp[j], dp[j - curW] + curV);
                }
            }
        }
    }

    cout << dp[totalTime] << endl;

    return 0;
}