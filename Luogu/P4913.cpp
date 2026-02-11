//求二叉树高度
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 5;
int Lc[MAXN],Rc[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for(int i = 1; i < n; i++)
    {
        cin >> Lc[i] >> Rc[i];
    }

    //根节点是1
    queue<int> q;
    q.push(1);

    int depth = 0;

    while(!q.empty())
    {
        int sz = q.size();
        depth++;

        while(sz--)
        {
            int u = q.front();
            q.pop();

            if (Lc[u] !=0) q.push(Lc[u]);
            if (Rc[u] !=0) q.push(Rc[u]);//u正好和数组中要输出的行数对应了
        }
    }
    cout << depth << endl;
    return 0;
}



//树递归写法
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 5;
int Lc[MAXN], Rc[MAXN];

int dfs(int u) 
{
    if (u == 0) return 0;  // 空结点高度为 0
    int lh = dfs(Lc[u]);   // 左子树高度
    int rh = dfs(Rc[u]);   // 右子树高度
    return 1 + max(lh, rh);
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) 
    {
        cin >> Lc[i] >> Rc[i];
    }

    cout << dfs(1) << endl;   // 根节点是 1
    return 0;
}
