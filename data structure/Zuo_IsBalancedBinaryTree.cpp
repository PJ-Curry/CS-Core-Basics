/*
判断是否是平衡二叉树
任何左右子树高度差不大于1
要做的就是两件事
1.子树也都是Balanced
2.找出左右子树的高度  套路：要信息
*/
#include<iostream>
#include<cmath>
using namespace std;
struct Node
{
    int val;
    Node *left;
    Node *right;
    Node(int v):val(v),left(NULL),right(NULL){}
};

struct Ret
{
    bool isBalanced;//子树的返回值要是balanced
    int height;//要返回子树的高度
    Ret(bool b=true,int h=0) : isBalanced(b), height(h) {}
};

//拿到最后子树信息 再汇总到当前节点 其实就是后序遍历
Ret process(Node *x) //返回值类型是自己定义的Return！
{
    if(x==NULL) return Ret(true,0);//在这里初始化了高度为0 空树

    Ret L = process(x->left);
    Ret R = process(x->right);

    int h=max(L.height,R.height)+1;
    bool ok=L.isBalanced && R.isBalanced && (abs(L.height-R.height)<2);

    return Ret(ok,h);
}

bool isBalancedBinaryTree(Node *root)
{
    return process(root).isBalanced;
}

int main()
{
    Node *root1=new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);
    root1->right->left = new Node(6);
    root1->right->right = new Node(7);

    cout<<"Is the Tree Balanced?"<<(isBalancedBinaryTree(root1)?"Yes":"No")<<endl;

    Node *root2 = new Node(1);
    root2->left = new Node(2);
    root2->left->left = new Node(3);
    root2->left->left->left = new Node(4);

    cout<<"Tree 2 is balanced?"<<(isBalancedBinaryTree(root2)?"Yes":"No")<<endl;

    return 0;
}