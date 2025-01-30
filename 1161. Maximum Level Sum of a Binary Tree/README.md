# 1161. Maximum Level Sum of a Binary Tree

## Question

Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.  

Return the smallest level x such that the sum of all the values of nodes at level x is maximal.  

**Example 1:**
- Input: root = [1,7,0,7,-8,null,null]
- Output: 2
- Explanation: 
    - Level 1 sum = 1.
    - Level 2 sum = 7 + 0 = 7.
    - Level 3 sum = 7 + -8 = -1.
    - So we return the level with the maximum sum which is level 2.

**Example 2:**
- Input: root = [989,null,10250,98693,-89388,null,null,null,-32127]
- Output: 2

**Constraints:**
- The number of nodes in the tree is in the range [1, 10^4].
- -10^5 <= Node.val <= 10^5

---
Date: 2025-01-30  
Start time: 21:22  

## Problem statement confirmation

- Integer overflow? No, because the sum should be in the range [-10^9, 10^9].
- The tree cannot be empty.

Time checkpoint: 21:25  

## Solution idea

I would use BFS to calculate the sum of each level from the root to the leaves, and then find the smallest level with the maximal level sum.  

I may use 2 queues to store the parent-level nodes and the child-level nodes. Everytime a parent-level node is popped, all its child nodes will be pushed to the child-level queue. After all parent nodes are popped and the level sum is calculated, check if the level sum is maximal, and then let the child-level queue to be the new parent-level queue.

Time checkpoint: 21:32  

## Complexity analysis

Assume that the number of the nodes in the tree is N, the breadth of the tree is B:
- Time complexity: O(N) because the solution will traverse all the nodes in the tree.
- Space complexity: O(B) because the number of the nodes stored in the queues is related to the tree's breadth (?).

Time checkpoint: 21:35  

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
    int maxLevelSum(TreeNode* root) {
        queue<TreeNode*> parent;
        parent.push(root);
        int level = 1;
        int max_sum = 0;
        int max_sum_level = 1;
        while (!parent.empty()) {
            int level_sum = 0;
            queue<TreeNode*> child;
            while (!parent.empty()) {
                if (parent.front() != nullptr) {
                    level_sum = level_sum + parent.front()->val;
                    child.push(parent.front()->left);
                    child.push(parent.front()->right);
                }
                parent.pop();
            }
            if (level_sum > max_sum) {
                max_sum = level_sum;
                max_sum_level = level;
            }
            parent = child;
            ++level;
        }
        return max_sum_level;
    }
};
```

Time checkpoint: 21:53  

## Testing (dry run)

Example 1: Input: root = [1,7,0,7,-8,null,null], Output: 2
- level=1, parent=[1] -> parent=[], level_sum=1, child=[7,0] -> max_sum=1, max_sum_level=1
- level=2, parent=[7,0] -> parent=[0], level_sum=7, child=[7,-8] -> parent=[], level_sum=7, child=[7,-8,null,null] -> max_sum=7, max_sum_level=2
- level=3, parent=[7,-8,null,null] -> parent=[-8,null,null], level_sum=7, child=[null,null] -> parent=[null,null], level_sum=-1, child=[null,null,null,null] -> parent=[], level_sum=-1, child=[null,null,null,null] -> max_sum=7, max_sum_level=2
- level=4, parent=[null,null,null,null] -> parent=[], level_sum=0, child=[] -> max_sum=7, max_sum_level=2
- Return 2

Example 2: Input: root = [989,null,10250,98693,-89388,null,null,null,-32127], Output: 2
- level=1, parent=[989] -> parent=[], level_sum=989, child=[null,10250] -> max_sum=989, max_sum_level=1
- level=2, parent=[null,10250] -> parent=[], level_sum=10250, child=[98693,-89388] -> max_sum=10250, max_sum_level=2
- level=3, parent=[98693,-89388] -> parent=[], level_sum=9305, child=[null,null,null,-32127] -> max_sum=10250, max_sum_level=2
- level=3, parent=[null,null,null,-32127] -> parent=[], level_sum=-32127, child=[null,null] -> max_sum=10250, max_sum_level=2
- Return 2

End time: 22:07  

## Results

Time spent: 45m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: WA (Note that the maximal level sum can be negative QQ)  

## Review

Revised solution:
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
    int maxLevelSum(TreeNode* root) {
        queue<TreeNode*> parent;
        parent.push(root);
        int level = 1;
        int max_sum = root->val;
        int max_sum_level = 1;
        while (!parent.empty()) {
            int level_sum = 0;
            queue<TreeNode*> child;
            while (!parent.empty()) {
                if (parent.front() != nullptr) {
                    level_sum = level_sum + parent.front()->val;
                    if (parent.front()->left != nullptr) {
                        child.push(parent.front()->left);
                    }
                    if (parent.front()->right != nullptr) {
                        child.push(parent.front()->right);
                    }
                }
                parent.pop();
            }
            if (level_sum > max_sum) {
                max_sum = level_sum;
                max_sum_level = level;
            }
            parent = child;
            ++level;
        }
        return max_sum_level;
    }
};
```

基本上使用 queue 的方向是正確的，但我們其實只需要一個 queue 就好：
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
```