#include <queue>
using namespace std;

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
    int maxLevelSum(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        int level = 1;
        int max_sum = root->val;
        int max_sum_level = 1;
        while (!q.empty()) {
            int level_sum = 0;
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                level_sum = level_sum + q.front()->val;
                if (q.front()->left != nullptr) {
                    q.push(q.front()->left);
                }
                if (q.front()->right != nullptr) {
                    q.push(q.front()->right);
                }
                q.pop();
            }
            if (level_sum > max_sum) {
                max_sum = level_sum;
                max_sum_level = level;
            }
            ++level;
        }
        return max_sum_level;
    }
};