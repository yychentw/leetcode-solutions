# 437. Path Sum III

## Question

Given the root of a binary tree and an integer targetSum, return the number of paths where the sum of the values along the path equals targetSum.  

The path does not need to start or end at the root or a leaf, but it must go downwards (i.e., traveling only from parent nodes to child nodes).  

**Example 1:**  
Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8  
Output: 3  
Explanation: [5,3], [5,2,1], [-3,11]

**Example 2:**  
Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22  
Output: 3  

**Constraints:**  
- The number of nodes in the tree is in the range [0, 1000].
- -10^9 <= Node.val <= 10^9
- -1000 <= targetSum <= 1000

---
Date: 2024-11-29  
Start time: 22:52  

## Problem statement confirmation

- The binary tree **can** be empty.
- The node value can be very large.... Should I consider integer overflow?

Time checkpoint: 22:58  

## Solution idea

Basic idea: DFS + prefix sum
- DFS: to traverse all possible paths
- predix sum: to calculate any sums along the paths

I need a helper function which:
1. calculate the prefix sum from the root to the current node
2. save prefixSum + targetSum (and its frequency) to the unordered map
3. check if prefixSum matches any key in the unordered map or is equal to targetSum
    - if yes, the answer += the frequency + left branch answer (recursion) + right branch answer (recursion)
    - if no, the answer += left branch answer (recursion) + right branch answer (recursion)

Call the helper function with prefix sum = 0, unordered_map {targetSum: 1}, ans = 0, and then return the answer.

Time checkpoint: 23:15  

## Complexity analysis

Assume that the number of nodes is N, the height of the tree is H:
- Time complexity: O(N) because I traverse the binary tree once.
- Space complexity: O(H) because I may need to save H prefix sums in the unordered map.

Time checkpoint: 23:17  

## Implementation

```cpp
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
    int checkSubPathSum(TreeNode* cur_node, int targetSum, int prefixSum, unordered_map<int, int>& umap) {
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

        return freq + left_res + right_res;
    }

    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<int, int> umap{{targetSum, 1}};
        return checkSubPathSum(root, targetSum, 0, umap);
    }
};
```

Time checkpoint: 23:51  

## Testing (dry run)

It's difficult to dry run tests on trees....  

End time: 23:58  

## Results

Time spent: 1h6m  
Whether to refer to others' solutions: 有重新複習 prefix sum 演算法和 unordered_map 的使用  
Results of submission to Leetcode: WA (QQ)  

## Review

### Unordered_map backtracking

Test case: root = [1,-2,-3], targetSum = -1  
- checkSubPathSum(root(1), -1, 0, umap{-1, 1})
- prefixSum = 0 + 1 = 1
- Because prefixSum(1) not in umap, freq = 0.
- targetPrefixSum = 1 - 1 = 0, umap{{-1, 1}, {0, 1}}
- Return 0 + checkSubPathSum(node(-2), -1, 1, umap{{-1, 1}, {0, 1}}) + checkSubPathSum(node(-3), -1, 1, umap{{-1, 1}, {0, 1}})
    - checkSubPathSum(node(-2), -1, 1, umap{{-1, 1}, {0, 1}}): prefixSum = 1 - 2 = -1, freq = 1, umap{{-1, 1}, {0, 1}, {-2, 1}}
    - checkSubPathSum(node(-3), -1, 1, umap{{-1, 1}, {0, 1}}) or checkSubPathSum(node(-3), -1, 1, umap{{-1, 1}, {0, 1}, {-2, 1}})?!

由於右支在左支後計算，umap 會包含左支的 targetPrefixSum，因此出現錯誤。  

必須在返回 parent node 後減去在 child node 增加的 frequency：
```cpp
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
    int checkSubPathSum(TreeNode* cur_node, int targetSum, int prefixSum, unordered_map<int, int>& umap) {
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

        umap[targetPrefixSum] = umap[targetPrefixSum] - 1;  // here!

        return freq + left_res + right_res;
    }

    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<int, int> umap{{targetSum, 1}};
        return checkSubPathSum(root, targetSum, 0, umap);
    }
};
```

### Unsigned integer overflow

這題確實會有 integer overflow 的問題，因此 prefix sum 要用 long 存：
```cpp
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
```

終於 accepted! Beats 100%～