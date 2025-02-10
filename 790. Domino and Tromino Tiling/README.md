# 790. Domino and Tromino Tiling

## Question

You have two types of tiles: a 2 x 1 domino shape and a tromino shape. You may rotate these shapes.  

Given an integer n, return the number of ways to tile an 2 x n board. Since the answer may be very large, return it modulo 10^9 + 7.  

In a tiling, every square must be covered by a tile. Two tilings are different if and only if there are two 4-directionally adjacent cells on the board such that exactly one of the tilings has both squares occupied by a tile.  

**Example 1:**
- Input: n = 3
- Output: 5

**Example 2:**
- Input: n = 1
- Output: 1

**Constraints:**
- 1 <= n <= 1000

---
Date: 2025-02-02  
Start time: 13:22  

## Problem statement confirmation

- n should be equal to or larger than 1.

Time checkpoint: 13:22  

## Solution idea

Any pattern?
- n = 1, ans = 1
- n = 2, ans = 1 + 1 = 2
- n = 3, ans = 1 * 2 + 3 = 5
- n = 4, ans = 1 * 5 + 2 * 2 + 3 = 12
- ...

dp[n] = dp[1] * dp[n-1] + dp[2] * dp[n-2] + ... + 3  

And note that we should return dp[n]%(10^9 + 7).  

Time checkpoint: 13:29  

## Complexity analysis

- Time complexity: O(N^2)? We calculate the DP results from 0 to N iteratively, and to calculate each result, we should go through all of the current vector.
- Space complexity: O(N) because a vector with size N is used to store the DP results.

Time checkpoint: 13:34  

## Implementation

```cpp
class Solution {
public:
    int numTilings(int n) {
        int m = 1000000007;
        
        if (n == 1) {
            return 1;
        }

        vector<int> dp(n+1, 0);
        dp[1] = 1;
        dp[2] = 2;
        
        for (int i = 3; i <= n; ++i) {
            int half = i/2;
            if (i % 2 == 1) {
                half = (i-1)/2;
            }
            for (int j = 1; j <= half; ++j) {
                dp[i] += (dp[j]%m) * (dp[i-j]%m);
            }
            dp[i] += 3;
        }
        return dp[n];
    }
};
```

Time checkpoint: 13:46  

## Testing (dry run)

Example 1: Input: n = 3, Output: 5
- n > 1, dp = [0,1,2]
- i = 3, dp[3] = 1 * 2 + 2 = 5
- return 5

Example 2: Input: n = 1, Output: 1
- n == 1, return 1

End time: 13:48  

## Results

Time spent: 26m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: WA（沒抓到正確的規律QQ）  

## Review

DP 的重點：
- 找出足夠的 base cases
- 找出前後相關的公式

### Solution 1

直觀但向量處理比較複雜的解法。

DP vector 除了記錄到第 i 個 column 的鋪磁磚方法數，還會分成三個 state：
- state = 0：剛好鋪滿
- state = 1：鋪到第 i 個 column 的第一列（但第二列為空）
- state = 2：鋪到第 i 個 column 的第二列（但第一列為空）

因此 DP 關係式如下：
dp[i][0] = dp[i-1][0] + dp[i-2][0] + dp[i-2][1] + dp[i-2][2]
dp[i][1] = dp[i-1][0] + dp[i-1][2]
dp[i][2] = dp[i-1][0] + dp[i-1][1]

```cpp
class Solution {
public:
    int numTilings(int n) {
        int m = 1000000007;

        if (n == 1) {
            return 1;
        }

        if (n == 2) {
            return 2;
        }

        vector< vector<int> > dp(n+1, vector<int>(3, 0));
        dp[1][0] = 1;
        dp[2][0] = 2;
        dp[1][1] = 1;
        dp[1][2] = 1;
        dp[2][1] = 2;
        dp[2][2] = 2;

        for (int i = 3; i <= n; ++i) {
            dp[i][0] = dp[i-1][0]%m + dp[i-2][0]%m + dp[i-2][1]%m + dp[i-2][2]%m;
            dp[i][1] = dp[i-1][0]%m + dp[i-1][2]%m;
            dp[i][2] = dp[i-1][0]%m + dp[i-1][1]%m;
        }

        return (int)(dp[n][0]%m);
    }
};
```

- Time complexity: O(N)
- Space complexity: O(N) 比較占空間的解法

### Solution 2

較不直覺，找到規律 dp[i] = dp[i-1] + dp[i-2] + 2*(dp[i-3] + dp[i-4] + … + dp[1])
並計算 prefix sum 加速

```cpp
class Solution {
public:
    int numTilings(int n) {
        int m = 1000000007;

        if (n == 1) {
            return 1;
        }

        if (n == 2) {
            return 2;
        }

        vector<long> dp(n+1, 0);
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;

        vector<long> prefix_sum(n+1, 0);
        prefix_sum[0] = 1;
        prefix_sum[1] = 2;
        prefix_sum[2] = 4;

        for (int i = 3; i <= n; ++i) {
            dp[i] = dp[i-1] % m + dp[i-2] % m + 2 * prefix_sum[i-3] % m;
            prefix_sum[i] = prefix_sum[i-1] % m + dp[i] % m;
        }

        return (int)(dp[n]%m);
    }
};
```

- Time complexity: O(N)
- Space complexity: O(N)

### Reference

- [LeetCode 解題紀錄 790. Domino and Tromino Tiling](https://kevinchung0921.medium.com/leetcode-%E8%A7%A3%E9%A1%8C%E7%B4%80%E9%8C%84-790-domino-and-tromino-tiling-7c36f7a3ac1b)
- [Domino and Tromino tiling problem](https://www.geeksforgeeks.org/domino-and-tromino-tiling-problem/)