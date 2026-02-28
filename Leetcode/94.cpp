//迭代版本的中序遍历 94题（简单）
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode *cur = root;
        stack<TreeNode*> st;
        
        while(!st.empty() || cur != nullptr){
            if(cur != nullptr){
                st.push(cur);
                cur = cur->left;
            }
            else{
                cur = st.top();
                st.pop();
                res.push_back(cur->val);//不能写输出 要存到那个vector数组里
                cur = cur->right;
            }
        }
        return res;
    }
};

int main() {
    // 【建树】手动捏一棵力扣最经典的测试树：
    //      1
    //       \
    //        2
    //       /
    //      3
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);

    // 【调用】实例化你的题解类，并传入树根
    Solution sol;
    vector<int> result = sol.inorderTraversal(root);

    // 【验证】打印你的收集袋里的结果
    cout << "你写的中序遍历结果是: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl; // 正确答案应该是: 1 3 2

    // 【打扫战场】C++ 程序员的修养，用完 new 记得 delete
    delete root->right->left;
    delete root->right;
    delete root;

    return 0;
}