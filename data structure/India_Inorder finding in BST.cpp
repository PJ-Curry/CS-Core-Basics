//在树的任何如遍历 删除等操作中 时间复杂度都是O(n) 想要通过中序遍历查找前一个数字和后继
//实现复杂度O(h) h=logn 即O(logn) 
//中序后继（Inorder Successor）
#include<iostream>
using namespace std;
struct Node
{
    int data;
    Node *left;
    Node *right;
};
Node *Find(Node *root,int data)
{
    if(root==NULL) return NULL;
    else if(root->data==data) return root;
    else if(root->data<data) return Find(root->right,data);
    else return Find(root->left,data);
}
Node *FindMin(Node *root)//找最小值 一定是往左子树上干
{
    if(root==NULL) return NULL;
    while(root->left!=NULL) root=root->left;
    return root;
}
struct Node *Getsuccessor(struct Node *root,int data)
{
    //查找带有该数据的节点 O(n)
    struct Node *current = Find(root,data);
    if(current==NULL) return NULL;
    //Case1:该节点有右子树
    if(current->right!=NULL)//这一块值得好好看一看
    return FindMin(current->right);
    //Case2:没有右子树
    else
    {
        Node *successor=NULL;
        Node *ancestor=root;
        while(ancestor!=current)//遍历整棵子树 直到到达当前current节点为止
        {
            //这里多看看！！！！！
            if(current->data<ancestor->data)//在这里就是让ancestor往下遍历数据 实现向下
            {
                successor=ancestor;//有可能是后继节点 但还不确定
                ancestor=ancestor->left;//及时向左更新
            }
            else
                ancestor=ancestor->right;//如果当前节点位于右侧 就向右侧移动
        }
        return successor;
    }
}
//Function to visit nodes in Inorder
void Inorder(Node *root) 
{
	if(root == NULL) return;
 
	Inorder(root->left);       //Visit left subtree
	printf("%d ",root->data);  //Print data
	Inorder(root->right);      // Visit right subtree
}
 
// Function to Insert Node in a Binary Search Tree
Node* Insert(Node *root,char data) 
{
	if(root == NULL) 
    {
		root = new Node();
		root->data = data;
		root->left = root->right = NULL;
	}
	else if(data <= root->data)
		root->left = Insert(root->left,data);
	else 
		root->right = Insert(root->right,data);
	return root;
}
int main()
{
    Node *root=NULL;
	root = Insert(root,5); root = Insert(root,10);
	root = Insert(root,3); root = Insert(root,4); 
	root = Insert(root,1); root = Insert(root,11);    

    cout<<"Inorder Traversal: ";
    Inorder(root);
    cout<<"\n";

    struct Node *successor=Getsuccessor(root,1);
    if(successor==NULL) cout<<"没有后继者\n";
    else
        cout<<"后继者是 "<<successor->data<<"\n";
}