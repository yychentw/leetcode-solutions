# 162. Find Peak Element

## Question

A peak element is an element that is strictly greater than its neighbors.  

Given a 0-indexed integer array nums, find a peak element, and return its index. If the array contains multiple peaks, return the index to any of the peaks.  

You may imagine that nums[-1] = nums[n] = -∞. In other words, an element is always considered to be strictly greater than a neighbor that is outside the array.  

You must write an algorithm that runs in O(log n) time.  

**Example 1:**  
- Input: nums = [1,2,3,1]
- Output: 2
- Explanation: 3 is a peak element and your function should return the index number 2.

**Example 2:**  
- Input: nums = [1,2,1,3,5,6,4]
- Output: 5
- Explanation: Your function can return either index number 1 where the peak element is 2, or index number 5 where the peak element is 6.

**Constraints:**  
- 1 <= nums.length <= 1000
- -2^31 <= nums[i] <= 2^31 - 1
- nums[i] != nums[i + 1] for all valid i.

---
Date: 2025-03-08  
Start time: 22:48  

## Problem statement confirmation

- nums[i] can be any integer.
- nums[1] and nums[n-1] are always greater than their boundary.
- The array is never empty. But its length can be 1, and in this case the only element is the peak element.
- nums[i] and its neighbors are unique.
- There is always a (or more) peak element existing.

Time checkpoint: 22:52  

## Solution idea

An O(log n) solution? Can it be binary search?  

When we find the middle point, we will check the following conditions:
- If nums[mid] is the peak element, return mid.
- If nums[mid-1] < nums[mid] < nums[mid+1], find the peak element in the right half part.
- If nums[mid-1] > nums[mid] > nums[mid+1], find the peak element in the left half part.
- If nums[mid-1] > nums[mid] < nums[mid+1], it's ok to find the peak element in either of the half parts.

Time checkpoint: 22:58  

## Complexity analysis

Assume that the length of the array is N:
- Time complexity: O(log N)
- Space complexity: O(1) because only extra constant space is needed.

Time checkpoint: 22:59  

## Implementation

```cpp
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right-left)/2;
            if (mid == 0 && nums[mid] > nums[mid+1]) {
                return mid;
            }
            else if (mid == 0 && nums[mid] < nums[mid+1]) {
                left = mid + 1;
            }
            else if (mid == nums.size() - 1 && nums[mid] > nums[mid-1]) {
                return mid;
            }
            else if (mid == nums.size() - 1 && nums[mid] < nums[mid-1]) {
                right = mid - 1;
            }
            else if (nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1]) {
                return mid;
            }
            else if (nums[mid] > nums[mid-1] && nums[mid] < nums[mid+1]) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return -1;
    }
};
```

Time checkpoint: 23:25  

## Testing (dry run)

Example 1: Input: nums = [1,2,3,1], Output: 2
- left = 0, right = 3
- mid = 1, nums[mid] > nums[mid-1] && nums[mid] < nums[mid+1], left = 2, right = 3
- mid = 2, nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1], return 2

Example 2: Input: nums = [1,2,1,3,5,6,4], Output: 1 or 5
- left = 0, right = 6
- mid = 3, nums[mid] = 3  > nums[mid-1] && nums[mid] < nums[mid+1], left = 4, right = 6
- mid = 5, nums[mid] = 6  > nums[mid-1] && nums[mid] > nums[mid+1], return 5

Edge case?

My test case 1: Input: nums = [1], Output: 0
- Return 0

My test case 2: Input: nums = [1,2], Output: 1
- left = 0, right = 1
- mid = 0, nums[mid] = 1 < nums[mid+1], left = 1, right = 1
- mid = 1, nums[mid] = 2 > nums[mid-1], return 1

My test case 3: Input: nums = [3,2,1], Output: 0
- left = 0, right = 2
- mid = 1, nums[mid] = 2 < nums[mid-1] && nums[mid] > nums[mid+1], left = 0, right = 0
- mid = 0, nums[mid] = 3 > nums[mid+1], return 0

End time: 23:25  

## Results

Time spent: 37m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: Accepted 

## Review

注意 vector 邊界的處理

可以簡化寫法如下：
```cpp
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if (n == 1) {
            return 0;
        }

        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right-left)/2;
            if (nums[mid] > nums[mid+1]) {
                right = mid;
            }
            =else {
                left = mid + 1;
            }
        }
        return left;
    }
};
```