//二分法基础题
#include<bits/stdc++.h>
using namespace std;

//判断高度 h 是否能锯出至少 m 米木材
bool check (int h, int n, int m, const vector<int>& trees) {
    long long sum = 0;
    for (int i = 0; i < n; i++){
        if (trees[i] > h){
            sum += (trees[i] - h);
        }
    }
    return sum >= m;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> trees(n);
    int max_h = 0;
    for(int i = 0; i < n; i++){
        cin >> trees[i];
        if (trees[i] > max_h) max_h = trees[i];
    }

    //确定二分搜索的范围
    int left = 0, right = max_h;
    int ans = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2; // 防止溢出的写法
        
        if (check(mid, n, m, trees)) {
            ans = mid;      // 暂时记录当前这个可行的高度
            left = mid + 1; // 尝试把锯片再升高一点，看看还能不能满足
        } else {
            right = mid - 1; // 锯太高了，得降低高度
        }
    }

    cout << ans << endl;

    return 0;
}