//297的另外一种方法 反序列化直接对字符串处理 字符串转化成数字
#include<bits/stdc++.h>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

class Codec{
public:
    //1.序列化 _#形式
    string serialize(TreeNode *root)
    {
        if(root == NULL) return "#_";
        string res = to_string(root->val) + "_";
        res += serialize(root->left);
        res += serialize(root->right);
        return res;
    }

    //2.反序列化入口 不再用队列 传递字符串和初始指向下标
    TreeNode* deserialize(string data)
    {
        int u = 0;
        return reconPreorder(data, u);
    }
private:
    TreeNode* reconPreorder(const string &data, int &u)//u是游标
    {
        if(u >= data.length()) return NULL;//游标越界 直接结束
        
        //情况1 遇见#说明是空节点
        if(data[u] == '#')
        {
            u += 2;
            return NULL;
        }

        //情况2 遇到数字 则把字符数字转换成真正的数字
        
    }
};