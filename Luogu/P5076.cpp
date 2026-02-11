#include <bits/stdc++.h>
using namespace std;

struct Node 
{
    int val, sz;
    Node *l, *r;
    Node(int v) : val(v), sz(1), l(nullptr), r(nullptr) {}//构造函数
};

int getsz(Node* u) { return u ? u->sz : 0; }//若u存在就返回它的大小
void pull(Node* u) { if (u) u->sz = 1 + getsz(u->l) + getsz(u->r); }
//当前树大小=1（自己）+左子树大小+右子树大小

// 插入
Node* Insert(Node* root, int x) 
{
    if (!root) return new Node(x);//调用第八行构造函数 创建一个新节点
    if (x <= root->val) root->l = Insert(root->l, x);
    else                root->r = Insert(root->r, x);
    pull(root);//更新当前节点sz
    return root;
}

// 严格小于 x 的数量
int CountLT(Node* u, int x) 
{
    if (!u) return 0;
    if (x <= u->val) return CountLT(u->l, x);
    return getsz(u->l) + 1 + CountLT(u->r, x);
    // 1. 左子树所有人都比 x 小（因为左 < 根 < x） -> getsz(u->l)
    // 2. 当前节点自己比 x 小 -> 1
    // 3. 右子树里可能还有比 x 小的 -> 递归 CountLT(u->r, x)
}

// 第 k 小（1-indexed，保证存在）
int Kth(Node* u, int k) 
{
    int ls = getsz(u->l);//先看左子树有多少人
    if (k == ls + 1) return u->val;//左人数+1恰好等于k
    if (k <= ls) return Kth(u->l, k);//k比左边人数还小
    return Kth(u->r, k - ls - 1);//k很大 在右边
}

// 前驱：< x 的最大值；不存在返回 -2147483647
int Pred(Node* u, int x) 
{
    int ans = -2147483647;
    while (u) //迭代写法
    {
        if (u->val < x) { ans = u->val; u = u->r; }//找到了比x小的数
        else u = u->l;//比x大
    }
    return ans;
}

// 后继：> x 的最小值；不存在返回 2147483647
int Succ(Node* u, int x) 
{
    int ans = 2147483647;
    while (u) 
    {
        if (u->val > x) { ans = u->val; u = u->l; }
        else u = u->r;
    }
    return ans;
}//逻辑同上

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    if (!(cin >> q)) return 0;
    Node* root = nullptr;

    while (q--) 
    {
        int op; int x;
        cin >> op >> x;
        if (op == 5) {
            root = Insert(root, x);
        } else if (op == 1) {
            cout << (CountLT(root, x) + 1) << '\n';
        } else if (op == 2) {
            cout << Kth(root, x) << '\n';
        } else if (op == 3) {
            cout << Pred(root, x) << '\n';
        } else if (op == 4) {
            cout << Succ(root, x) << '\n';
        }
    }
    return 0;
}