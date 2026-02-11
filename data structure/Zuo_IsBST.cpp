//用左神所讲的套路来写判断是否是BST 真是很巧妙 重点中的重点 向左树要信息 向右树要信息
#include<bits/stdc++.h>
using namespace std;

struct Node
{
    int val;
    Node *left;
    Node *right;
    Node(int v):val(v),left(NULL),right(NULL){}
};

//创建包裹Info 1.左右子树都应该也是BST 2.左侧最大值小于根 3.右侧最小值大于根
struct Info
{
    bool isBST;
    int maxval;
    int minval;

    Info(bool i,int ma,int mi):isBST(i),maxval(ma),minval(mi){}
};

Info* process(Node *x)//这里的Info变成了指针类型函数 和Zuo_IsBalancedBinaryTree的判断函数有所不同(两种写法) 这个是用指针 另外一个是返回对象
{
    if(x == NULL)
    {
        return NULL;
    }

    //向左右分别递归
    Info* leftData = process(x->left);
    Info* rightData = process(x->right);

    //算出最大最小值 先默认是自己 初始化
    int myMax = x->val;
    int myMin = x->val;

    //开始更新范围
    if(leftData != NULL)
    {
        myMax = max(myMax,leftData->maxval);
        myMin = min(myMin,leftData->minval);
    }
    if(rightData != NULL)
    {
        myMax = max(myMax,rightData->maxval);
        myMin = min(myMin,rightData->minval);
    }

    bool isBST = true; 

    if(leftData != NULL && (!leftData->isBST || leftData->maxval >= x->val))
    {
        isBST = false;
    }
    if(rightData != NULL && (!rightData->isBST || rightData->minval <= x->val))
    {
        isBST = false;
    }

    /*
    bool isBST = false;
    if(
        (leftData != NULL ? (leftData->isBST && leftData->maxval <= x->val) : true) &&
        (rightData != NULL ? (rightData->isBST && rightData->minval >= x->val) : true)
    )
    {
        isBST = true;
    }方向和上面的相反的
    */

    return new Info(isBST,myMax,myMin);//在堆上了 不在栈上 堆会给你保存数据 需要手动释放才行
}

bool isBST(Node* head)
{
    if(head == NULL) return true;
    Info *res = process(head);
    return res->isBST;
}

int main() 
{
    // 
    // 场景一：造一棵合法的 BST
    //       4
    //      / \
    //     2   6
    //    / \ / \
    //   1  3 5  7
    Node* head = new Node(4);
    head->left = new Node(2);
    head->right = new Node(6);
    head->left->left = new Node(1);
    head->left->right = new Node(3);
    head->right->left = new Node(5);
    head->right->right = new Node(7);

    cout << "Test Case 1 (Valid BST): " << (isBST(head) ? "True" : "False") << endl;

    // 场景二：造一棵违规的树
    //       4
    //      / \
    //     5   6  <-- 5 在 4 的左边，这就错了！(左边必须小于根)
    Node* badHead = new Node(4);
    badHead->left = new Node(5); // 错误点
    badHead->right = new Node(6);

    cout << "Test Case 2 (Invalid BST): " << (isBST(badHead) ? "True" : "False") << endl;

    return 0;
}