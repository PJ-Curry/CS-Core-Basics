#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long dp[20] = {0};  // dp[i] 表示 C_i（第 i 个卡特兰数）
    dp[0] = 1;               // C0 = 1

    for (int i = 1; i <= n; i++) {       // 计算 dp[i]
        for (int j = 0; j < i; j++) {
            dp[i] += dp[j] * dp[i - 1 - j];
        }
    }

    cout << dp[n] << endl;
    return 0;
}

/*
#include <bits/stdc++.h>
using namespace std;

long long memo[20];  // 记忆化数组，memo[n] 保存 C_n

long long C(int n) {
    if (n == 0) return 1;        // C0 = 1
    if (memo[n] != 0) return memo[n]; // 记忆化：如果算过就直接返回

    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += C(i - 1) * C(n - i);
    }
    memo[n] = sum;  // 保存结果，下次不用算
    return sum;
}

int main() {
    int n;
    cin >> n;
    cout << C(n) << endl;
    return 0;
}

*/