# 1248. Count Number of Nice Subarrays

## Question

Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.

Return the number of nice sub-arrays.

Example 1:  
Input: nums = [1,1,2,1,1], k = 3  
Output: 2  
Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].  

Example 2:  
Input: nums = [2,4,6], k = 1  
Output: 0  
Explanation: There are no odd numbers in the array.  

Example 3:  
Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2  
Output: 16  

Constraints:
- 1 <= nums.length <= 50000
- 1 <= nums[i] <= 10^5
- 1 <= k <= nums.length

---
Date: 2024-06-22  
Start time: 14:40  

## Problem statement confirmation

- The array must not be empty.
- k must be smaller than the array size.
- All elements in the array are positive. No zeros.

Time checkpoint: 14:43 

## Solution idea

The solution may be something like prefix sum. Let’s say…prefix number of the odd numbers (?).  
We can use prefix sum to compute the sum of the elements in the arbitrary continuous subarrays.  
Similarly, we can utilize the “prefix number of the odd numbers” to derive the number of the odd numbers in the arbitrary continuous subarrays.  

The steps are as below:
1. Iterate through the array and calculate the number of the odd numbers from the first element to the current element
2. Use a hashmap to store the prefix number of the odd numbers and its frequency
3. If the prefix number of the odd numbers (pre_odd_num) is equal to k, then we find a nice subarray.
4. If the prefix number of the odd numbers (pre_odd_num) is no less than k, check the frequency of (pre_odd_num-k). The frequency represents the number of the nice subarrays we newly find.
5. Add up the number of the nice subarrays we find in Step 3 & 4. Then we obtain the answer!

Time checkpoint: 14:56 

## Complexity analysis

Assume that the length of the array nums is N.  
Time complexity: O(N), since we only iterate through the array once.  
Space complexity: O(N) (worst-case), since we use a hashmap to store the prefix number of the odd numbers and its frequency. In the worst case (all elements are odd), the hashmap size is equal to the length of the array.   

Time checkpoint: 14:59 

## Implementation

```python
class Solution:
    def numberOfSubarrays(self, nums: List[int], k: int) -> int:
        count = 0
        prefix_odd_num = 0
        dic = {}
        for n in nums:
            if n % 2 == 1:
                prefix_odd_num += 1
            
            if prefix_odd_num == k:
                count += 1
            if (prefix_odd_num >= k) and (dic.get(prefix_odd_num-k) is not None):
                count += dic[prefix_odd_num-k]
            
            if dic.get(prefix_odd_num) is not None:
                dic[prefix_odd_num] += 1
            else:
                dic[prefix_odd_num] = 1

        return count
```

Time checkpoint: 15:06 

## Testing (dry run)

Example 1: Input: nums = [1,1,2,1,1], k = 3  
prefix_odd_nums = [1, 2, 2, 3, 4]  
dic = {1: 1, 2: 2, 3: 1, 4: 1}  
count = 1+1 = 2  

Example 2: Input: nums = [2,4,6], k = 1  
prefix_odd_nums = [0, 0, 0]  
dic = {0: 3}  
count = 0  

Example 3: Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2  
prefix_odd_nums = [0, 0, 0, 1, 1, 1, 2, 2, 2, 2]  
dic = {0: 3, 1: 3, 2: 4}  
count = 4+4*3 = 16  

End time: 15:12 

## Results

Time spent: 32m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: Accepted  

## Review

None