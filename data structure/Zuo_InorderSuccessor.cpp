//题意是找后继节点 后继节点定义：中序遍历元素的下一个元素 正常O(n) 两个点之间路径是k 如何将时间复杂度降低到O(k)
/*
1)x有右树 则x右孩子的左孩子(最最最左的孩子)就是后继节点
2)x无右树 一路往上找 看这些节点是不是一个祖宗的左孩子 如果是 那么那个祖宗就是x的后继节点
3)x是整个树的最后一个节点 后继节点是NULL
*/
#include<bits/stdc++.h>
using namespace std;
struct Node
{
    int val;
    Node *left;
    Node *right;
    Node *parent;
    Node(int x) : val(x), left(NULL), right(NULL), parent(NULL){}
};
class solution{
public:
    //找左孩子
    Node *getLeftMost(Node *node)
    {
        if(node == NULL)
        {
            return node; 
        }
        while(node->left != NULL)
        {
            node = node->left;
        }
        return node;
    }

    //寻找后继节点
    Node *getSuccessorNode(Node *node)
    {
        if(node == NULL)
        {
            return node;
        }
        if(node->right != NULL)//情况1 x有右树 则x右孩子的左孩子(最最最左的孩子)就是后继节点
        {
            return getLeftMost(node->right);
        }
        else//情况23 x无右树 一路往上找 看这些节点是不是一个祖宗的左孩子 如果是 那么那个祖宗就是x的后继节点
        {
            Node *parent = node->parent;
            while(parent != NULL && parent -> left != NULL)
            {
                node = parent;
                parent = node->parent;
            }
            return parent;//如果parent是空 那么说明这个节点就是最后一个节点 则情况3也包含
        }
    }
};