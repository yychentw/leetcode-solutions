# 1372. Longest ZigZag Path in a Binary Tree

## Question

You are given the root of a binary tree.  

A ZigZag path for a binary tree is defined as follow:  
- Choose any node in the binary tree and a direction (right or left).
- If the current direction is right, move to the right child of the current node; otherwise, move to the left child.
- Change the direction from right to left or from left to right.
- Repeat the second and third steps until you can't move in the tree.
- Zigzag length is defined as the number of nodes visited - 1. (A single node has a length of 0).

Return the longest ZigZag path contained in that tree.  

**Example 1:**  
- Input: root = [1,null,1,1,1,null,null,1,1,null,1,null,null,null,1]
- Output: 3

**Example 2:**  
- Input: root = [1,1,1,null,1,null,null,1,1,null,1]
- Output: 4

**Example 3:**  
- Input: root = [1]
- Output: 0

**Constraints:**  
- The number of nodes in the tree is in the range [1, 5 * 10^4].
- 1 <= Node.val <= 100

---
Date: 2024-12-08  
Start time: 17:48  

## Problem statement confirmation

- The binary tree should have at least 1 node, and the ZigZag path is 0.

Time checkpoint: 17:50  

## Solution idea

Recursive DFS: 
Define a helper function which accepts the inputs of the current node and the current ZigZag path length, apply the helper function for the left and right child nodes, and return the max output of the helper function for the child nodes.  
If the current node does not have any child node, return the current longest ZigZag path length.  

Time checkpoint: 17:59  

## Complexity analysis

Assume that the number of nodes in the binary tree is N, and the height of the tree is H:
- Time complexity: O(N) because I traverse all the nodes once.
- Space complexity: O(H) because the solution needs to store H current ZigZag path length in the recursion process.

Time checkpoint: 18:05  

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
```

- Need direction information.

Time checkpoint: 18:22  

## Testing (dry run)

Detected issues:
1. Did not handle null left / right child node
2. zigzaglen computation is not correct.

Must check:
- root = [1]
- root = [1,1,null,null,1]
- root = [1,1,null,1,null]
- root = [1,1,null,1,null,null,1,1,null]

End time: 19:01  

## Results

Time spent: 1h13m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: Accepted  

## Review

None