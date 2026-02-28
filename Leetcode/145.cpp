//后序遍历 用双栈 st1：根左右的往里存入 弹出时候就是根右左 放进st2 弹出就是左右根
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
    vector<int> postorderTraversal(TreeNode* root){
        vector<int> res;
        if(root == nullptr){
            return res;
        }

        stack<TreeNode*> st1;
        stack<TreeNode*> st2;

        st1.push(root);
    
        while(!st1.empty()){
            TreeNode *cur = st1.top();
            st1.pop();
            st2.push(cur);//st1中弹出后就放进st2里

            if(cur->left != nullptr){
                st1.push(cur->left);
            }
            if(cur->right != nullptr){
                st1.push(cur->right);
            }
        }

        while(!st2.empty()){
                res.push_back(st2.top()->val);
                st2.pop();
        }
        return res;
    }
};