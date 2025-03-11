# 1679. Max Number of K-Sum Pairs

## Question

You are given an integer array nums and an integer k.  

In one operation, you can pick two numbers from the array whose sum equals k and remove them from the array.  

Return the maximum number of operations you can perform on the array.  

**Example 1:**  
- Input: nums = [1,2,3,4], k = 5
- Output: 2
- Explanation: Starting with nums = [1,2,3,4]:
    - Remove numbers 1 and 4, then nums = [2,3]
    - Remove numbers 2 and 3, then nums = []
    - There are no more pairs that sum up to 5, hence a total of 2 operations.

**Example 2:**  
- Input: nums = [3,1,3,4,3], k = 6
- Output: 1
- Explanation: Starting with nums = [3,1,3,4,3]:
    - Remove the first two 3's, then nums = [1,4,3]
    - There are no more pairs that sum up to 6, hence a total of 1 operation.

**Constraints:**  
- 1 <= nums.length <= 10^5
- 1 <= nums[i] <= 10^9
- 1 <= k <= 10^9

---
Date: 2025-03-11  
Start time: 09:19  

## Problem statement confirmation

- The array should not be empty.
- It is possible that the number of operations is 0 because we cannot find any pair sum equal to k?
- nums[i] are all positive.

Time checkpoint: 09:22  

## Solution idea

I will use a hash map to store nums[i] as key ans their occurences as value.  

But before inserting a new nums[i] to the hash map, I will check if k-nums[i] is in the hash map with its occurences > 0. If yes, the number of the operations is increased by 1, the occurences of k-nums[i] is decreased by 1, and nums[i] won't be inserted to the umap.  

After going through the whole array, return the total number of operations.  

Time checkpoint: 09:27  

## Complexity analysis

Assume that the length of the array is N:
- Time complexity: O(N) because I only go through the array once.
- Space complexity: O(N) because I store each of the elements in the hash map.

Time checkpoint: 09:28  

## Implementation

```cpp
class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        unordered_map<int, int> umap;
        int max_ops = 0;
        for (int n: nums) {
            int c = k - n;
            if (umap[c] > 0) {
                max_ops++;
                umap[c]--;
                continue;
            }
            umap[n]++;
        }
        return max_ops;
    }
};
```

Time checkpoint: 09:32  

## Testing (dry run)

Example 1: Input: nums = [1,2,3,4], k = 5; Output: 2
- n = 1, umap[4] == 0, max_ops = 0, umap = {1:1}
- n = 2, umap[3] == 0, max_ops = 0, umap = {1:1, 2:1}
- n = 3, umap[2] > 0, max_ops = 1, umap = {1:1, 2:0}
- n = 4, umap[1] > 0, max_ops = 2, umap = {1:0, 2:0}
- Return 2

Example 2: Input: nums = [3,1,3,4,3], k = 6; Output: 1
- n = 3, umap[3] == 0, max_ops = 0, umap = {3:1}
- n = 1, umap[5] == 0, max_ops = 0, umap = {3:1, 1:1}
- n = 3, umap[3] > 0, max_ops = 1, umap = {3:0, 1:1}
- n = 4, umap[2] == 0, max_ops = 1, umap = {3:0, 1:1, 4:1}
- n = 3, umap[3] == 0, max_ops = 1, umap = {3:1, 1:1, 4:1}
- Return 1

End time: 21:38  

## Results

Time spent: 19m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: Accepted  

## Review
