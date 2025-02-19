# 875. Koko Eating Bananas

## Question

Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.  

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.

**Example 1:**  
- Input: piles = [3,6,7,11], h = 8
- Output: 4

**Example 2:**  
- Input: piles = [30,11,23,4,20], h = 5
- Output: 30

**Example 3:**  
- Input: piles = [30,11,23,4,20], h = 6
- Output: 23
 
**Constraints:**  
- 1 <= piles.length <= 10^4
- piles.length <= h <= 10^9
- 1 <= piles[i] <= 10^9

---
Date: 2025-02-19  
Start time: 12:56  

## Problem statement confirmation

- Is it possible that the number of the piles is larger than h? No, it must no larger than h.
- Should I handle the case that there's zero pile of bananas? No, there's at least a pile.
- k is a constant speed throughout the h hours that I sould output.
- Note that the number of the piles can be large (1e4), and h and the number of the bananas in a pile can be super large (1e9)!

Time checkpoint: 13:03  

## Solution idea

To solve this problem in the simplest way, I can subsequently try k = 1, 2, 3, ... until I find a k that fulfills the requirements.  

However, I realize that I am searching a value from a sorted series of numbers. Maybe I can utilize binary search to solve the problem in a more efficient way.  

But now I have a question: What is the upper bound of k?

When h is equal to the number of the piles, k should be the maximum of the number of the bananas in a pile so that in each hour Koko can eat a pile. Therefore, I should firstly find the maximum of the number of the bananas in a pile, which is the upper bound of k.

Then, I can start perform binary search! Note that the problem requests the minimum possible k, so I should not stop search when I find the first k in which Koko can eat out all the bananas. Instead I should keep searching in the smaller half until the left and right pointers cross. And the value in the left index is the answer.

Time checkpoint: 13:16  

## Complexity analysis

Assume that the number of the piles is N, the maximum number of the bananas in a pile is M
- Time complexity: O(N+NlogM) (?), O(N) is for finding the maximum, and O(NlogM) is for the binary search.
- Space complexity: O(1).

Time checkpoint: 13:22  

## Implementation

```cpp
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int max_num_bananas = 0;
        for (int num: piles) {
            if (num > max_num_bananas) {
                max_num_bananas = num;
            }
        }

        int left = 1;
        int right = max_num_bananas;
        while (left <= right) {
            int mid  = left + (right-left)/2;
            int required_h = 0;
            for (int num: piles) {
                required_h += ceil((double)num/mid);
            }

            if (required_h > h) {
                left = mid + 1;
            }
            else if (required_h <= h) {
                right = mid - 1;
            }
        }
        return left;
    }
};
```

Time checkpoint: 13:31  

## Testing (dry run)

Example 1: Input: piles = [3,6,7,11], h = 8, Output: 4
- max_num_bananas = 11, left = 1, right = 11
- mid = 6, required_h = 1+1+2+2 = 6 < 8, left = 1, right = 5
- mid = 3, required_h = 1+2+3+4 = 10 > 8, left = 4, right = 5
- mid = 4, required_h = 1+2+2+3 = 8 == 8, left = 4, right = 3
- Return 4

Example 2: Input: piles = [30,11,23,4,20], h = 5, Output: 30
- max_num_bananas = 30, left = 1, right = 30
- mid = 15, required_h = 2+1+2+1+2 = 8 > 5, left = 16, right = 30
- mid = 23, required_h = 2+1+1+1+1 = 6 > 5, left = 24, right = 30
- mid = 27, required_h = 2+1+1+1+1 = 6 > 5, left = 28, right = 30
- mid = 29, required_h = 2+1+1+1+1 = 6 > 5, left = 30, right = 30
- mid = 30, required_h = 1+1+1+1+1 = 5 == 5, left = 30, right = 29
- Return 30

Example 3: Input: piles = [30,11,23,4,20], h = 6, Output: 23
- max_num_bananas = 30, left = 1, right = 30
- mid = 15, required_h = 2+1+2+1+2 = 8 > 6, left = 16, right = 30
- mid = 23, required_h = 2+1+1+1+1 = 6 == 6, left = 16, right = 29
- mid = 22, required_h = 2+1+2+1+1 = 7 > 6, left = 23, right = 29
- mid = 26, required_h = 2+1+1+1+1 = 6 == 6, left = 23, right = 25
- mid = 24, required_h = 2+1+1+1+1 = 6 == 6, left = 23, right = 23
- mid = 23, required_h = 2+1+1+1+1 = 6 == 6, left = 23, right = 22
- Return 23

End time: 13:42  

## Results

Time spent: 46m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: Runtime Error (注意 required_h 可能會 integer overflow) 

## Review

Solution 大致正確，但 required_h 要改成 long：
```cpp
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int max_num_bananas = 0;
        for (int num: piles) {
            if (num > max_num_bananas) {
                max_num_bananas = num;
            }
        }

        int left = 1;
        int right = max_num_bananas;
        while (left <= right) {
            int mid  = left + (right-left)/2;
            long required_h = 0;
            for (int num: piles) {
                required_h += ceil((double)num/mid);
            }

            if (required_h > h) {
                left = mid + 1;
            }
            else if (required_h <= h) {
                right = mid - 1;
            }
        }
        return left;
    }
};
```

第一次解 binary search 變化題，感覺稍微不直覺