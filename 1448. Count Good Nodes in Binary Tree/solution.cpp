struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {}
};

class Solution {
public:
    int solve(TreeNode* cur, int cur_max) {
        if (cur == nullptr) {
            return 0;
        }

        if (cur->val >= cur_max) {
            // the current node is a good node
            int leftGoodNodes = solve(cur->left, cur->val);
            int rightGoodNodes = solve(cur->right, cur->val);
            return leftGoodNodes + rightGoodNodes + 1;
        }
        else {
            // the current node is not a good node
            int leftGoodNodes = solve(cur->left, cur_max);
            int rightGoodNodes = solve(cur->right, cur_max);
            return leftGoodNodes + rightGoodNodes;
        }
    }

    int goodNodes(TreeNode* root) {
        return solve(root, -10000);
    }
};