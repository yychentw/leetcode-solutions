# 974. Subarray Sums Divisible by K

## Question

Given an integer array nums and an integer k, return the number of non-empty subarrays that have a sum divisible by k.  

A subarray is a contiguous part of an array.  

Example 1:  
Input: nums = [4,5,0,-2,-3,1], k = 5  
Output: 7  
Explanation: There are 7 subarrays with a sum divisible by k = 5:  
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]

Example 2:  
Input: nums = [5], k = 9  
Output: 0  

Constraints:
- 1 <= nums.length <= 3 * 10^4
- -10^4 <= nums[i] <= 10^4
- 2 <= k <= 10^4

---
Date: 2024-06-09  
Start time: 12:12  

## Problem statement confirmation

- Is it possible that the array is empty? No.
- Is it possible that none of the subarrays have a sum divisible by k? Yes.
- k must be a positive integer.
- 0 is divisible by any positive integer k.
- Negative numbers are also divisible.

Time checkpoint: 12:19 

## Solution idea

Brute force
- Find all subarrays of nums
- Compute all sums of the subarrays
- Check if the sums are divisible by k
- Return the number of the subarrays that have a sum divisible by k

Some optimization thoughts (still incomplete)
- There are some repeated calculations of sums in the brute-force solution. For example, we don’t need to re-calculate the sum of all elements of a subarray if we already calculate the sums of “the subarrays of the subarray”. 
- Something like cumulative sum may help solve the question.

But for now, I would like to start with the brute-force solution.  

Time checkpoint: 12:33 

## Complexity analysis

Assume that the length of the array is N.

For the brute-force solution, we need to calculate the sums of 
N+(N-1)+...+1 = N(N-1)/2 subarrays

And to calculate each sum, the worst-case complexity is O(N).

Therefore, the overall worst-case complexity is O(N^3).

Time checkpoint: 12:41 

## Implementation

```python
class Solution:
    def subarraysDivByK(self, nums: List[int], k: int) -> int:
        ans = 0
        for i in range(len(nums)):
            for j in range(i, len(nums)):
                subarr = nums[i:(j+1)]
                subarr_sum = sum(subarr)
                if abs(subarr_sum) % k == 0:    # not sure the behavior of negative_int % positive_int
                    ans += 1
        return ans
```

Suddenly come up with a solution utilizing cumulative sum: 
```python
class Solution:
    def subarraysDivByK(self, nums: List[int], k: int) -> int:
        ans = 0
        for i in range(len(nums)):
            cul_sum = nums[i]
            for j in range(i, len(nums)):
                if j != i:
                    cul_sum += nums[j]
                if abs(cul_sum) % k == 0:
                    ans += 1
        return ans
```
For the cumulative sum solution, we utilize the computed sum of the previous elements with the afterward element, and get the new sum.  
The worst-case complexity of sum calculation O(N) is only applied N times.  
Therefore the overall worst-case complexity is O(N^2).  

Time checkpoint: 13:04 

## Testing (dry run)

Let’s firstly test the solution with the given 2 examples.

Example 1:  
nums = [4,5,0,-2,-3,1], k = 5  
ans = 0  
- i = 0: cul_sum = nums[i] = 4
    - j = 0: cul_sum = 4, not divisive by 5, ans = 0
    - j = 1: cul_sum = 4+5 = 9, not divisive by 5, ans = 0
    - j = 2: cul_sum = 9+0 = 9, not divisive by 5, ans = 0
    - j = 3: cul_sum = 9-2 = 7, not divisive by 5, ans = 0
    - j = 4: cul_sum = 7-3 = 4, not divisive by 5, ans = 0
    - j = 5: cul_sum = 4+1 = 5, divisive by 5, ans = 1
- i = 1: cul_sum = nums[i] = 5
    - j = 1: cul_sum = 5, divisive by 5, ans = 2
    - j = 2: cul_sum = 5+0 = 5, divisive by 5, ans = 3
    - j = 3: cul_sum = 5-2 = 3, not divisive by 5, ans = 3
    - j = 4: cul_sum = 3-3 = 0, divisive by 5, ans = 4
    - j = 5: cul_sum = 0+1 = 1, not divisive by 5, ans = 4
- i = 2: cul_sum = nums[i] = 0
    - j = 2: cul_sum = 0, divisive by 5, ans = 5
    - j = 3: cul_sum = 0-2 = -2, not divisive by 5, ans = 5
    - j = 4: cul_sum = -2-3 = -5, divisive by 5, ans = 6
    - j = 5: cul_sum = -5+1 = -4, not divisive by 5, ans = 6
