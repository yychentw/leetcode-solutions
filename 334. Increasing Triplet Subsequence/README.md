# 334. Increasing Triplet Subsequence

## Question

Given an integer array nums, return true if there exists a triple of indices (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k]. If no such indices exists, return false.  

**Example 1:**  
- Input: nums = [1,2,3,4,5]
- Output: true
- Explanation: Any triplet where i < j < k is valid.

**Example 2:**  
- Input: nums = [5,4,3,2,1]
- Output: false
- Explanation: No triplet exists.

**Example 3:**  
- Input: nums = [2,1,5,0,4,6]
- Output: true
- Explanation: The triplet (3, 4, 5) is valid because nums[3] == 0 < nums[4] == 4 < nums[5] == 6.

**Constraints:**  
- 1 <= nums.length <= 5 * 10^5
- -2^31 <= nums[i] <= 2^31 - 1

Follow up: Could you implement a solution that runs in O(n) time complexity and O(1) space complexity?  

---
Date: 2025-03-12  
Start time: 08:31  

## Problem statement confirmation

- Can the array with the length smaller than 3? Yes. In this case, no valid triplet exist.
- The elements of the array can be any integer.

Time checkpoint: 08:34  

## Solution idea

I would like to use 2 vectors: 1 vector storing prefix min, and another vector storing suffix max. Hence I need to firstly go through the nums twice to retrieve the prefix mins and suffix maxes.  

Then I can traverse nums from index 1 to index nums.size()-2, and check if nums[i] is larger than prefix_min[i-1] and smaller than suffix_max[i+1]. If yes, a valid triplet exists.  

Time checkpoint: 08:39  

## Complexity analysis

Assume that the length of nums is N:
- Time complexity: O(N) because I traverse the nums third times.
- Space complexity: O(N) because I use 2 vectors with the length N to store prefix mins and suffix maxes.

Time checkpoint: 08:41  

## Implementation

```cpp
class Solution {
public:
    bool validTriplet(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefix_min(n, 0);
        vector<int> suffix_max(n, 0);

        prefix_min[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefix_min[i] = min(prefix_min[i-1], nums[i]);
        }

        suffix_max[n-1] = nums[n-1];
        for (int i = n-2; i >= 0; i--) {
            suffix_max[i] = max(suffix_max[i+1], nums[i]);
        }

        for (int i = 1; i < n-1; i++) {
            if (nums[i] > prefix_min[i-1] && nums[i] < suffix_max[i+1]) {
                return true;
            }
        }
        return false;
    }
};
```

Time checkpoint: 08:47  

## Testing (dry run)

Example 1: Input: nums = [1,2,3,4,5]; Output: true
- prefix_min = [1,1,1,1,1]
- suffix_max = [5,5,5,5,5]
- i = 1, nums[i] = 2 > prefix_min[i-1] = 1 && nums[i] = 2 < suffix_max[i+1] = 5, return true

Example 2: Input: nums = [5,4,3,2,1]; Output: false
- prefix_min = [5,4,3,2,1]
- suffix_max = [5,4,3,2,1]
- i = 1, nums[i] = 4 < prefix_min[i-1] = 5 && nums[i] = 4 > suffix_max[i+1] = 3
- i = 2, nums[i] = 3 < prefix_min[i-1] = 4 && nums[i] = 3 > suffix_max[i+1] = 2
- i = 3, nums[i] = 2 < prefix_min[i-1] = 3 && nums[i] = 2 > suffix_max[i+1] = 1
- return false

Example 3: Input: nums = [2,1,5,0,4,6]; Output: true
- prefix_min = [2,1,1,0,0,0]
- suffix_max = [6,6,6,6,6,6]
- i = 1, nums[i] = 1 < prefix_min[i-1] = 2 && nums[i] = 1 < suffix_max[i+1] = 6
- i = 2, nums[i] = 5 > prefix_min[i-1] = 1 && nums[i] = 5 <> suffix_max[i+1] = 6, return true

End time: 08:54  

## Results

Time spent: 23m  
Whether to refer to others' solutions: Yes  
Results of submission to Leetcode:  

## Review

最近在基本的 string/array 題比較卡關，這題看了很久沒有好的想法，就決定先參考其他人的解法。  

其實有看到 one-pass 的解法，但這個解法不會找出正確的 triplet，只是輸出是否有 triplet 存在的結果是正確的，不好理解也很難跟人解釋，所以不太想採用。覺得結合 prefix_min 和 suffix_max 的方式雖然較慢，也使用較多空間，但比較能加強對演算法的理解。   

後來想到稍微改進的作法（少跑一次 loop）：
```cpp
class Solution {
public:
    bool validTriplet(vector<int>& nums) {
        int n = nums.size();
        vector<int> suffix_max(n, 0);

        suffix_max[n-1] = nums[n-1];
        for (int i = n-2; i >= 0; i--) {
            suffix_max[i] = max(suffix_max[i+1], nums[i]);
        }

        int prefix_min = nums[0];
        for (int i = 1; i < n-1; i++) {
            if (nums[i] > prefix_min && nums[i] < suffix_max[i+1]) {
                return true;
            }
            prefix_min = min(prefix_min, nums[i]);
        }
        return false;
    }
};
```