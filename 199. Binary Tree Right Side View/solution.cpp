#include<vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) {}
};

class Solution {
public:
    void checkRightSideView(TreeNode* node, int depth, vector<int>& ans) {
        if (node == nullptr) {
            return;
        }

        if (ans.size() == depth) {
            ans.push_back(node->val);
        }
        
        depth += 1;
        checkRightSideView(node->right, depth, ans);
        checkRightSideView(node->left, depth, ans);
    }

    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans{};
        checkRightSideView(root, 0, ans);
        return ans;
    }
};