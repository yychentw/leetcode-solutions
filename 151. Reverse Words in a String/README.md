# 151. Reverse Words in a String

## Question

Given an input string s, reverse the order of the words.  

A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.  

Return a string of the words in reverse order concatenated by a single space.  

Note that s may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.  

**Example 1:**  
- Input: s = "the sky is blue"
- Output: "blue is sky the"

**Example 2:**  
- Input: s = "  hello world  "
- Output: "world hello"
- Explanation: Your reversed string should not contain leading or trailing spaces.

**Example 3:**  
- Input: s = "a good   example"
- Output: "example good a"
- Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.

**Constraints:**  
- 1 <= s.length <= 10^4
- s contains English letters (upper-case and lower-case), digits, and spaces ' '.
- There is at least one word in s.

---
Date: 2025-03-10  
Start time: 21:33  

## Problem statement confirmation

- The string cannot be empty, and there's at least 1 word in the string.
- There can be multiple spaces between, before, or after words.

Time checkpoint: 21:35  

## Solution idea

Firstly, I will create an empty output string.  

Then, I will loop through the string, use a temporary string to store the non-space charactors, and add it to the begin() of the output string when a space is met. After adding a word, clear the temporary string. And remember always add a space after the newly added words.  

Time checkpoint: 21:46  

## Complexity analysis

Assume that the length of the string is N:
- Time complexity: O(N) because I only traverse the string once.
- Space complexity: O(N)? because I add all the words first before removing the original string.

Time checkpoint: 21:49  

## Implementation

```cpp
class Solution {
public:
    string reverseWords(string s) {
        string ans = "";
        string tmp = "";
        for (char si: s) {
            if (si != ' ') {
                tmp += si;
            }
            else if (!tmp.empty()) {
                ans = tmp + " " + ans;
                tmp = "";
            }
        }
        if (!tmp.empty()) {
            ans = tmp + " " + ans;
        }
        ans.erase(ans.end()-1);
        return ans;
    }
};
```

Time checkpoint: 21:59  

## Testing (dry run)

Example 1: Input: s = "the sky is blue", Output: "blue is sky the"
- i = 0~2, tmp = "the", ans = ""
- i = 3, tmp = "", ans = "the "
- i = 4~6, tmp = "sky", ans = "the "
- i = 7, tmp = "", ans = "sky the "
- i = 8~9, tmp = "is", ans = "sky the "
- i = 10, tmp = "", ans = "is sky the "
- i = 11~14, tmp = "blue", ans = "is sky the "
- ans = "blue is sky the"

Example 2: Input: s = "  hello world  ", Output: "world hello"
- i = 0~1, tmp = "", ans = ""
- i = 2~6, tmp = "hello", ans = ""
- i = 7, tmp = "", ans = "hello "
- i = 8~12, tmp = "world", ans = "hello "
- i = 13~14, tmp = "", ans = "world hello "
- ans = "world hello"

Example 3: Input: s = "a good   example", Output: "example good a"
- i = 0, tmp = "a", ans = ""
- i = 1, tmp = "", ans = "a "
- i = 2~5, tmp = "good", ans = "a "
- i = 6~8, tmp = "", ans = "good a "
- i = 9~15, tmp = "example", ans = "good a "
- ans = "example good a"

End time: 22:17  

## Results

Time spent: 44m   
Whether to refer to others' solutions: No  
Results of submission to Leetcode: Accepted  

## Review

明明以前寫過的題目但還是寫不順@@  

要注意 string 的 element 是 char，條件判別是否為空格時要用單引號 ' '。  