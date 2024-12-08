#include <algorithm>
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
    int findCurrentLongestZigZag(TreeNode* curr, int zigzaglen, bool fromLeft) {
        if (curr == nullptr) {
            return zigzaglen;
        }

        int left_len, right_len;
        if (fromLeft) { // should go right to achieve zigzag path
            left_len = findCurrentLongestZigZag(curr->left, 0, true);
            right_len = findCurrentLongestZigZag(curr->right, zigzaglen+1, false);
        }
        else {
            left_len = findCurrentLongestZigZag(curr->left, zigzaglen+1, true);
            right_len = findCurrentLongestZigZag(curr->right, 0, false);
        }
        return max(left_len, right_len);
    }

    int longestZigZag(TreeNode* root) {
        return max(findCurrentLongestZigZag(root->left, 0, true), findCurrentLongestZigZag(root->right, 0, false));
    }
};