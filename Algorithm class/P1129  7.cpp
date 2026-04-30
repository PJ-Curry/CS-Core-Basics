#include<bits/stdc++.h>
using namespace std;
/*
【矩阵游戏：二分图最大匹配】

 逻辑拆解：
 1. 每一个黑格子 (i, j) 是一条边，连接了“行i”和“列j”。
 2. 目标是在 n 行和 n 列之间找到 n 条不相交的边。
 3. 这就是求二分图的最大匹配。
*/

const int MAXN = 205;
vector<int> adj[MAXN]; // 邻接表存图：adj[行] = {可以匹配的列}
int match[MAXN];       // match[列] = 目前匹配的行
bool vis[MAXN];        // 标记这一轮 DFS 中，该列是否被访问过
int n;

//匈牙利算法：为行u找到一个匹配的列
bool dfs(int u) { // 为员工 u 找位子
    for (int v : adj[u]) { // 遍历员工 u 喜欢的所有位子 v
        if (!vis[v]) { // 这一轮还没找过位子 v（防止套娃死循环）
            vis[v] = true; // 标记一下，我现在正在谈位子 v 的归属
            
            // 接下来是两种成功的可能：
            // 1. 位子 v 还没人坐
            // 2. 位子 v 有人坐(match[v])，但我成功地让那个人挪到了别的位子
            if (match[v] == 0 || dfs(match[v])) { 
                match[v] = u; // 最终，员工 u 成功入驻位子 v
                return true;  // 告诉上级：我搞定了！
            }
        }
    }
    return false; // 找了一圈，实在没人愿意让座，失败
}

void solve(){
    cin >> n;

    //1.初始化
    for (int i = 1; i <= n; i++) adj[i].clear();
    memset(match, 0, sizeof(match));

    //2.建图
    for (int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int val;
            cin >> val;
            if(val == 1){
                adj[i].push_back(j);
            }
        }
    }

    //3.求最大匹配
    int count = 0;
    for(int i = 1; i <= n; i++){
        memset(vis, false, sizeof(vis));
        if(dfs(i)) count++;
    }

    //4.判断是否达到完美匹配
    if(count == n) cout << "Yes" << endl;
    else cout << "No" << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        solve();
    }
    return 0;
}