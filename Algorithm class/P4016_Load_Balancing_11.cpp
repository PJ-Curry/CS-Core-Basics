#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> a(n);
    ll sum = 0;
    for (ll &x : a) {
        cin >> x;
        sum += x;
    }

    ll avg = sum / n;

    vector<ll> prefix(n);
    ll cur = 0;
    for (int i = 0; i < n; ++i) {
        // cur 表示到当前位置为止，多出来的货物需要从下一条边运走多少。
        cur += a[i] - avg;
        prefix[i] = cur;
    }

    // 环上可以任选一条边作为“断点”，等价于给所有前缀和减同一个数。
    // 绝对值之和在中位数处最小，所以取中位数作为断点对应的偏移量。
    vector<ll> sorted = prefix;
    sort(sorted.begin(), sorted.end());
    ll median = sorted[n / 2];

    ll ans = 0;
    for (ll x : prefix) {
        ans += llabs(x - median);
    }

    cout << ans << '\n';
    return 0;
}
