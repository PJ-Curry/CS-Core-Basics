#include<bits/stdc++.h>
using namespace std;

const int MAXN = 105; 

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    if (!(cin >> n)) return 0;

    // adj[i] 存储第 i 个人的所有孩子列表
    vector<int> adj[MAXN];
    // in_degree[i] 存储第 i 个人的入度（有多少个直接长辈）
    int in_degree[MAXN] = {0};

    // 读取输入
    // 第 i 行描述第 i 个人的后代
    for (int i = 1; i <= n; ++i) 
    {
        int child;
        // 循环读取直到遇到 0
        while (cin >> child && child != 0) 
        {
            adj[i].push_back(child); // i 指向 child
            in_degree[child]++;      // child 的入度 +1
        }
    }

    // 拓扑排序：将所有入度为 0 的点放入队列
    queue<int> q;
    for (int i = 1; i <= n; ++i) 
    {
        if (in_degree[i] == 0) 
        {
            q.push(i);
        }
    }

    vector<int> result; // 存储结果序列

    while (!q.empty()) 
    {
        int u = q.front();
        q.pop();
        
        result.push_back(u);

        // 遍历 u 的所有孩子 v
        for (int v : adj[u]) 
        {
            in_degree[v]--; // v 的长辈 u 已经被处理，v 的入度减 1
            if (in_degree[v] == 0) 
            {
                // 如果 v 没有其他未处理的长辈了，加入队列
                q.push(v);
            }
        }
    }

    // 输出结果
    for (int i = 0; i < result.size(); ++i) 
    {
        cout << result[i] << (i == result.size() - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}