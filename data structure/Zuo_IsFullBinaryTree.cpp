/*
判断一棵树是否是满二叉树 条件就是：总节点数=2^高度—1
*/
#include<iostream>
#include<algorithm>
using namespace std;
struct Info
{
    int height;//统计高度 这是结构体成员 和下面的局部变量不一样
    int nodes;//统计节点个数
    Info(int h,int n):height(h),nodes(n){}
};
struct Node
{
    int data;
    Node *right;
    Node *left;
    Node(int v):data(v),left(NULL),right(NULL){}
};
Info f(Node *x)
{
    if(x == NULL) return Info(0, 0);
    Info leftdata = f(x->left);
    Info rightdata = f(x->right);
    int height = max(leftdata.height, rightdata.height) + 1;//局部变量
    int nodes = leftdata.nodes + rightdata.nodes + 1;
    return Info(height,nodes);
}
bool isF(Node *head)//调用主函数
{
    if(!head) return true;
    Info data = f(head);
    return data.nodes==(1 << data.height) - 1;//二进制数左移一位
}