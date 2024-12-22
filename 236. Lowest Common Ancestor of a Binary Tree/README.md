# 236. Lowest Common Ancestor of a Binary Tree

## Question

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.  

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow **a node to be a descendant of itself**).”  

**Example 1:**  
- Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
- Output: 3

**Example 2:**  
- Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
- Output: 5
- Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

**Example 3:**  
- Input: root = [1,2], p = 1, q = 2
- Output: 1

**Constraints:**  
- The number of nodes in the tree is in the range [2, 10^5].
- -10^9 <= Node.val <= 10^9
- All Node.val are unique.
- p != q
- p and q will exist in the tree.

---
Date: 2024-12-22  
Start time: 15:29  

## Problem statement confirmation

- All node values are unique.
- p and q must exist in the tree.
- It is guaranteed that p is not equal to q.
- A node can be a descendant of itself.
- The absolute value of a node can be quite large, but we don't need to consider integer overflow in this case because this is not related to integer operations.
- The number of nodes can be large. That is to say, a solution with linear complexity is reauired.

Time checkpoint: 15:37  

## Solution idea

Although I have no clear idea for now, but I try to think out loud as below:  
- Use DFS to find p or q.
- For example, if we firstly find p, then all nodes from root to p can be LCA of p and q.
- Keep using DFS to traverse the tree until q is found.
- I may use some flags to record if p is found and if q is found so that the function can check whether some conditions are met in the recursion.
- But how? I think I need to write a helper function to record if the current node is ancestor of p and q, and once found, return the node.

Therefore, the helper function should include the following steps:
- Check whether the current node is null. If null, return false, false.
- Check whether the current node is p. If yes, return true, false. Similarly, if current node is q, return false, true.
- If the function given any child node outputs true for finding p/q, the parent node should also output true for finding p/q.
- If a node return true, true, record the node in the output parameter. The default output parameter is a null node.
- If the output node is not null, return true, true and skip all the following traversing. 

Then, we can return the output node in the main function.

Time checkpoint: 16:08  

## Complexity analysis

Assume that the number of the nodes is N, the height of the tree is H:
- Time complexity: O(N) because the solution only traverse the tree once.
- Space complexity: O(H) because when the helper function visits the deepest node, there are H x 3 (found_p_flag, found_q_flag, LCA) variables in the memory. 

Time checkpoint: 16:12  

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
    TreeNode* checkLCA(TreeNode* curr, TreeNode* p, TreeNode* q, pair<bool, bool>& flags) {
        if (curr == nullptr) {
            return nullptr;
        }

        pair<bool, bool> left_flags = make_pair(false, false);
        pair<bool, bool> right_flags = make_pair(false, false);
        TreeNode* left_ret = checkLCA(curr->left, p, q, left_flags);
        TreeNode* right_ret = checkLCA(curr->right, p, q, right_flags);

        if (left_ret != nullptr) {
            return left_ret;
        }
        if (right_ret != nullptr) {
            return right_ret;
        }

        if (curr->val == p->val || left_flags.first || right_flags.first) {
            flags.first = true;
        }
        if (curr->val == q->val || left_flags.second || right_flags.second) {
            flags.second = true;
        }

        if (flags.first && flags.second) {
            return curr;
        }

        return nullptr;
    }

    TreeNode* lowestCommonAncestor(TreeNode* head, TreeNode* p, TreeNode* q) {
        pair<bool, bool> flags(false, false);
        return checkLCA(head, p, q, flags);
    }
};
```

Time checkpoint: 16:41  

## Testing (dry run)

Example 3: Input: root = [1,2], p = 1, q = 2, Output: 1
- Input: curr = node(1), p = node(1), q = node(2), flags = (false, false)
    - Input: curr = node(2), p = node(1), q = node(2), flags = (false, false) -> Output: nullptr, flags = (false, true)
    - Input: curr = null, p = node(1), q = node(2), flags = (false, false) -> Output: nullptr, flags = (false, false)
- Output: node(1), flags = (true, true)

For Examples 1 & 2, I verify the answer through drawing tree on paper.

End time: 16:54  

## Results

Time spent: 1h25m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: Accepted  

## Review

雖然有解出來，但想得太複雜了。其實只要在分支遇到 p 或 q 時回傳該 node，然後在分支結果都不是 nullptr 時回傳當時的 node 作為最終結果即可。  

這個解法乍看有點不直覺，但試想 LCA 只會出現在兩種情況：
1. 兩個同階層的分支分別包含 p 和 q，因此他們的 parent node 為 LCA
2. 一個 subtree 的 root 為 p/q，而底下包含 q/p，因此 p/q 為 LCA

因此解題步驟為：
1. 檢查 root 是否為 p 或 q，如果是，其一定為 LCA
2. 分別檢查 left 和 right 是否包含 p 或 q，是就回傳該 node
3. 如果 left 和 right 都回傳非 null 的 node，代表 root 為 LCA
4. 如果只有 left 輸出為非 null，則 left 輸出為 LCA
5. 相同的，如果只有 right 輸出為非 null，則 right 輸出為 LCA

Tree 底下的任意 subtree 也適用此規則。

Implementation: 
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
```