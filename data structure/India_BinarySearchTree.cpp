//二叉搜索树
#include<iostream>
using namespace std;
struct BstNode
{
    int data;
    BstNode *left;
    BstNode *right;
};

BstNode* GetNewNode(int data)
{
    BstNode *newNode=new BstNode();//创建新节点
    newNode->data=data;
    newNode->left=newNode->right=NULL;//新节点一定是叶节点 指针都指向NULL
    return newNode;//返回该节点
}

BstNode *Insert(BstNode *root,int data)//这里root作为局部变量 只能以指针形式传递
{
    if(root==NULL)
    {
        root=GetNewNode(data);
    }
    else if(data<=root->data)
    {
        root->left=Insert(root->left,data);//递归
    }
    else
    {
        root->right=Insert(root->right,data);//递归
    }
    return root;//还得返回root
}

//实现查找函数 查找成功则返回true 失败则返回false
bool Search(BstNode *root,int data)
{
    if(root==NULL) return false;
    else if(root->data==data) return true;
    else if(data<=root->data) return Search(root->left,data);//递归
    else return Search(root->right,data);
}

int main()
{
    BstNode *root=NULL;//为定义在main函数中的局部变量 不是全局变量
    root=Insert(root,15);
    root=Insert(root,10);
    root=Insert(root,20);
    root=Insert(root,25);
    root=Insert(root,8);
    root=Insert(root,12);
    int number;
    cout<<"Enter number be searched\n";
    cin>>number;
    //如果找到输出FOUND
    if(Search(root,number)==true) cout<<"Found\n";
    else cout<<"Not Found\n";
}