#include<bits/stdc++.h>
using namespace std;

int dp[205][205];

int main(){
    int n, M, T;
    if(!(cin >> n >> M >> T)) return 0;

    for(int i = 0; i < n; i++){
        int m, t;//每个愿望需要的金钱和时间
        cin >> m >> t;
        for (int j = M; j >= m; --j) {
            for (int k = T; k >= t; --k) {
                // 如果决定实现这个愿望，就在“剩下钱和时间”的最优解基础上 + 1
                dp[j][k] = max(dp[j][k], dp[j - m][k - t] + 1);
            }
        }
    }
    cout << dp[M][T] << endl;//恰好是时间和金钱都最大的格子

    return 0;
}