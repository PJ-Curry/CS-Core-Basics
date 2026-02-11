//二叉树遍历 深度优先 广度优先
//广度优先 树+队列
#include<iostream>
#include<unordered_map>
#include<queue>
using namespace std;
struct Node
{
    char data;
    Node *left;
    Node *right;
};
//什么时候用void函数 当你不需要产生数据 只需要完成一个运算或动作 就用void
void LevelOrder(Node *root)
{
    if(root==NULL) return;
    queue<Node*> Q;//创建一个指向节点的指针队列
    Q.push(root);
    while(!Q.empty())//只要至少存在一个已经发现的节点
    {
        Node *current=Q.front();
        cout<<current->data<<" ";
        if(current->left!=NULL) Q.push(current->left);
        if(current->right!=NULL) Q.push(current->right);
        Q.pop();//移除前端元素
    }
    //看起来没有递归 当同一层有很多个节点 还怎么向下遍历 这是队列在起作用 自己写写看就好了
}

//插入节点
Node *Insert(Node *root,char data)
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

//统计树中的最大宽度 很多种方法 
//方法1：GPT版 队列大小法 最简单的一种方法了
int LevelOrderMaxWidth(Node *root)
{
    if(root==NULL); return 0;
    queue<Node*> Q;
    Q.push(root);
    int maxWidth=0;
    while(!Q.empty())
    {
        int sz=Q.size();//统计一个层中的个数 即宽度 这块和for循环是分割开的 
        //所以不用考虑队列中 上层下层同时在队列中而算错数的情况
        maxWidth=max(sz,maxWidth);
        for(int i=0;i<sz;i++)//while(sz--)也可以
        {
            Node *current=Q.front();
            Q.pop();
            if(current->left) Q.push(current->left);
            if(current->right) Q.push(current->right);
        }
    }
    cout<<"\n";
    return maxWidth;
}

//方法2：层尾指针法
int MaxWidth_EndMarkers(Node *root)
{
    if(!root) return 0;
    queue<Node*> q;
    q.push(root);
    Node *curEnd=root;
    Node *nextEnd=NULL;
    int curCnt=0,ans=0;//curCnt是当前层正在数数查到的节点数，ans是层的最大值
    while(!q.empty())
    {
        Node *cur=q.front();
        q.pop();
        curCnt++;
        if(cur->left) q.push(cur->left); nextEnd=cur->left;//只要有下一层的节点了就要更新nextEnd指针
        if(cur->right) q.push(cur->right); nextEnd=cur->right;//要更往右移 才会更靠近End
        
        if(cur==curEnd)
        {
            ans=max(ans,curCnt);
            curCnt=0;
            curEnd=nextEnd;
            nextEnd=NULL;
        }
    }
    return ans;
}

//方法3 哈希表映射法 用哈希表记录每一个对应节点所在层数
int MaxWidth_HashMap(Node *root)
{
    if(!root) return 0;
    queue<Node*>q;
    q.push(root);
    unordered_map<Node*,int>level;
    level[root]=1;
    int curLevel=1,curCnt=0,ans=0;//当前层 当前层节点数 到目前为止的最大宽度
    while(!q.empty())
    {
        Node *cur=q.front();
        q.pop();
        int lv=level[cur];//查哈希表 取出当前节点的层号

        if(lv==curLevel)//还是在这一层 这一层的计数器++
        {
            curCnt++;
        }
        else
        {
            ans=max(ans,curCnt);//结算上一层
            curLevel=lv;//把层号更新成新层
            curCnt=1;//当前节点是新层的第一个节点
        }

        if(cur->left){ level[cur->left] = lv+1; q.push(cur->left);}//孩子节点 层数要+1
        if(cur->right){ level[cur->right] = lv+1; q.push(cur->right);}

    }
    ans=max(ans,curCnt);
    return ans;
}

//方法4 使用两层的end指针 来解决哈希表空间复杂度为O(n)的问题 其实就是方法2 一样的 只不过重新听课就再写了一遍
int MaxWidth_NoMap_Pointer(Node *root)
{
    if(!root) return 0;
    queue<Node*>q;
    q.push(root);

    Node* curEnd = root;//当前层的尾节点
    Node* nextEnd = NULL;//下一层的尾节点
    int curLevelNodes = 0;//当前层节点数
    int maxW = 0;

    while(!q.empty())
    {
        Node* cur = q.front();
        q.pop();

        if(cur->left != NULL)
        {
            q.push(cur->left);
            nextEnd = cur->left;
        }
        if(cur->right != NULL)
        {
            q.push(cur->right);
            nextEnd = cur->right;
        }
        curLevelNodes++;//当前层节点数+1

        if(cur == curEnd)
        {
            maxW = max(maxW,curLevelNodes);

            curLevelNodes = 0;
            curEnd = nextEnd;
        }
    }
    return  maxW;
}

int main()
{
    /* tree
        M
       / \
      B   Q
     / \   \
    A   C   Z
    */
    Node *root=NULL;
    root = Insert(root,'M'); root = Insert(root,'B');
	root = Insert(root,'Q'); root = Insert(root,'Z'); 
	root = Insert(root,'A'); root = Insert(root,'C');
    LevelOrder(root);
    cout<<LevelOrderMaxWidth(root)<<endl;
    cout<<MaxWidth_EndMarkers(root)<<endl;
    cout<<MaxWidth_HashMap(root)<<endl;
}
//Time-complexity O(n)
//Space-complexity Worst/Average:O(n) Best:O(1)