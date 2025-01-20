# 199. Binary Tree Right Side View

## Question

Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

**Example 1:**
- Input: root = [1,2,3,null,5,null,4]
- Output: [1,3,4]

**Example 2:**
- Input: root = [1,2,3,4,null,null,null,5]
- Output: [1,3,4,5]

**Example 3:**
- Input: root = [1,null,3]
- Output: [1,3]

**Example 4:**
- Input: root = []
- Output: []

**Constraints:**
- The number of nodes in the tree is in the range [0, 100].
- -100 <= Node.val <= 100

---
Date: 2025-01-20  
Start time: 22:29  

## Problem statement confirmation

- The number of nodes can be 0.

Time checkpoint: 22:31  

## Solution idea

The basic idea is to use DFS from the right to the left.  

A recursion helper function will firstly check the right branch, and then check the left branch. There is a integer parameter to record the depth, and a vector parameter to record the rightest nodes. The rightest nodes the first node that the function touch in the same depth level.

Time checkpoint: 22:37  

## Complexity analysis

Assume that the number of the nodes is N, and the height of the tree is H:
- Time complexity: O(N) because the solution will traverse all the nodes in the tree.
- Space complexity: O(H log H) (?) because the solution needs a vector parameter in the recursion.

Time checkpoint: 22:41  

## Implementation

```cpp
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
```

Time checkpoint: 22:52  

## Testing (dry run)

Example 1: Input: root = [1,2,3,null,5,null,4], Output: [1,3,4]
- Initialize: root, depth = 0, ans = []
- Since ans.size() == depth, depth = 1, ans = [1]
- Check: node(3), depth = 1, ans = [1]
- Since ans.size() == depth, depth = 2, ans = [1,3]
- Check: node(4), depth = 2, ans = [1,3]
- Since ans.size() == depth, depth = 3, ans = [1,3,4]
- Check: node(null), depth = 2, ans = [1,3,4]
- Since node == nullptr, do nothing
- Check: node(2), depth = 1, ans = [1,3,4], do nothing
- Check: node(5), depth = 2, ans = [1,3,4], do nothing
- Return: [1,3,4]

Example 2: Input: root = [1,2,3,4,null,null,null,5], Output: [1,3,4,5]
- Initialize: root, depth = 0, ans = []
- Since ans.size() == depth, depth = 1, ans = [1]
- Check: node(3), depth = 1, ans = [1]
- Since ans.size() == depth, depth = 2, ans = [1,3]
- Check: node(2), depth = 1, ans = [1,3], depth++
- Check: node(4), depth = 2, ans = [1,3]
- Since ans.size() == depth, depth = 3, ans = [1,3,4]
- Check: node(5), depth = 3, ans = [1,3,4]
- Since ans.size() == depth, depth = 4, ans = [1,3,4,5]
- Return: [1,3,4,5]

Example 3: Input: root = [1,null,3], Output: [1,3]
- Initialize: root, depth = 0, ans = []
- Since ans.size() == depth, depth = 1, ans = [1]
- Check: node(3), depth = 1, ans = [1]
- Since ans.size() == depth, depth = 2, ans = [1,3]
- Return: [1,3]

Example 4: Input: root = [], Output: []
- Initialize: root, depth = 0, ans = []
- Since root == nullptr, do nothing
- Return: []

End time: 23:05  

## Results

Time spent: 36m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: Accepted  

## Review

None