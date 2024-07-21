# 394. Decode String

## Question

Given an encoded string, return its decoded string.  

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.  

You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].  

The test cases are generated so that the length of the output will never exceed 10^5.  

Example 1:  
Input: s = "3[a]2[bc]"  
Output: "aaabcbc"  

Example 2:  
Input: s = "3[a2[c]]"  
Output: "accaccacc"  

Example 3:  
Input: s = "2[abc]3[cd]ef"  
Output: "abcabccdcdcdef"  

Constraints:  
- 1 <= s.length <= 30
- s consists of lowercase English letters, digits, and square brackets '[]'.
- s is guaranteed to be a valid input.
- All the integers in s are in the range [1, 300].

---
Date: 2024-07-21  
Start time: 15:13  

## Problem statement confirmation

- Note that it is possible that there are square brackets inside square brackets. (Therefore, we should decode the inner brackets first and then the outer ones).
- The square brackets are well paired.
- It is guarenteed that the output length <= 10^5 

Time checkpoint: 15:17 

## Solution idea

My test case:  
Input: s = "ef2[abc]3[cd]"  
Output: "efabcabccdcdcd"  

I am thinking about using stack to solve this problem: 
1. Iterate over the encoded string
2. If encountering a digit, push the previous substring to the stack.
3. If encountering "[", push the previous digit substring to the stack.
4. If encountering "]", pop the digit substring from the stack and transform it into integer k, repeat the current substring by k times, and concatenate the resulted string with the top string of the stack.
5. After all the characters of the encoded string are processed, get the string inside the stack as the answer.

Time checkpoint: 15:31 

## Complexity analysis

Assume that the length of the encoded string is N, the integer in the string is k.
- Time complexity: O(N) in the best case and O(kN) in the worst case? If there's no square bracket in the input string, then the time complexity will be O(N). However, if the input string is like "k[string]", then the time complexity will roughly be O(kN), because we not only iterate over the string but also repeat almost the whole string by k times. (Any other possible cases? Highly nested string?)
- Space complexity: O(N) in the best case and O(kN) in the worst case? It depends on the output size.

Time checkpoint: 15:38 

## Implementation

```cpp
class Solution {
public:
    string decodeString(string s) {
        stack<string> st;
        string temp = "";
        for (char si: s) {
            if (isdigit(si)) {
                st.push(temp);
                temp = si;
            }
            else if (si == '[') {
                st.push(temp);
                temp = "";
            }
            else if (si == ']') {
                int k = stoi(st.top());
                st.pop();
                string decoded = "";
                for (int i = 0; i < k; ++i) {
                    decoded += temp;
                }
                temp = st.top() + decoded;
                st.pop();
            }
            else {  // English letters
                temp += si;
            }
        }
        return temp;
    }
};
```

Time checkpoint: 15:51 

## Testing (dry run)

Example 1: Input: s = "3[a]2[bc]"  
- si = "3", temp = "3", stack = [""]
- si = "[", temp = "", stack = ["","3"]
- si = "a", temp = "a", stack = ["","3"]
- si = "]", temp = "aaa", stack = []
- si = "2", temp = "2", stack = ["aaa"]
- si = "[", temp = "", stack = ["aaa","2"]
- si = "b", temp = "b", stack = ["aaa","2"]
- si = "c", temp = "bc", stack = ["aaa","2"]
- si = "]", temp = "aaabcbc", stack = [], return "aaabcbc"

Example 2: Input: s = "3[a2[c]]"  
- si = "3", temp = "3", stack = [""]
- si = "[", temp = "", stack = ["","3"]
- si = "a", temp = "a", stack = ["","3"]
- si = "2", temp = "2", stack = ["","3","a"]
- si = "[", temp = "", stack = ["","3","a","2"]
- si = "c", temp = "c", stack = ["","3","a","2"]
- si = "]", temp = "acc", stack = ["","3"]
- si = "]", temp = "accaccacc", stack = [], return "accaccacc"

