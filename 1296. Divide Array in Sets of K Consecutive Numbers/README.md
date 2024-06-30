# 1296. Divide Array in Sets of K Consecutive Numbers

## Question

Given an array of integers nums and a positive integer k, check whether it is possible to divide this array into sets of k consecutive numbers.  

Return true if it is possible. Otherwise, return false.  

Example 1:  
Input: nums = [1,2,3,3,4,4,5,6], k = 4  
Output: true  
Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].  

Example 2:  
Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3  
Output: true  
Explanation: Array can be divided into [1,2,3] , [2,3,4] , [3,4,5] and [9,10,11].  

Example 3:  
Input: nums = [1,2,3,4], k = 3  
Output: false  
Explanation: Each array should be divided in subarrays of size 3.  

Constraints:  
- 1 <= k <= nums.length <= 10^5
- 1 <= nums[i] <= 10^9

---
Date: 2024-06-16  
Start time: 21:11  

## Problem statement confirmation

- The array cannot be empty.
- There’s no guarantee that the length of the array should be divisible by k.
- Note that k can be 1.

Time checkpoint: 21:16 

## Solution idea

1. First of all I would check if the length of the array is divisible by k. If not, directly return false to improve the best-case time complexity.
2. Sort the array
3. Consider the sorted array as a stack, pop out the last k elements each time. 
4. If some of the popped-out elements is equal to the previous one, temporarily save them to another array, and pop out more elements until there are k unique popped-out elements.
5. Check if the popped-out elements are consecutive. Return false if they aren’t.
6. If the popped-out elements are consecutive, push back the temporarily saved duplicated elements to the stack, and repeat step 3 to 6 until the stack is empty.
7. Finally if all sets of popped-out elements are consecutive, return true.

Time checkpoint: ? 

## Complexity analysis

Best-case time complexity: O(1) (because we only need to obtain the length of the array)  

Since we sort the array, assume that the length of the array is N, the time complexity of the sorting is O(N logN).  
Then we pop out and check all the elements in the stack, the time complexity of this part is O(N).  
Therefore in general the time complexity is O(N logN), and the worst-case space complexity is O(N) if we need to temporarily save a number of duplicated elements.  

Time checkpoint: 21:38 

## Implementation

```python
class Solution:
    def isPossibleDivide(self, nums: List[int], k: int) -> bool:
        if k == 1:
            return True
        
        if len(nums) % k != 0:
            return False

        nums.sort()

        last_element = nums.pop()
        cur_subarr_size = 1
        temp = []
        while len(nums) > 0:
            if cur_subarr_size == k:
                while len(temp) > 0:
                    nums.append(temp.pop())
                last_element = nums.pop()
                cur_subarr_size = 1
                continue
            
            popped_element = nums.pop()
            if popped_element == last_element:
                temp.append(popped_element)
                continue
            if popped_element == last_element - 1:
                last_element = popped_element
                cur_subarr_size += 1
            else:
                return False
        
        return True
```

Time checkpoint: 21:59 

## Testing (dry run)

Example 1: nums = [1,2,3,3,4,4,5,6], k = 4  
k != 1  
len(nums) % 4 = 8 % 4 == 0  
sorted nums = [1,2,3,3,4,4,5,6]  
last_element = 6, cur_subarr_size = 1, temp = []  
- popped_element = 5 == last_element - 1, so last_element = 5, cur_subarr_size = 2, temp = []
- popped_element = 4 == last_element - 1, so last_element = 4, cur_subarr_size = 3, temp = []
- popped_element = 4 == last_element, so last_element = 4, cur_subarr_size = 3, temp = [4]
- popped_element = 3 == last_element - 1, so last_element = 3, cur_subarr_size = 4, temp = [4]
- since cur_subarray_size == k, sorted nums = [1,2,3], last_element = 4, cur_subarr_size = 1, temp = []
- popped_element = 3 == last_element - 1, so last_element = 3, cur_subarr_size = 2, temp = []
- popped_element = 2 == last_element - 1, so last_element = 2, cur_subarr_size = 3, temp = []
- popped_element = 1 == last_element - 1, so last_element = 1, cur_subarr_size = 4, temp = []  

return true  