- i = 3: cul_sum = nums[i] = -2
    - j = 3: cul_sum = -2, not divisive by 5, ans = 6
    - j = 4: cul_sum = -2-3 = -5, divisive by 5, ans = 7
    - j = 5: cul_sum = -5+1 = -4, not divisive by 5, ans = 7
- i = 4: cul_sum = nums[i] = -3
    - j = 4: cul_sum = -3, not divisive by 5, ans = 7
    - j = 5: cul_sum = -3+1 = -2, not divisive by 5, ans = 7
- i = 5: cul_sum = nums[i] = 1
    - j = 5: cul_sum = 1, not divisive by 5, ans = 7

Therefore, the answer is 7 (correct).

Example 2:  
nums = [5], k = 9  
- i = 0: cul_sum = nums[i] = 5
    - j = 0: cul_sum = 5, not divisive by 9, ans = 0

Therefore, the answer is 0 (correct).  

Any edge cases? No thoughts for now.  

End time: 13:18 

## Results

Time spent: 1h6m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: TLE (need to find another optimized solution QQ)  

## Review

本題為陣列任意區間和的變形，適用 prefix sums 的概念  

Prefix sums 具體做法是對陣列進行預處理，計算出從第一個元素到當前位置的所有元素的和，而要查詢任意區間的和（例如第 i 到第 j 元素的區間和），只要計算 prefix_sums[j+1] - prefix_sums[i] 即可  

而現在要解決的是任意區間 modulus 的問題  

nums = [4, 5, 0, -2], k = 5  
prefix_sums = [0, 4, 9, 9, 7]  
prefix_mods = [0, 4, 4, 4, 2]  
[1, 2] 區間 mod = prefix_mods[3] - prefix_mods[1] = 0
任意 [i, j] 區間 mod = prefix_mods[j+1] - prefix_mods[i]
當 prefix_mods[j+1] == prefix_mods[i] 時，代表扣除掉共同前綴，這個區間的 modulus == 0  
因此可以解決方向可以從是否有重複的 prefix_mods 來思考  

假設 prefix_mod == 0，代表從第一個元素到當前位置的所有元素和可被 k 整除，這是第一個需要計入的部分  
假設 prefix_mod == 0 的情況出現不只一次，除了要計入從第一個元素到當前位置的區間，也要計入其與先前所有數值為 0 的   prefix_mod 的區間，例如在計算到這個 prefix_mod 前已有 2 個 prefix_mod 的值等於 0，代表可以組成兩個區間其元素和的 modulus 為零  
其餘若特定非零的 predix_mod 數值只出現一次，代表以當前位置為起點或終點並沒辦法組成一個元素和可被 k 整除的區間  
而若特定非零的 prefix_mod 數值出現超過一次，第二次出現之後就可與先前同數值的 prefix_mod 組成元素和可被 k 整除的區間  

可以用 hash_map 來記錄 prefix_mod 的出現次數  

因此重新嘗試表達解法：  
1. Calculate the prefix modulus for all elements in the array
2. Store the prefix modulus and its frequency in a heap map
3. If the prefix modulus is equal to 0, the count is increased by (previous_freq+1)
4. If the prefix modulus is not equal to 0, the count is increased by previous_freq (no need to update the count if the prefix_mod has not been stored in the hash map)

Time complexity: O(N)  
Space complexity: O(k)  

Implementation:  
```python
class Solution:
    def subarraysDivByK(self, nums: List[int], k: int) -> int:
        ans = 0
        prefix_sum = 0
        map = {}
        for n in nums:
            prefix_sum += n
            prefix_mod = prefix_sum % k
            if prefix_mod == 0:
                ans += 1
            if map.get(prefix_mod) is not None:
                ans += map[prefix_mod]
                map[prefix_mod] += 1
            else:
                map[prefix_mod] = 1
        return ans
```
We can further optimize the solution:  
```python
class Solution:
    def subarraysDivByK(self, nums: List[int], k: int) -> int:
        ans = 0
        prefix_sum = 0
        map = {0: 1}    # need to further add 1 to the count if prefix_mod == 0
        for n in nums: 
            prefix_sum += n
            prefix_mod = prefix_sum % k
            if map.get(prefix_mod) is not None:
                ans += map[prefix_mod]
                map[prefix_mod] += 1
            else:
                map[prefix_mod] = 1
        return ans
```

是個沒看過就想不到的解法@@  

參考資料：[Prefix Sums（前綴和）概念](https://claire-chang.com/2023/05/04/prefix-sums%EF%BC%88%E5%89%8D%E7%B6%B4%E5%92%8C%EF%BC%89%E6%A6%82%E5%BF%B5/)