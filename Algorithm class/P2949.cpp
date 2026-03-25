//农夫干活贪心问题
#include<bits/stdc++.h>
using namespace std;
struct Job {
    int d, p;
};

// 按截止日期从小到大排序
bool cmp(const Job& x, const Job& y) {
    return x.d < y.d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    if (!(cin >> n)) return 0;

    vector<Job> jobs(n);
    for (int i = 0; i < n; i++) {
        cin >> jobs[i].d >> jobs[i].p;
    }

    // 1. 决策：先按截止日期排序
    sort(jobs.begin(), jobs.end(), cmp);

    // 2. 算账：用小根堆维护最赚钱的任务列表
    // 堆的大小就代表了我们已经占用的总时间单位
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < n; i++) {
        if (jobs[i].d > pq.size()) {
            // 时间还够，直接做
            pq.push(jobs[i].p);
        } else if (!pq.empty() && jobs[i].p > pq.top()) {
            // 时间不够了，但当前任务比已选任务里最垃圾的那个赚钱
            // 那就反悔，把垃圾的踢了，换这个
            pq.pop();
            pq.push(jobs[i].p);
        }
    }

    // 3. 输出：把堆里剩下的利润全加起来
    long long total_profit = 0;
    while (!pq.empty()) {
        total_profit += pq.top();
        pq.pop();
    }

    cout << total_profit << endl;

    return 0;
}