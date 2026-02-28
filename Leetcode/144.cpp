//先序遍历
#include <iostream>
#include <vector>
#include <stack>

using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
public:
    void process(TreeNode* node, vector<int>& res){
        if(node == nullptr){
            return;
        }
        res.push_back(node->val);
        process(node->left, res);
        process(node->right, res);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        process(root, res);
        return res;
    }
};
//迭代版本看Zuo_Tree UnRecur