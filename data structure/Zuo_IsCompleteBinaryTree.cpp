/*
判断一个树是否是完全二叉树
1)有右孩子 无左孩子 直接返回false
2)在不违反1)的情况下 出现了左右孩子有不全的情况 接下来遍历到的节点都必须是叶节点
  否则返回false
*/
#include<iostream>
#include<queue>
using namespace std;
struct Node
{
    int val;
    Node *left;
    Node *right;
    Node(int v):val(v),left(NULL),right(NULL){}
};

bool isCBT(Node *root)
{
    if(root==NULL) return true;

    queue<Node*> q;
    q.push(root);
    bool leafPhase=false;//是否进入"必须是子叶"阶段

    //类似于宽度优先遍历
    while(!q.empty())
    {
        Node *cur=q.front();q.pop();
        Node *L=cur->left;
        Node *R=cur->right;

        //规则1：有右孩子无左孩子
        if(L==NULL&&R!=NULL) return false;

        //规则2：进入叶节点阶段，又遇到了有孩子的情况 false
        if(leafPhase&&(L!=NULL)||R!=NULL) return false;
        //入队：正常的层序遍历
        if(L!=NULL) q.push(L);
        if(R!=NULL) q.push(R);

        if(L==NULL||R==NULL) leafPhase=true;
    }
    return true;
}