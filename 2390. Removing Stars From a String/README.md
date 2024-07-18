# 2390. Removing Stars From a String

## Question

You are given a string s, which contains stars *.

In one operation, you can:
- Choose a star in s.
- Remove the closest non-star character to its left, as well as remove the star itself.
- Return the string after all stars have been removed.

Note:
- The input will be generated such that the operation is always possible.
- It can be shown that the resulting string will always be unique.
 

Example 1:  
Input: s = "leet\*\*cod\*e"  
Output: "lecoe"  
Explanation: Performing the removals from left to right:  
- The closest character to the 1st star is 't' in "leet\*\*cod\*e". s becomes "lee\*cod\*e".
- The closest character to the 2nd star is 'e' in "lee\*cod\*e". s becomes "lecod\*e".
- The closest character to the 3rd star is 'd' in "lecod\*e". s becomes "lecoe".
There are no more stars, so we return "lecoe".  

Example 2:  
Input: s = "erase\*\*\*\*\*"  
Output: ""  
Explanation: The entire string is removed, so we return an empty string.  

Constraints:  
- 1 <= s.length <= 10^5
- s consists of lowercase English letters and stars *.
- The operation above can be performed on s.

---
Date: 2024-07-18  
Start time: 22:32  

## Problem statement confirmation

- It is guarenteed that the operation can always be performed on s. This means that there are always more English letters at the left sides of the stars. 

Time checkpoint: 22:39 

## Solution idea

- Create an empty string
- Iterate over the input string. "Append" the character to the new string. As encountering a star, remove the last character of the new string and do not append the star.
- Return the new string.

Time checkpoint: 22:42 

## Complexity analysis

Assume that the length of the string is N.
- Time complexity: O(N) since I only iterate over the string once.
- Space complexity: O(N) since I use another string to stored the non-star characters. In the worst case (there's no star in the string), the extra space I use is equal to the size of the input string.

Time checkpoint: 22:45 

## Implementation

```python
class Solution:
    def removeStars(self, s: str) -> str:
        ans = ""
        for si in s:
            if si == "*":
                ans = ans[:-1]
                continue
            ans += si
        return ans
```

Time checkpoint: 22:47 

## Testing (dry run)

Example 1: Input: s = "leet\*\*cod\*e"  
- si = "l", ans = "l"
- si = "e", ans = "le"
- si = "e", ans = "lee"
- si = "t", ans = "leet"
- si = "*", ans = "lee"
- si = "*", ans = "le"
- si = "c", ans = "lec"
- si = "o", ans = "leco"
- si = "d", ans = "lecod"
- si = "*", ans = "leco"
- si = "e", ans = "lecoe"

Example 2: Input: s = "erase\*\*\*\*\*"  
- si = "e", ans = "e"
- si = "r", ans = "er"
- si = "a", ans = "era"
- si = "s", ans = "eras"
- si = "e", ans = "erase"
- si = "*", ans = "eras"
- si = "*", ans = "era"
- si = "*", ans = "er"
- si = "*", ans = "e"
- si = "*", ans = ""

End time: 22:51 

## Results

Time spent: 19m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode:  

## Review

注意 Python 的 list/string slicing 本身是 O(N) 的 copy operations，因此解法實際上的 time complexity 不只 O(N)...  

用 list pop 和 append 在實際運算時間上較快：
```python
class Solution:
    def removeStars(self, s: str) -> str:
        ans=[]
        for i in s:
            if i=='*':
                ans.pop()
            else:
                ans+=[i]
        return "".join(ans)
```

C++ 的部分則要記得 string 可以 push_back 和 pop_back，本身就可以當字符的 stack 用