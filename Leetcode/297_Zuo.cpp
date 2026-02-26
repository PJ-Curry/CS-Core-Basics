//二叉树的序列化和反序列化
#include<bits/stdc++.h>
using namespace std;
struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Codec {
public:
    // Encodes a tree to a single string.序列化
    string serialize(TreeNode* root) {
        if (root == NULL) {
            return "#_";
        }
        // 先序遍历
        string res = to_string(root->val) + "_"; // to_string 把数字转化为字符串
        res += serialize(root->left);
        res += serialize(root->right);
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(
        string data) { // 把字符串切碎进入队列 java里可以直接data_split("_")
        queue<string> q;
        stringstream ss(data); // 变成字符串流
        string item;

        while (getline(ss, item, '_')) {
            q.push(item);
        }

        return reconPreorder(q);
    }

private:
    TreeNode*
    reconPreorder(queue<string>& q) // 要采用引用传递 不能值传递(传复印件)
    {
        if (q.empty())
            return NULL;

        // 抓住队首元素 出队
        string val = q.front();
        q.pop();

        if (val == "#") {
            return NULL;
        }
        TreeNode* head =
            new TreeNode(stoi(val)); // 把字符串转化为整数 和to_string对应

        head->left = reconPreorder(q);
        head->right = reconPreorder(q);

        return head;
    }
};