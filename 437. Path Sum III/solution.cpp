#include <unordered_map>
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
    int checkSubPathSum(TreeNode* cur_node, int targetSum, long prefixSum, unordered_map<long, int>& umap) {
        if (cur_node == nullptr) {
            return 0;
        }

        prefixSum = prefixSum + cur_node->val;
        int freq = 0;
        if (umap.find(prefixSum) != umap.end()) {
            freq = umap[prefixSum];
        }

        int targetPrefixSum = prefixSum + targetSum;
        if (umap.find(targetPrefixSum) == umap.end()) {
            umap[targetPrefixSum] = 1;
        }
        else {
            umap[targetPrefixSum] = umap[targetPrefixSum] + 1;
        }

        int left_res = checkSubPathSum(cur_node->left, targetSum, prefixSum, umap);
        int right_res = checkSubPathSum(cur_node->right, targetSum, prefixSum, umap);

        umap[targetPrefixSum] = umap[targetPrefixSum] - 1;

        return freq + left_res + right_res;
    }

    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<long, int> umap{{targetSum, 1}};
        return checkSubPathSum(root, targetSum, 0, umap);
    }
};