Example 3: Input: s = "2[abc]3[cd]ef"  
- si = "2", temp = "2", stack = [""]
- si = "[", temp = "", stack = ["","2"]
- si = "a", temp = "a", stack = ["","2"]
- si = "b", temp = "ab", stack = ["","2"]
- si = "c", temp = "abc", stack = ["","2"]
- si = "]", temp = "abcabc", stack = []
- si = "3", temp = "3", stack = ["abcabc"]
- si = "[", temp = "", stack = ["abcabc","3"]
- si = "c", temp = "c", stack = ["abcabc","3"]
- si = "d", temp = "cd", stack = ["abcabc","3"]
- si = "]", temp = "abcabccdcdcd", stack = []
- si = "e", temp = "abcabccdcdcde", stack = []
- si = "f", temp = "abcabccdcdcdef", stack = [], return "abcabccdcdcdef"

My test case: Input: s = "ef2[abc]3[cd]"   
- si = "e", temp = "e", stack = []
- si = "f", temp = "ef", stack = []
- si = "2", temp = "2", stack = ["ef"]
- si = "[", temp = "", stack = ["ef","2"]
- si = "a", temp = "a", stack = ["ef","2"]
- si = "b", temp = "ab", stack = ["ef","2"]
- si = "c", temp = "abc", stack = ["ef","2"]
- si = "]", temp = "efabcabc", stack = []
- si = "3", temp = "3", stack = ["efabcabc"]
- si = "[", temp = "", stack = ["efabcabc","3"]
- si = "c", temp = "c", stack = ["efabcabc","3"]
- si = "d", temp = "cd", stack = ["efabcabc","3"]
- si = "]", temp = "efabcabccdcdcd", stack = [], return "efabcabccdcdcd"

End time: 16:05 

## Results

Time spent: 52m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: WA (QQ)  

## Review

Test case: Input: s = "100[leetcode]"
- si = "1", temp = "1", stack = [""]
- si = "0", temp = "0", stack = ["","1"]... Oh no I need to concatenate the digit string.

The revised solution idea:
1. Iterate over the encoded string
2. If encountering a digit, check if the previous substring is a digit string: 
    a. if yes, concatenate the digit to the substring.
    b. if no, push the previous substring to the stack, and let the digit as the new substring.
3. If encountering "[", push the previous digit substring to the stack.
4. If encountering "]", pop the digit substring from the stack and transform it into integer k, repeat the current substring by k times, and concatenate the resulted string with the top string of the stack.
5. After all the characters of the encoded string are processed, return the resulted string as the answer.

```cpp
class Solution {
public:
    string decodeString(string s) {
        stack<string> st;
        string temp = "";
        for (char si: s) {
            if (isdigit(si)) {
                if (temp.empty() || !isdigit(temp[0])) {
                    st.push(temp);
                    temp = si;
                }
                else {
                    temp += si;
                }
            }
            else if (si == '[') {
                st.push(temp);
                temp = "";
            }
            else if (si == ']') {
                int k = stoi(st.top());
                st.pop();
                string decoded = "";
                for (int i = 0; i < k; ++i) {
                    decoded += temp;
                }
                temp = st.top() + decoded;
                st.pop();
            }
            else {  // English letters
                temp += si;
            }
        }
        return temp;
    }
};
```

Beats 100% runtime!  

C++ 的部分需要注意 string 和 stack 相關的語法

stack  
- stack.empty()
- stack.size()
- stack.push()
- stack.pop()
- stack.top()

string
- string.empty()
- string.size()
- string.begin(), string.end()
- string.clear()
- string.front(), string.back()
- string.push_back(), string.pop_back()
- +=
- stoi()：將 string 轉成 integer

至於判別 character 是否為 digit，解法使用 <cctype> std::isdigit，不過如果忘記的話，可以透過 char 大小判別（`s[i] >= '0' && s[i] <= '9'`）  

另外將數字與字母字串分開存取，邏輯會更簡單，不過儲存空間會占用多一點