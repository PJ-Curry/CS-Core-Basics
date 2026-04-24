#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
【树形 DP：没有上司的舞会】
 
 逻辑结构图：
      校长(Root)
      /    \
    经理A   经理B  <-- 如果校长去，他们都不准去
    /  \      \
 员工1 员工2   员工3 <-- 如果经理A不去，员工1可以去也可以不去
 
*/

const int MAXN = 6005;
int r[MAXN];          // 快乐指数
int dp[MAXN][2];      // dp[i][0]不来, dp[i][1]来
vector<int> edge[MAXN]; // 用邻接表存树的结构
bool has_boss[MAXN];  // 标记是否有上司，用来找校长（根节点）

void dfs(int u) {
    dp[u][0] = 0;      // 初始：我不来，快乐值为0
    dp[u][1] = r[u];   // 初始：我来了，快乐值为我自己的r[u]

    // 遍历每一个直接下属 v
    for (int v : edge[u]) {
        dfs(v); // 先递归处理下属的子树（自底向上）

        // 情况1：老总 u 参加，下属 v 必不参加
        dp[u][1] += dp[v][0];

        // 情况2：老总 u 不参加，下属 v 随便，选个大的
        dp[u][0] += max(dp[v][0], dp[v][1]);
    }
}

int main() {
    int n;
    cin >> n;

    // 1. 读入快乐值
    for (int i = 1; i <= n; i++) cin >> r[i];

    // 2. 读入从属关系
    for (int i = 1; i < n; i++) {
        int l, k;
        cin >> l >> k; // k 是 l 的上司
        edge[k].push_back(l);
        has_boss[l] = true; // l 有上司，不是校长
    }

    // 3. 寻找校长（根节点）：谁没有上司谁就是校长
    int root = 1;
    while (has_boss[root]) root++;

    // 4. 从校长开始 DFS
    dfs(root);

    // 5. 最终答案：校长来或不来中的最大值
    cout << max(dp[root][0], dp[root][1]) << endl;

    return 0;
}