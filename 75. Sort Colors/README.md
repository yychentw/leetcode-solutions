# 75. Sort Colors

## Question

Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.

You must solve this problem without using the library's sort function.

Example 1:  
Input: nums = [2,0,2,1,1,0]  
Output: [0,0,1,1,2,2]  

Example 2:  
Input: nums = [2,0,1]  
Output: [0,1,2]  

Constraints:  
n == nums.length  
1 <= n <= 300  
nums[i] is either 0, 1, or 2.  
 
Follow up: Could you come up with a one-pass algorithm using only constant extra space?

---
Date:  2024-06-29
Start time:  17:22

## Problem statement confirmation

- Note that there are only three types of elements in the array
- Note that only constant space can be used to sort the array (in-place sorting)

Time checkpoint: 17:25

## Solution idea

The key is, there are only three types of array elements: 
- 0 is the smallest and should be in the front of the array
- 2 is the largest and should be in the end of the array
- 1 is between 0 and 2

Therefore, we only need to go through each element in the array once, and
- if the element is 0, insert it to the front of the array, remove the element in the original position+1
- if the element is 1, keep it unchanged
- if the element is 2, append it to the end of the array, remove the element in the original position, keep the query index unchanged in the next iteration, and remember that the last index to visit -1

Time checkpoint: 17:36

## Complexity analysis

Assume that the length of the array is N,  
Time complexity: O(N) because we only go through each element in the array once  
Space complexity: O(1) because the solution should be in-place sorting  

Time checkpoint: 17:38

## Implementation

```python
class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        i = 0
        end_pos = len(nums)
        while i < end_pos:
            if nums[i] == 0:
                nums.insert(0, nums[i])
                nums.pop(i+1)
            elif nums[i] == 2:
                nums.append(nums[i])
                nums.pop(i)
                end_pos -= 1
                i -= 1
            i += 1
```

Time checkpoint: 17:45

## Testing (dry run)

Example 1: Input: nums = [2,0,2,1,1,0], Output: [0,0,1,1,2,2]  
- i = 0, nums = [0,2,1,1,0,2], end_pos = 5
- i = 0, nums = [0,2,1,1,0,2], end_pos = 5
- i = 1, nums = [0,1,1,0,2,2], end_pos = 4
- i = 1, nums = [0,1,1,0,2,2], end_pos = 4
- i = 2, nums = [0,1,1,0,2,2], end_pos = 4
- i = 3, nums = [0,0,1,1,2,2], end_pos = 4
- i = 4, end

Example 2: Input: nums = [2,0,1], Output: [0,1,2]
- i = 0, nums = [0,1,2], end_pos = 2
- i = 0, nums = [0,1,2], end_pos = 2
- i = 1, nums = [0,1,2], end_pos = 2
- i = 2, end

End time: 17:53

## Results

Time spent: 31m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: Accepted  

## Review

None