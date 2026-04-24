#include <iostream>
#include <algorithm>

using namespace std;

int dp[1005]; // 总时间 T <= 1000

int main() {
    int T, M;
    cin >> T >> M;

    for (int i = 0; i < M; ++i) {
        int w, v;
        cin >> w >> v;
        // 0/1 背包核心：容量必须倒序遍历
        for (int j = T; j >= w; --j) {
            dp[j] = max(dp[j], dp[j - w] + v);
        }
    }

    cout << dp[T] << endl;
    return 0;
}