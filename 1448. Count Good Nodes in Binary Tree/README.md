# 1448. Count Good Nodes in Binary Tree

## Question

Given a binary tree root, a node X in the tree is named good if in the path from root to X there are no nodes with a value greater than X.  

Return the number of good nodes in the binary tree.  

**Example 1:**  
Input: root = [3,1,4,3,null,1,5]  
Output: 4  
Root Node (3) is always a good node.  
Node 4 -> (3,4) is the maximum value in the path starting from the root.  
Node 5 -> (3,4,5) is the maximum value in the path  
Node 3 -> (3,1,3) is the maximum value in the path.  

**Example 2:**  
Input: root = [3,3,null,4,2]  
Output: 3  
Explanation: Node 2 -> (3, 3, 2) is not good, because "3" is higher than it.  

**Example 3:**  
Input: root = [1]  
Output: 1  
Explanation: Root is considered as good.  

**Constraints:**  
- The number of nodes in the binary tree is in the range [1, 10^5].
- Each node's value is between [-10^4, 10^4].

---
Date: 2024-11-20  
Start time: 15:03  

## Problem statement confirmation

- The binary tree has at least one node.
- The root node is always a good node.
- The value of a parent node can be equal to or less than that of a good child node.

Time checkpoint: 15:07  

## Solution idea

I will use a recursion DFS method to scan through the binary tree and find all good nodes.  

Firstly I will create a helper function, the input is the current node and the partial number of the good nodes. In the function, the function is called respectively for the left node and the right node of the current node, and finally the total number of the good nodes is returned.  

Time checkpoint: 15:13  

## Complexity analysis

Assume that the number of nodes in the binary tree is N.
- Time complexity: O(N) because I only scan through the binary tree once.
- Space complexity: O(height of the tree, H)? Since at most I need to store H partial numbers of good nodes in the recursion process.

Time checkpoint: 15:19  

## Implementation

```cpp
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
```

Time checkpoint: 15:37  

## Testing (dry run)

Example 1: Input: root = [3,1,4,3,null,1,5], Output: 4  
- solve(root(3), -10000)
- solve(node(1), 3) + solve(node(4), 3) + 1
- solve(node(3), 3) + solve(node(null), 3) + solve(node(1), 4) + solve(node(5), 4) + 2
- 1 + 0 + 0 + 1 + 2 = 4

Example 2: Input: root = [3,3,null,4,2], Output: 3  
- solve(root(3), -10000)
- solve(node(3), 3) + solve(node(null), 3) + 1
- solve(node(4), 3) + solve(node(2), 3) + 1 + 0 + 1
- 1 + 0 + 2 = 3

Example 3: Input: root = [1], Output: 1  
- solve(root(1), -10000) = solve(node(null), 1) + solve(node(null), 1) + 1 = 0 + 0 + 1 = 1

End time: 15:45  

## Results

Time spent: 42m  
Whether to refer to others' solutions: 有先複習 DFS 和 recursion  
Results of submission to Leetcode: Accepted  

## Review

- 複習如何實現 binary tree
- 寫 C++ 時，注意與 Python 不同，helper function 不可寫於主要解法的 function 中
- 注意 node value 下界