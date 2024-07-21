# 735. Asteroid Collision

## Question

We are given an array asteroids of integers representing asteroids in a row.  

For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.  

Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.  

Example 1:  
Input: asteroids = [5,10,-5]  
Output: [5,10]  
Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.  

Example 2:  
Input: asteroids = [8,-8]  
Output: []  
Explanation: The 8 and -8 collide exploding each other.  

Example 3:  
Input: asteroids = [10,2,-5]  
Output: [10]  
Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide resulting in 10.  

Constraints:  
- 2 <= asteroids.length <= 10^4
- -1000 <= asteroids[i] <= 1000
- asteroids[i] != 0

---
Date: 2024-07-21  
Start time: 17:11  

## Problem statement confirmation

- No element == 0.
- One asteroid can collide with other asteroid multiple times.
- Input array length is always larger than 2.

Time checkpoint: 17:13 

## Solution idea

My test case 1:  
Input: asteroids = [8,-8,5]  
Output: [5]  

My test case 2:  
Input: asteroids = [5,8,-8]  
Output: [5]  

My test case 3:  
Input: asteroids = [-8,8]  
Output: [-8,8]  

- Set `temp` = 0. Iterate over the array. 
- If `temp` == 0, let `temp` = the current element and then continue the loop.
- Check if `temp` is positive and the current element is negative.
    - If yes, a collision happens. Compare the absolute values of `temp` and the current element.
        - If abs(`temp`) is larger, keep `temp` (do nothing).
        - If abs(`temp`) is smaller, keep checking if the back of the answer array collide with the current element.
        - If they are equal, 
            - If the answer array is not empty, `temp` = the back of the answer array and pop back.
            - If the answer array is empty, let `temp` = 0.
    - If no, push back the `temp` to the answer array and let `temp` = the current element.
- After the end of the loop, push back `temp` to the anser array if `temp` != 0.

Time checkpoint: 17:34 

## Complexity analysis

Assume the length of the array is N.
- Time complexity: Roughly O(N) because we only iterate over the array once (although we do some pushing-back and popping-back).
- Space complexity: O(N) for saving the answer.

Time checkpoint: 17:36 

## Implementation

```cpp
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        int temp = 0;
        vector<int> ans;
        for (int i = 0; i < asteroids.size(); ++i) {
            if (temp == 0) {
                temp = asteroids[i];
                continue;
            }
            if (temp > 0 && asteroids[i] < 0) {
                int sum = temp + asteroids[i];
                if (sum < 0 && !ans.empty()) {
                    temp = ans.back();
                    ans.pop_back();
                    --i;
                }
                else if (sum < 0 && ans.empty()) {
                    temp = asteroids[i];
                }
                else if (sum == 0 && !ans.empty()) {
                    temp = ans.back();
                    ans.pop_back();
                }
                else if (sum == 0 && ans.empty()) {
                    temp = 0;
                }
            }
            else {
                ans.push_back(temp);
                temp = asteroids[i];
            }
        }
        if (temp != 0) {
            ans.push_back(temp);
        }
        return ans;
    }
};
```

Time checkpoint: 17:44 

## Testing (dry run)

Example 1: Input: asteroids = [5,10,-5]  
- temp = 0
- i = 5, since temp == 0, temp = 5, ans = []
- i = 10, temp = 10, ans = [5]
- i = -5, collision! temp = 10, ans = [5]
- end, ans = [5,10]

Example 2: Input: asteroids = [8,-8]  
- temp = 0
- i = 8, since temp == 0, temp = 8, ans = []
- i = -8, collision! temp = 0, ans = []
- end, ans = []

Example 3: Input: asteroids = [10,2,-5]  
- temp = 0
- i = 10, since temp == 0, temp = 10, ans = [] 
- i = 2, temp = 2, ans = [10]
- i = -5, temp = 10, ans = []
- i = -5, temp = 10, ans = []
- end, ans = [10]

My test case 1: Input: asteroids = [8,-8,5]  
- temp = 0
- i = 8, since temp == 0, temp = 8, ans = [] 
- i = -8, collision! temp = 0, ans = []
- i = 5, since temp == 0, temp = 5, ans = [] 
- end, ans = [5]

My test case 2: Input: asteroids = [5,8,-8]  
- temp = 0
- i = 5, since temp == 0, temp = 5, ans = [] 
- i = 8, temp = 8, ans = [5]
- i = -8, collision! temp = 5, ans = []
- end, ans = [5]

My test case 3: Input: asteroids = [-8,8]  
- temp = 0
- i = -8, since temp == 0, temp = -8, ans = [] 
- i = 8, temp = 8, ans = [-8]
- end, ans = [-8,8]

End time: 18:06 

## Results

Time spent: 55m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: Accepted  

## Review

複習一下 C++ std::vector 相關語法（操作基本和 std::string 差不多）：
- vector.empty()
- vector.size()
- vector.begin(), vector.end()
- vector.clear()
- vector.front(), vector.back()
- vector.push_back(), vector.pop_back()

原本想用 <cmath> std::abs() 計算絕對值，後來發現這題中會發生碰撞的狀況一定是左邊正右邊負，和的正負就能推得絕對值比較結果。

以下是參考別人的解法，執行時間較長但邏輯比較簡單：
```cpp
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> ans;
        
        for (int asteroid: asteroids) {
            bool alive = true;
            while (!ans.empty() && asteroid < 0 && ans.back() > 0) {
                if (ans.back() < -asteroid) {
                    ans.pop_back();
                    continue;
                } else if (ans.back() == -asteroid) {
                    ans.pop_back();
                }
                alive = false;
                break;
            }
            if (alive) {
                ans.push_back(asteroid);
            }
        }
        
        return ans;
    }
};
```