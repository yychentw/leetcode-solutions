struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {}
};

class Solution {
    TreeNode* lowestCommonAncestor(TreeNode* head, TreeNode* p, TreeNode* q) {
        if (head == nullptr) {
            return nullptr;
        }

        if (head == p || head == q) {
            return head;
        }

        TreeNode* left_ret = lowestCommonAncestor(head->left, p, q);
        TreeNode* right_ret = lowestCommonAncestor(head->right, p, q);
        if (left_ret != nullptr && right_ret != nullptr) {
            return head;
        }
        else if (left_ret != nullptr) {
            return left_ret;
        }
        return right_ret;
    }
};