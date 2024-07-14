# 443. String Compression

## Question

Given an array of characters chars, compress it using the following algorithm:

Begin with an empty string s. For each group of consecutive repeating characters in chars:
- If the group's length is 1, append the character to s.
- Otherwise, append the character followed by the group's length. 

The compressed string s should not be returned separately, but instead, be stored in the input character array chars. Note that group lengths that are 10 or longer will be split into multiple characters in chars.

After you are done modifying the input array, return the new length of the array.

You must write an algorithm that uses only constant extra space.

Example 1:  
Input: chars = ["a","a","b","b","c","c","c"]  
Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]  
Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".  

Example 2:  
Input: chars = ["a"]  
Output: Return 1, and the first character of the input array should be: ["a"]  
Explanation: The only group is "a", which remains uncompressed since it's a single character.  

Example 3:  
Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]  
Output: Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].  
Explanation: The groups are "a" and "bbbbbbbbbbbb". This compresses to "ab12".  
 

Constraints:  
- 1 <= chars.length <= 2000
- chars[i] is a lowercase English letter, uppercase English letter, digit, or symbol.

---
Date: 2024-07-14  
Start time: 21:29  

## Problem statement confirmation

- Note that only constant extra space can be used.
- The elements of the arrays can be lowercase English letter, uppercase English letter, digit, or symbol. Lowercase and uppercase letters should be considered different?
- The array must not be empty.

Time checkpoint: 21:36 

## Solution idea

- Go through the array. Pop out the first element each time.
- If it is the firstly popped element, record its value and set the occurence time to 1.
- If it is the same as the previous popped elements, add 1 to the occurence time.
- If it is different from the previous popped element, append the previously saved value (and occurence time) to the array (according to the compression rule!), record the new value and set the occurence to 1.
- Remember to append the value and occurence time when the loop ends.
- Return the length of the array.

Time checkpoint: 21:47 

## Complexity analysis

Assume that the length of the array is N.  
- Time complexity: O(N), since I go through the array once.
- Space complexity: O(1), since I only use two extra variables (value & occurence time) to temporarily save the string information. Furthermore, when the array is being modified, the size of the array must be no larger than the original size.

Time checkpoint: 21:55 

## Implementation

```python

class Solution:
    def compress(self, chars: List[str]) -> int:
        def append_compressed_str(value, count):
            chars.append(value)
            if count >= 10:
                s = str(count)
                for si in s:
                    chars.append(si)
            elif count > 1:
                chars.append(str(count))
        
        n = len(chars)
        for i in range(n):
            c = chars.pop(0)
            if i == 0:
                v = c
                count = 1
            elif c == v:
                count += 1
            else:
                append_compressed_str(v, count)
                v = c
                count = 1
        append_compressed_str(v, count)

        return len(chars)
```

Time checkpoint: 22:05 

## Testing (dry run)

Example 1: Input: chars = ["a","a","b","b","c","c","c"]  
n = 7
- i = 0, c = "a", v = "a", count = 1, chars = ["a","b","b","c","c","c"]
- i = 1, c = "a", v = "a", count = 2, chars = ["b","b","c","c","c"]
- i = 2, c = "b", v = "b", count = 1, chars = ["b","c","c","c","a","2"]
- i = 3, c = "b", v = "b", count = 2, chars = ["c","c","c","a","2"]
- i = 4, c = "c", v = "c", count = 1, chars = ["c","c","a","2","b","2"]
- i = 5, c = "c", v = "c", count = 2, chars = ["c","a","2","b","2"]
- i = 6, c = "c", v = "c", count = 3, chars = ["a","2","b","2"]

chars = ["a","2","b","2","c","3"], return 6

Example 2: Input: chars = ["a"]  
n = 1
- i = 0, c = "a", v = "a", count = 1, chars = []

chars = ["a"], return 1

Example 3: Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]  
n = 13  
- i = 0, c = "a", v = "a", count = 1, chars = ["b","b","b","b","b","b","b","b","b","b","b","b"]
- i = 1, c = "b", v = "b", count = 1, chars = ["b","b","b","b","b","b","b","b","b","b","b","a"]
- i = 2, c = "b", v = "b", count = 2, chars = ["b","b","b","b","b","b","b","b","b","b","a"]
- i = 3, c = "b", v = "b", count = 3, chars = ["b","b","b","b","b","b","b","b","b","a"]
- i = 4, c = "b", v = "b", count = 4, chars = ["b","b","b","b","b","b","b","b","a"]
- i = 5, c = "b", v = "b", count = 5, chars = ["b","b","b","b","b","b","b","a"]
- i = 6, c = "b", v = "b", count = 6, chars = ["b","b","b","b","b","b","a"]
- i = 7, c = "b", v = "b", count = 7, chars = ["b","b","b","b","b","a"]
- i = 8, c = "b", v = "b", count = 8, chars = ["b","b","b","b","a"]
- i = 9, c = "b", v = "b", count = 9, chars = ["b","b","b","a"]
- i = 10, c = "b", v = "b", count = 10, chars = ["b","b","a"]
- i = 11, c = "b", v = "b", count = 11, chars = ["b","a"]
- i = 12, c = "b", v = "b", count = 12, chars = ["a"]

chars = ["a","b","1","2"], return 4

End time: 22:17 

## Results

Time spent: 48m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode:  

## Review

這題比較常見的解法是 two pointers