Example 2: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3  
k != 1  
len(nums) % 3 = 12 % 3 == 0  
sorted nums = [1,2,2,3,3,3,4,4,5,9,10,11]  
last_element = 11, cur_subarr_size = 1, temp = []  
- popped_element = 10 == last_element - 1, so last_element = 10, cur_subarr_size = 2, temp = []
- popped_element = 9 == last_element - 1, so last_element = 9, cur_subarr_size = 3, temp = []
- since cur_subarr_size == k, sorted nums = [1,2,2,3,3,3,4,4], last_element = 5, cur_subarray_size = 1, temp = []
- popped_element = 4 == last_element - 1, so last_element = 4, cur_subarr_size = 2, temp = []
- popped_element = 4 == last_element, so last_element = 4, cur_subarr_size = 2, temp = [4]
- popped_element = 3 == last_element - 1, so last_element = 3, cur_subarr_size rray_size = 3, temp = [4]
- since cur_subarr_size == k, sorted nums = [1,2,2,3,3], last_element = 4, cur_subarray_size = 1, temp = []
- popped_element = 3 == last_element - 1, so last_element = 3, cur_subarr_size = 2, temp = []
- popped_element = 3 == last_element, so last_element = 3, cur_subarr_size = 2, temp = [3]
- popped_element = 2 == last_element - 1, so last_element = 2, cur_subarr_size = 3, temp = [3]
- since cur_subarr_size == k, sorted nums = [1,2], last_element = 3, cur_subarr_size = 1, temp = []
- popped_element = 2 == last_element - 1, so last_element = 2, cur_subarr_size = 2, temp = []
- popped_element = 1 == last_element - 1, so last_element = 1, cur_subarr_size = 3, temp = []

return true

Example 3: nums = [1,2,3,4], k = 3  
k != 1  
len(nums) % 3 = 4 % 3 != 0, return false  

End time: 22:14 

## Results

Time spent: 1h3m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: WA (QQ), and after fixing the bug, still TLE (QQ) 

## Review

The reason of WA?  
- Some typos
- WA for this test case: nums = [1,1,2,2,3,3], k = 2, expected answer = False
    k != 1  
    len(nums) % 2 = 6 % 2 == 0  
    sorted nums = [1,1,2,2,3,3]  
    last_element = 3, cur_subarray_size = 1, temp = []   
    - popped_element = 3 == last_element, so last_element = 3, cur_subarr_size = 1, temp = [3]  
    - popped_element = 2 == last_element - 1, so last_element = 2, cur_subarr_size = 2, temp = [3]
    - since cur_subarr_size == 2, so sorted nums = [1,1,2], last_element = 3, cur_subarray_size = 1, temp = []
    - popped_element = 2 == last_element - 1, so last_element = 2, cur_subarr_size = 2, temp = []
    - since cur_subarr_size == 2, so sorted nums = [1], last_element = 1, cur_subarray_size = 1, temp = []
    - popped_element = 1 == last_element, so last_element = 1, cur_subarr_size = 1, temp = [1]
    - Here, I forgot to add a condition: 
    - If the while loop is completed, check if the temp list is empty. If not empty, return False.

Modified implementation  
```python
class Solution:
    def isPossibleDivide(self, nums: List[int], k: int) -> bool:
        if k == 1:
            return True
        
        if len(nums) % k != 0:
            return False

        nums.sort()

        last_element = nums.pop()
        cur_subarr_size = 1
        temp = []
        while len(nums) > 0:
            if cur_subarr_size == k:
                while len(temp) > 0:
                    nums.append(temp.pop())
                last_element = nums.pop()
                cur_subarr_size = 1
                continue
            
            popped_element = nums.pop()
            if popped_element == last_element:
                temp.append(popped_element)
                continue
            if popped_element == last_element - 1:
                last_element = popped_element
                cur_subarr_size += 1
            else:
                return False
        
        if len(temp) != 0: 
            return False
        
        return True
```

參考別人的作法，可以使用 sorting + hash map  

Solution idea  
1. Sort the array  
2. Build a hash map to store each value’s frequency in the array
3. Iterate through the sorted array again, find the starter of the subarray (the one with non-zero frequency), check if there exists a consecutive subarray of size k, and subtract the frequency accordingly
4. If a consecutive subarray of size k does not exist, return false.
5. Finally return true if the array can be divided to a set of consecutive subarray with size k.
6. The time complexity of this solution is close to the original solution (?), but this solution can handle duplicate elements in the array in a simpler way.

Implementation  
```python
class Solution:
    def isPossibleDivide(self, nums: List[int], k: int) -> bool:
        if k == 1:
            return True
        
        if len(nums) % k != 0:
            return False

        nums.sort()

        dic = {}
        for num in nums:
            if dic.get(num) is None:
                dic[num] = 1
            else:
                dic[num] += 1

        for num in nums:
            if dic[num] > 0:
                for i in range(num, num+k):
                    if dic.get(i) is None or dic[i] == 0:
                        return False
                    else:
                        dic[i] -= 1

        return True
```
