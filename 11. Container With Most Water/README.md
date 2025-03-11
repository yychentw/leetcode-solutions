# 11. Container With Most Water

## Question

You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).  

Find two lines that together with the x-axis form a container, such that the container contains the most water.  

Return the maximum amount of water a container can store.  

Notice that you may not slant the container.  

**Example 1:**  
- Input: height = [1,8,6,2,5,4,8,3,7]
- Output: 49

**Example 2:**  
- Input: height = [1,1]
- Output: 1

**Constraints:**  
- n == height.length
- 2 <= n <= 10^5
- 0 <= height[i] <= 10^4

---
Date: 2025-03-11  
Start time: 22:02  

## Problem statement confirmation

- There are at least 2 heights, so there's always some horizontal space to contain water.
- The height may be 0. In some extreme case, no water can be contained because both selected heights are 0.
- The maximum space to contain water is 10^5*10^4 = 10^9. Should we consider integer overflow?

Time checkpoint: 22:08  

## Solution idea

I will use 2 pointers, one from the left and another from the right, to explore the space that can contain water.  

when left != right, I will compare the values of height[left] and height[right]. For the side with lower height, e.g., left, move it to the right next index. And if height[right] is lower, move right to the left next index.  

Everytime moving the pointers, also calculate the space for containing water min(height[left], height[right])*(right-left), and record the maximum space (the amount of water it can contain) as the answer.  

Time checkpoint: 22:16  

## Complexity analysis

The length of height is n:
- Time complexity: O(n) because I use 2 pointers to go through the whole height array once.
- Space complexity: O(1) because I only use left, right, max_water to store information.

Time checkpoint: 22:18  

## Implementation

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int max_area = 0;
        while (left != right) {
            int area = min(height[left], height[right]) * (right-left);
            if (area > max_area) {
                max_area = area;
            }
            if (height[left] <= height[right]) {
                left++;
            }
            else {
                right--;
            }
        }
        return max_area;
    }
};
```

Time checkpoint: 22:22  

## Testing (dry run)

Example 1: Input: height = [1,8,6,2,5,4,8,3,7]; Output: 49
- left = 0, right = 8, area = 8
- left = 1, right = 8, area = 49
- left = 1, right = 7, area = 24
- left = 1, right = 6, area = 40
- left = 2, right = 6, area = 24
- left = 3, right = 6, area = 6
- left = 4, right = 6, area = 10
- left = 5, right = 6, area = 4
- left == right = 6, end
- return 49

Example 2: Input: height = [1,1]; Output: 1
- left = 0, right = 1, area = 1
- left == right = 1, end
- return 1

My test case: Input: height = [4,1,6,4]; Output: 12
- left = 0, right = 3, area = 12
- left = 1, right = 3, area = 2
- left = 2, right = 3, area = 4
- left == right = 2, end
- return 12

End time: 22:30  

## Results

Time spent: 28m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: Accepted  

## Review
