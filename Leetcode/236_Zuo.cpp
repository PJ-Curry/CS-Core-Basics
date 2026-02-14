//二叉树中两个节点的最小祖先
#include<bits/stdc++.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL || root == p || root == q) {
            return root;
        }

        // 开始递归
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        // 左右两侧都有 则自己本身就是那个公共点
        if (left != NULL && right != NULL) {
            return root;
        }

        return left != NULL ? left : right; // 否则进入到这里 分到左右子树去 然后重新递归
    }
};