//二叉树的非递归形式代码练习
#include<bits/stdc++.h>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x):val(x),left(NULL),right(NULL){};//构造函数
};
//写的都是关于二叉树的非递归形式（自己手搓栈）
//先序
void preOrderUnRecur(TreeNode *head)
{
    stack<TreeNode*> st;
    //放入头结点
    st.push(head);

    while(!st.empty())
    {
        TreeNode *cur = st.top();
        st.pop();//只要pop了必须打印
        cout<<cur->val<<" ";

        //先序 根左右 自己创建栈则要反过来 根右左
        if(cur -> right != NULL)
        {
            st.push(cur->right);
        }

        if(cur -> left != NULL)
        {
            st.push(cur->left);
        }
    }
}
void preorderTraversal(TreeNode* root){
    TreeNode *cur = root;
    stack<TreeNode*> st;
    while(!st.empty() || cur != nullptr){
        if(cur != nullptr){
            cout << cur->val << " ";
            st.push(cur);
            cur = cur->left;
        }
        else{
            cur = st.top();//从栈里找出来一个存档
            st.pop();
            cur = cur->right;
        }
    }
}

//中序 左根右 只要按照这个顺序“根 左”压栈 就始终能保证是中序 当栈空了 就去右孩子 继续重复根左压栈
void inOrderUnRecur(TreeNode *head)
{
    TreeNode *cur = head;//指向头结点的指针cur
    stack<TreeNode*> st;
    while(!st.empty()|| cur != NULL)
    {
        if(cur != NULL)
        {
            st.push(cur);
            cur = cur -> left;
        }
        else
        {
            cur = st.top();
            st.pop();
            cout << cur->val<<" ";
            cur = cur->right;
        }
    }
}