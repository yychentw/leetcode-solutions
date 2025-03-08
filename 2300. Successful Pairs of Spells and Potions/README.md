# 2300. Successful Pairs of Spells and Potions

## Question

You are given two positive integer arrays spells and potions, of length n and m respectively, where spells[i] represents the strength of the ith spell and potions[j] represents the strength of the jth potion.  

You are also given an integer success. A spell and potion pair is considered successful if the product of their strengths is at least success.  

Return an integer array pairs of length n where pairs[i] is the number of potions that will form a successful pair with the ith spell.  

**Example 1:**  
- Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7
- Output: [4,0,3]
- Explanation:
    - 0th spell: 5 * [1,2,3,4,5] = [5,10,15,20,25]. 4 pairs are successful.
    - 1st spell: 1 * [1,2,3,4,5] = [1,2,3,4,5]. 0 pairs are successful.
    - 2nd spell: 3 * [1,2,3,4,5] = [3,6,9,12,15]. 3 pairs are successful.
    - Thus, [4,0,3] is returned.

**Example 2:**  
- Input: spells = [3,1,2], potions = [8,5,8], success = 16
- Output: [2,0,2]
- Explanation:
    - 0th spell: 3 * [8,5,8] = [24,15,24]. 2 pairs are successful.
    - 1st spell: 1 * [8,5,8] = [8,5,8]. 0 pairs are successful. 
    - 2nd spell: 2 * [8,5,8] = [16,10,16]. 2 pairs are successful. 
    - Thus, [2,0,2] is returned.

**Constraints:**  
- n == spells.length
- m == potions.length
- 1 <= n, m <= 10^5
- 1 <= spells[i], potions[i] <= 10^5
- 1 <= success <= 10^10

---
Date: 2025-03-08  
Start time: 17:12  

## Problem statement confirmation

- Considering the range of spells and potions, integer overflow is possible.
- The strength of spells and potions should be positive. (But this seems nothing to do with the solution...)
- It is possible that there's no successful pair for spells[i].
- What is the maximum possible successful pairs? m!
- Both the arrays of spells and potions should not be empty.

Time checkpoint: 17:18  

## Solution idea

### Brute force solution

Calculate all products of spells and potions, and count the successful pairs.  

In this solution, the time complexity is O(NM), and the space complexity may be O(1) because we don't need extra space except for the answer array.  

However, given that n & m may be large (10^5), the time complexity may not be acceptable.  

### Binary search

In the problem clarification stage, I have found that there's upper bound for the number of the successful pairs, i.e., m. This means that we are searching for some values between 0 and m, so we may use binary search to solve this problem.  

...I am getting stuck.

### Other solutions?

Actually we don't need to calculates all the products of spells and potions. We need to find the potions that no less than success/spells[i]. This may slightly optimize the solution, but the time complexity is still O(NM).  

How about sorting the potions and then using binary search? The time complexity would be O(MlogM+NlogM). This solution is better.  

Another idea is that we can use a vector with size 10^5 to store the culmulative freqency (from current value to 10^5) of the potions, and we can calculate the minimum possible strength of the potions to query the answer. In this way, the time complexity is O(M+10^5+N) and the space complexity is O(10^5) even when n & m is small. Not quite practical.  

How about using a hash map to store the strength of the potions and their frequency? To achieve this, I have to go through the potions first. Then, for every spells[i], I have to go through the hash map to find the sum of the frequency of the potions no less than success/spells[i]. However, in the worst case, the time complexity is O(M+NM).  

Now I decide to adopt **the sorting + binary search solution**, and I will search for the leftmost potion that is no less than success/spells[i].  

Time checkpoint: 17:48  

## Complexity analysis

Assume that the length of spells is N and the length of potions is M:
- Time complexity: O((N+M)logM)
- Space complexity: O(1)

Time checkpoint: 17:49  

## Implementation

```cpp
class Solution {
public:
    vector<int> uccessfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        vector<int> answer(spells.size(), 0);
        sort(potions.begin(), potions.end());
        for (int i = 0; i < spells.size(); i++) {
            int left = 0;
            int right = potions.size() - 1;
            long long target = (success+spells[i]-1)/spells[i];
            while (left <= right) {
                int mid = left + (right-left)/2;
                if (potions[mid] < target) {
                    left = mid + 1;
                }
                else if (potions[mid] >= target) {
                    right = mid - 1;
                }
            }
            answer[i] = potions.size() - left;
        }
        return answer;
    }
};
```

Time checkpoint: 18:04  

## Testing (dry run)

Example 1: Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7; Output: [4,0,3]
- answer = [0,0,0], potions = [1,2,3,4,5] (after sorting)
- i = 0, spells[i] = 5, target = 2, left = 0, right = 4
    - mid = 2, potions[mid] = 3 > target, left = 0, right = 1
    - mid = 0, potions[mid] = 1 < target, left = 1, right = 1
    - mid = 1, potions[mid] = 2 == target, left = 1, right = 0, end, answer[i] = potions.size()-left = 4
- i = 1, spells[i] = 1, target = 7, left = 0, right = 4
    - mid = 2, potions[mid] = 3 < target, left = 3, right = 4
    - mid = 3, potions[mid] = 4 < target, left = 4, right = 4
    - mid = 4, potions[mid] = 5 < target, left = 5, right = 4, end, answer[i] = potions.size()-left = 0
- i = 2, spells[i] = 3, target = 3, left = 0, right = 4
    - mid = 2, potions[mid] = 3 = target, left = 0, right = 1
    - mid = 0, potions[mid] = 1 < target, left = 1, right = 1
    - mid = 1, potions[mid] = 2 < target, left = 2, right = 1, end, answer[i] = potions.size()-left = 3

Example 2: Input: spells = [3,1,2], potions = [8,5,8], success = 16; Output: [2,0,2]
- answer = [0,0,0], potions = [5,8,8] (after sorting)
- i = 0, spells[i] = 3, target = 6, left = 0, right = 2
    - mid = 1, potions[mid] = 8 > target, left = 0, right = 0
    - mid = 0, potions[mid] = 5 < target, left = 1, right = 0, end, answer[i] = potions.size()-left = 2
- i = 1, spells[i] = 1, target = 16, left = 0, right = 2
    - mid = 1, potions[mid] = 8 < target, left = 2, right = 2
    - mid = 2, potions[mid] = 8 < target, left = 3, right = 2, end, answer[i] = potions.size()-left = 0
- i = 2, spells[i] = 2, target = 8, left = 0, right = 2
    - mid = 1, potions[mid] = 8 = target, left = 0, right = 0
    - mid = 0, potions[mid] = 5 < target, left = 1, right = 0, end, answer[i] = potions.size()-left = 2

End time: 18:18  

## Results

Time spent: 1h6m (中間想太久了...)  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: Accepted   

## Review

中庸的執行時間，還可以接受的 solution，但就是中間收斂想法的過程太久。另外有認真 dry run 提前發現了一些 bugs，dry run 很重要，不過希望一開始寫 code 時腦袋就更清楚。 

此外，需要熟悉 sort 語法與 C++ 變數範圍。