#include<iostream>
using namespace std;
struct BstNode
{
    int data;
    BstNode *left;
    BstNode *right;
};
int FindMin(BstNode *root)
{
    if(root==NULL)
    {
        cout<<"Error:Tree is empty\n";
        return -1;
    }
    while(root->left!=NULL)
    {
        root=root->left;
    }
    return root->data;
}

//上面是循环写法 下面是递归写法
int FindMin(BstNode *root)
{
    if(root==NULL)
    {
        cout<<"Error:Tree is empty\n";
        return -1;
    }
    else if(root->left==NULL)//到达叶节点
    {
        return root->data;
    }
    return FindMin(root->left);//调用递归
}

int FindHeight(struct BstNode *root)//其实就是Node *root Bst是上一个题的
{
    if(root==NULL)
    {
        return -1;
    }
    return max(FindHeight(root->left),FindHeight(root->right))+1;
}