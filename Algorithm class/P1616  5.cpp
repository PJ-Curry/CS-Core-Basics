//动态规划正序遍历
#include<bits/stdc++.h>
using namespace std;
// t 最大 10^7，数组开在全局区，防止栈溢出
long long dp[10000005];

int main() {
    int t, m;//t采药时间 m数量
    if (!(cin >> t >> m)) return 0;

    for (int i = 0; i < m; ++i) {
        int w, v;
        cin >> w >> v;
        // 注意这里：正序遍历！
        // 因为可以无限采摘，dp[j] 依赖的 dp[j-w] 可以是已经更新过的
        for (int j = w; j <= t; ++j) {
            dp[j] = max(dp[j], dp[j - w] + v);
        }
    }

    cout << dp[t] << endl;

    return 0;
}