# 1657. Determine if Two Strings Are Close

## Question

Two strings are considered close if you can attain one from the other using the following operations:
- Operation 1: Swap any two existing characters.
    - For example, abcde -> aecdb
- Operation 2: Transform every occurrence of one existing character into another existing character, and do the same with the other character.
    - For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)

You can use the operations on either string as many times as necessary.  

Given two strings, word1 and word2, return true if word1 and word2 are close, and false otherwise.  

Example 1:  
Input: word1 = "abc", word2 = "bca"  
Output: true  
Explanation: You can attain word2 from word1 in 2 operations.  
Apply Operation 1: "abc" -> "acb"  
Apply Operation 1: "acb" -> "bca"  

Example 2:  
Input: word1 = "a", word2 = "aa"  
Output: false  
Explanation: It is impossible to attain word2 from word1, or vice versa, in any number of operations.  

Example 3:  
Input: word1 = "cabbba", word2 = "abbccc"  
Output: true  
Explanation: You can attain word2 from word1 in 3 operations.  
Apply Operation 1: "cabbba" -> "caabbb"  
Apply Operation 2: "caabbb" -> "baaccc"  
Apply Operation 2: "baaccc" -> "abbccc"  

Constraints:  
- 1 <= word1.length, word2.length <= 10^5
- word1 and word2 contain only lowercase English letters.

---
Date: 2024-07-16  
Start time: 22:04  

## Problem statement confirmation

- The lengths of word1 and word2 can be different.
- The length of the word cannot be 0.

Time checkpoint: 22:07 

## Solution idea

Two strings are close if:  
- Operation 1: Two strings have the same unique characters and frequencies.
- Operation 2: Two strings have the same unique characters, and the sum of the frequencies are the same

Steps:  
- Return false if the lengths of word1 and word2 are different.
- Use a hash table to store the unique characters and their frequencies of word1
- Check if word2 are close to word1:
    - If the character in word2 is not in the hash table, return false.
    - If the character is in the hash table, the frequency -= 1.
    - After going through all the characters of word2, calculate the sum of the frequencies.
        - if the sum == 0, return true.
        - if the sum != 0, return false.

Time checkpoint: 22:19 

## Complexity analysis

Assume that the length of word1 is N, the length of word2 is M.

- Time complexity: O(2N+M)(?)
    - Build a hash table for word1: O(N)
    - Go through word2: O(M)
    - Calculate the frequency sum: O(N)
- Space complexity: O(N) since I use a hash table to store the characters and their frequency of word1.

Time checkpoint: 22:23 

## Implementation

```python
class Solution:
    def closeStrings(self, word1: str, word2: str) -> bool:
        if len(word1) != len(word2):
            return False

        dic = {}
        for c1 in word1:
            if dic.get(c1) is not None:
                dic[c1] += 1
            else:
                dic[c1] = 1

        for c2 in word2:
            if dic.get(c2) is not None:
                dic[c2] -= 1
            else:
                return False

        sum_ = 0
        for freq in dic.values():
            sum_ += freq
        if sum_ != 0:
            return False

        return True
```

Time checkpoint: 22:28 

## Testing (dry run)

Example 1: Input: word1 = "abc", word2 = "bca"  
- len(word1) == len(word2)
- dic = {"a": 1, "b": 1, "c": 1}
- After going through word2, dic = {"a": 0, "b": 0, "c": 0}
- sum_ = 0, return True

Example 2: Input: word1 = "a", word2 = "aa"  
- len(word1) == len(word2), return False

Example 3: Input: word1 = "cabbba", word2 = "abbccc"  
- len(word1) == len(word2)
- dic = {"a": 2, "b": 3, "c": 1}
- After going through word2, dic = {"a": 1, "b": 1, "c": -2}
- sum_ = 0, return True

End time: 22:32 

## Results

Time spent: 28m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: WA (QQ)  

## Review

Test case: word1 = "abbbzcf", word2 = "babzzcz"
- len(word1) == len(word2)
- dic = {"a": 1, "b": 3, "c": 1, "f": 1, "z": 1}
- After going through word2, dic = {"a": 0, "b": 1, "c": 0, "f": 1, "z": -2}
- sum_ = 0, return True

But the answer should be False because word2 does not have "f".
I need to check if all the keys are "touched".
Or I need to build another hash table for word2 and check if the two hash tables have the same keys and have the same "distribution of frequencies" (not sum!).

The modified solution is as below:  
```python
class Solution:
    def closeStrings(self, word1: str, word2: str) -> bool:
        if len(word1) != len(word2):
            return False

        dic1 = {}
        for c1 in word1:
            if dic1.get(c1) is not None:
                dic1[c1] += 1
            else:
                dic1[c1] = 1

        dic2 = {}
        for c2 in word2:
            if dic2.get(c2) is not None:
                dic2[c2] += 1
            else:
                dic2[c2] = 1

        if len(dic1.keys()) != len(dic2.keys()):
            return False

        for k1 in dic1.keys():
            if dic2.get(k1) is None:
                return False

        vals1 = sorted(dic1.values())
        vals2 = sorted(dic2.values())
        for v1, v2 in zip(vals1, vals2):
            if v1 != v2:
                return False

        return True
```

Time complexity: O(M+N+26\*2+26log(26)\*2)  
Space complexity: O(26\*4)  

解題方向正確但應該能再優化時間空間複雜度...