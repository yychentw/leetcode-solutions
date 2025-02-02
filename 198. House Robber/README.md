# 198. House Robber

## Question

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.  

Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.  

**Example 1:**
- Input: nums = [1,2,3,1]
- Output: 4
- Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3). Total amount you can rob = 1 + 3 = 4.

**Example 2:**
- Input: nums = [2,7,9,3,1]
- Output: 12
- Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1). Total amount you can rob = 2 + 9 + 1 = 12.

**Constraints:**
- 1 <= nums.length <= 100
- 0 <= nums[i] <= 400

---
Date: 2025-02-02  
Start time: 10:54  

## Problem statement confirmation

- There's at least 1 house.
- The amount of money should be non-negative.
- Integer overflow is impossible.

Time checkpoint: 10:57  

## Solution idea

I would use recursion to split the task into sub-tasks:
maxRobbedMoney(nums) = max(nums[0]+maxRobbedMoney(nums[2:]), nums[1]+maxRobbedMoney(nums[3:]))

Time checkpoint: 11:00  

## Complexity analysis

Not sure how to estimate the complexity.... I will get back later.

Time checkpoint: 11:01  

## Implementation

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }

        if (nums.size() == 1) {
            return nums[0];
        }

        int res1 = nums[0];
        if (nums.size() > 2) {
            vector<int> sv(nums.begin()+2, nums.end());
            res1 += rob(sv);
        }

        int res2 = nums[1];
        if (nums.size() > 3) {
            vector<int> sv(nums.begin()+3, nums.end());
            res2 += rob(sv);
        }

        return max(res1, res2);
    }
};
```

Time checkpoint: 11:14  

## Testing (dry run)

Example 1: Input: nums = [1,2,3,1], Output: 4
- nums.size() >= 2
- res1 = 1 + rob([3,1]) = 1 + max(3, 1) = 4
- res2 = 2 + rob([1]) = 2 + 1 = 3
- return max(res1, res2) = 4

Example 2: Input: nums = [2,7,9,3,1], Output: 12
- nums.size() >= 2
- res1 = 2 + rob([9,3,1]) = 2 + max(9+rob([1]), 3) = 2 + 10 = 12
- res2 = 7 + rob([3,1]) = 7 + max(3, 1) = 10
- return max(res1, res2) = 12

My test case: Input: nums=[1,30,2,2,36], Output: 66
- nums.size() >= 2
- res1 = 1 + rob([2,2,36]) = 1 + max(2+rob[36], 2) = 1 + 38 = 39
- res2 = 30 + rob([2,36]) = 30 + max(2, 36) = 30 + 36 = 66
- return max(res1, res2) = 66

End time: 11:21  

## Results

Time spent: 27m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: MLE....  

## Review

雖然 recursion 能解這個問題，但是產生大量的 subvector 會導致高 memory complexity，應該從 iteration 的方向考慮。  

除此之外，我們可以簡化 DP 的定義為截至第 i 間房子最大的 rob 收益：  
dp[i] = max(dp[i-1], nums[i]+dp[i-2])  
前項代表跳過這間房子的收益，後項代表 rob 這間房子的收益。  

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 1) {
            return nums[0];
        }

        vector<int> dp(n, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        
        for (int i = 2; i < n; ++i) {
            dp[i] = max(dp[i-1], nums[i]+dp[i-2]);
        }
        return dp[n-1];
    }
};
```

算法複雜度也變得比較好評估（假設房子數量為 N）：
- Time complexity: O(N)
- Space complexity: O(N)

然而，從前面的解法可以注意到，我們不需要記住所有 DP 計算出來的結果，真正需要的只有 dp[i-1] 和 dp[i-2]。  

因此，我們可以進一步改善解法如下：
```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 1) {
            return nums[0];
        }

        int prev = nums[0];
        int prevmax = max(nums[0], nums[1]);
        
        for (int i = 2; i < n; ++i) {
            int temp = max(prevmax, nums[i]+prev);
            prev = prevmax;
            prevmax = temp;
        }
        return prevmax;
    }
};
```

算法複雜度（假設房子數量為 N）：
- Time complexity: O(N)
- Space complexity: O(1)