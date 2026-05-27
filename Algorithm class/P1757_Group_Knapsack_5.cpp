//分组背包问题 不能选同一个组的
/*
1.第一层：遍历组(k) 现决定处理那一拨人
2.第二层：遍历容量 从大到小
3.第三层：遍历组内每一个物品 在当前组里挑最好的
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// dp[j] 表示容量为 j 时的最大价值
int dp[1005];
// 用来存每组里有哪些物品，weight[组号][第几个]
vector<int> weight[1001], value[1001];
int max_group = 0;

int main() {
    int m, n;
    cin >> m >> n;

    for (int i = 0; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        weight[c].push_back(a);
        value[c].push_back(b);
        max_group = max(max_group, c); // 记录一共多少组
    }

    // 1. 遍历每一组
    for (int k = 1; k <= max_group; ++k) {
        if (weight[k].empty()) continue;
        
        // 2. 遍历容量（倒序，0/1 背包思想）
        for (int j = m; j >= 0; --j) {
            // 3. 遍历组内的每一个物品
            for (int i = 0; i < weight[k].size(); ++i) {
                if (j >= weight[k][i]) {
                    // 在“不选这组”和“选这组里的某一个”之间选最大的
                    dp[j] = max(dp[j], dp[j - weight[k][i]] + value[k][i]);
                }
            }
        }
    }

    cout << dp[m] << endl;

    return 0;
}