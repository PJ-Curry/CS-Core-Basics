//删除二叉搜索树中的节点 前提：是二叉搜索树！！！ 不要搞混！！！
//case1:No child    case2:one child   case3:two children
//在要删除的节点的右子树中找到最小值 然后放在该节点处 然后断开该点右子树链接 直接连下一个
//也可以找左子树中的最大值
#include<iostream>
using namespace std;
struct Node
{
    int data;
    Node *left;
    Node *right;
};
struct Node *FindMin(struct Node *root)
{
    if(root==NULL) return NULL;
    while(root->left!=NULL)
    {
        root=root->left;
    }
    return root;
}
struct Node *Delete(struct Node *root,int data)//待删除的数据是参数 data
{
    if(root==NULL) return root;
    else if(data < root->data) root->left = Delete(root->left,data);//把返回值设定为当前节点的左孩子
    else if(data > root->data) root->right = Delete(root->right,data);
    else//找到了
    {
        //Case1:No child
        if(root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            return root;
        }
        //Case2:One child
        else if(root->left == NULL)
        {
            struct Node *temp=root;
            root=root->right;
            delete temp;
            return root;
        }
        else if(root->right == NULL)
        {
            struct Node *temp=root;
            root=root->left;
            delete temp;
            return root;
        }
        //case3:2 children
        else
        {
            struct Node *temp=FindMin(root->right);//FindMin函数不能是void 因为要返回的是指针
            //找右子树的最小值 然后替换
            root->data=temp->data;
            root->right=Delete(root->right,temp->data);//删除这个子节点
        }
    }
    return root;
}
void Inorder(Node *root)
{
    if(root==NULL) return;
    Inorder(root->left);
    cout<<root->data<<" ";
    Inorder(root->right);
}
Node *Insert(Node *root,int data)
{
    if(root==NULL)
    {
        root=new Node();
        root->data=data;
        root->left=root->right=NULL;
    }
    else if(data<root->data)
    {
        root->left=Insert(root->left,data);
    }
    else
    {
        root->right=Insert(root->right,data);
    }
    return root;
}
int main()
{
    Node *root=NULL;
	root = Insert(root,5); root = Insert(root,10);
	root = Insert(root,3); root = Insert(root,4); 
	root = Insert(root,1); root = Insert(root,11);//插入二叉搜索树
    
    root=Delete(root,5);

    cout<<"Inorder:";
    Inorder(root);
    cout<<"\n";
}