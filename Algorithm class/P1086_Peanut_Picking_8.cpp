#include<bits/stdc++.h>
using namespace std;
/*
【 采花生：贪心 + 模拟逻辑拆解 】

 1. 存储：用一个结构体存下每棵花生的坐标 (r, c) 和数量 count。
 2. 排序：按 count 从大到小排序。
 3. 模拟采摘过程：
    - 第一次：从路边 (row 0) 跳到第一多的花生处。
    - 之后：从“当前花生”跳到“下一棵最多的花生”。
 
 关键时间计算：
    - 移动时间 = abs(r1 - r2) + abs(c1 - c2)
    - 采摘时间 = 1
    - 回回路边时间 = 当前行号 r （因为路边在 row 0）
*/

struct Node {
    int r, c, count;
};

// 排序规则：花生多的排前面
bool cmp(const Node& a, const Node& b) {
    return a.count > b.count;
}

int main() {
    int m, n, k;
    if (!(cin >> m >> n >> k)) return 0;

    vector<Node> peanuts;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int val;
            cin >> val;
            if (val > 0) {
                peanuts.push_back({i, j, val});
            }
        }
    }

    // 1. 贪心第一步：按数量降序排列
    sort(peanuts.begin(), peanuts.end(), cmp);

    int total_peanuts = 0;
    int cur_r = 0, cur_c = 0; // 初始位置在路边，行号设为0
    int cur_time = 0;

    // 2. 依次尝试采摘
    for (int i = 0; i < (int)peanuts.size(); i++) {
        int next_r = peanuts[i].r;
        int next_c = peanuts[i].c;
        int move_time;

        // 如果是第一棵，路边跳过去的时间就是行号 next_r
        if (i == 0) move_time = next_r; 
        else move_time = abs(next_r - cur_r) + abs(next_c - cur_c);

        // 【核心预判】：
        // 已用时间 + 跑过去的时间 + 采摘 1 秒 + 摘完后能回到路边的时间(next_r)
        if (cur_time + move_time + 1 + next_r <= k) {
            cur_time += move_time + 1; // 累加移动和采摘时间
            total_peanuts += peanuts[i].count;
            cur_r = next_r; // 更新当前坐标
            cur_c = next_c;
        } else {
            // 时间不够了，剩下的花生也摘不了了（因为要按顺序摘）
            break;
        }
    }

    cout << total_peanuts << endl;

    return 0;
}