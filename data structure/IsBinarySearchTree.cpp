#include<iostream>
#include<climits>//INT_MAX和INT_MIN宏
#include<limits>
#include<stack>
#include<algorithm>
using namespace std;
struct Node
{
    int data;
    Node *left;
    Node *right;
};
Node* Insert(Node *root,int data)
{
    if(root==NULL)
    {
        root=new Node();
        root->data=data;
        root->left=root->right=NULL;
    }
    else if(data<=root->data)
    {
        root->left=Insert(root->left,data);
    }
    else
    {
        root->right=Insert(root->right,data);
    }
    return root;
}

/*bool IsSubtreeLesser(Node *root,int value)//检查这棵树中的所有元素都小于给定的值
{
    if(root==NULL) return true;
    if(root->data<=value
        &&IsSubtreeLesser(root->left,value)
        &&IsSubtreeLesser(root->right,value))
        return true;
    else
        return false;
}
bool IsSubtreeGreater(Node *root,int value)
{
    if(root==NULL) return true;
    if(root->data>=value
        &&IsSubtreeGreater(root->left,value)
        &&IsSubtreeGreater(root->right,value))
        return true;
    else
        return false;
}
bool IsBinarySearchTree(Node *root)
{
    if(root==NULL) return true;
    if(IsSubtreeLesser(root->left,root->data)//传递地址向IsSubtreeLesser函数进行验证
    &&IsSubtreeGreater(root->right,root->data)
    &&IsBinarySearchTree(root->left)//对左子树进行递归调用 检查子树是不是二叉搜索树
    &&IsBinarySearchTree(root->right))
    return true;
    else return false;
}*/
bool IstBstCheck(Node *root, int minValue, int maxValue)//用划定范围的方式来查找
{
    if(root==NULL) return true;

    if(root->data>minValue && root->data<maxValue
        &&IstBstCheck(root->left,minValue,root->data)
        &&IstBstCheck(root->right,root->data,maxValue))
        return true;
    else
    return false;
}
bool IsBinarySearchTree(Node *root)
{
    return IstBstCheck(root,INT_MIN,INT_MAX);//是C++里面自带的宏常量
}

//中序遍历
void Inorder(Node *root)
{
    if(root==NULL) return;
    Inorder(root->left);
    cout<<root->data<<" ";
    Inorder(root->right);
}
int main()
{
    Node *root=NULL;
    root=Insert(root,15);
    root = Insert(root, 15);
    root = Insert(root, 10);
    root = Insert(root, 20);
    root = Insert(root, 8);
    root = Insert(root, 12);
    root = Insert(root, 17);
    root = Insert(root, 25);

    cout << "中序遍历结果: ";
    Inorder(root);
    cout << endl;

    if(IsBinarySearchTree(root))
    {
        cout<<"这是二叉搜索树！"<<endl;
    }
    else
    {
        cout<<"这不是二叉搜索树"<<endl;
    }
    return 0;
}


static bool checkBSTImpl(Node *head,long long *prev)//和中序遍历的代码类似 就是把输出行为变成bool
{
    if(head==NULL) return true;
    if(!checkBSTImpl(head->left,prev)) return false;
    if(head->data<=*prev) return false;//注意要解引用
    *prev=head->data;
    return checkBSTImpl(head->right,prev);
}
bool checkBST(Node *root)
{
    long long prev=numeric_limits<long long>::min();
    return checkBSTImpl(root,&prev);
}//这个是动态检查 其实把中序遍历到的数字 放在list里面遍历顺序 就是main函数之前的代码

//中序遍历非递归形式 非递归就是要自己手动维护栈
void inorderTraversal(Node *root)
{
    stack<Node*>st;
    Node *cur=root;

    while(cur!=NULL||!st.empty())
    {
        //一直往左走，把路径上的节点压栈
        while(cur!=NULL)
        {
            st.push(cur);
            cur=cur->left;
        }
        cur=st.top();
        st.pop();
        cout<<cur->data<<" ";

        cur=cur->right;
    }
}


/*
套路模式：左树：是搜索二叉树 max<root
         右树：是搜索二叉树 min>root
         递归行为返回的因该是同一个东西 但是min和max不一样
         所以我们两个都返回 左树右树两个都要即可
*/

struct Ret
{
    bool isBST;
    int Min,Max;
    Ret(bool b=true,int mn=INT_MIN,int mx=INT_MAX):isBST(b),Min(mn),Max(mx){}
};
Ret process(Node *x)
{
    if(!x) return Ret(true,INT_MAX,INT_MIN);

    Ret L=process(x->left);
    Ret R=process(x->right);

    int mn=min(x->data,min(L.Min,R.Min));
    int mx=max(x->data,max(L,Max,R.Max));

    bool okleft = (!x->left || (L.isBST && L.Max<x->data));
         
}