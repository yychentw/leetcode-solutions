# 1768. Merge Strings Alternately

## Question

You are given two strings word1 and word2. Merge the strings by adding letters in alternating order, starting with word1. If a string is longer than the other, append the additional letters onto the end of the merged string.  

Return the merged string.  

Example 1:  
Input: word1 = "abc", word2 = "pqr"  
Output: "apbqcr"  
Explanation: The merged string will be merged as so:  
word1:  a   b   c  
word2:    p   q   r  
merged: a p b q c r  

Example 2:  
Input: word1 = "ab", word2 = "pqrs"  
Output: "apbqrs"  
Explanation: Notice that as word2 is longer, "rs" is appended to the end.  
word1:  a   b   
word2:    p   q   r   s  
merged: a p b q   r   s  

Example 3:  
Input: word1 = "abcd", word2 = "pq"  
Output: "apbqcd"  
Explanation: Notice that as word1 is longer, "cd" is appended to the end.  
word1:  a   b   c   d  
word2:    p   q   
merged: a p b q c   d  

Constraints:  
- 1 <= word1.length, word2.length <= 100
- word1 and word2 consist of lowercase English letters.

---
Date: 2024-07-22  
Start time: 07:54  

## Problem statement confirmation

- The lengths of the two strings can be different. Append the remaining letters of the longer string to the end of the merged string.
- No empty string.

Time checkpoint: 07:56 

## Solution idea

- Create an empty string `ans`.
- Alternately add the characters of `word1` & `word2` to `ans` util the end of one of the string.
- If there are unvisited characters in `word1`, append them to `ans`.
- Similarly, if there are unvisited characters in `word2`, append them to `ans`.
- Return `ans`.

Time checkpoint: 08:00 

## Complexity analysis

Assume that the length of `word1` is N and the length of `word2` is M.
- Time complexity: O(N+M) because I iterate over the 2 strings.
- Space complexity: O(N+M) because the length of the merged string is the sum of the input string lengths.

Time checkpoint: 08:02 

## Implementation

```cpp
class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string ans;
        int i = 0;
        while (i < word1.size() && i < word2.size()) {
            ans += word1[i];
            ans += word2[i];
            ++i;
        }
        if (i < word1.size()) {
            ans += word1.substr(i, word1.size() - i);
        }
        else if (i < word2.size()) {
            ans += word2.substr(i, word2.size() - i);
        }
        return ans;
    }
};
```

Time checkpoint: 08:09 

## Testing (dry run)

Example 1: Input: word1 = "abc", word2 = "pqr"  
- i = 0, ans = "ap"
- i = 1, ans = "apbq"
- i = 2, ans = "apbqcr"
- i = 3, end, return "apbqcr"

Example 2: Input: word1 = "ab", word2 = "pqrs"  
- i = 0, ans = "ap"
- i = 1, ans = "apbq"
- i = 2 < word2.size(), return ans = "apbqrs"

Example 3: Input: word1 = "abcd", word2 = "pq"  
- i = 0, ans = "ap"
- i = 1, ans = "apbq"
- i = 2 < word1.size(), return ans = "apbqcd"

End time: 08:12 

## Results

Time spent: 18m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: Accepted  

## Review

複習 std::string 的 substr 用法：
```
string substr (size_t pos = 0, size_t len = npos) const;
```
第一個參數是初始位置，第二個參數是長度。  
記得 substr 用法，這裡解法就可以寫得簡潔一點～