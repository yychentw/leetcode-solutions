# 547. Number of Provinces

## Question

There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.  

A province is a group of directly or indirectly connected cities and no other cities outside of the group.  

You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.  

Return the total number of provinces.  

**Example 1:**  
- Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
- Output: 2

**Example 2:**  
- Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
- Output: 3

**Constraints:**  
- 1 <= n <= 200
- n == isConnected.length
- n == isConnected[i].length
- isConnected[i][j] is 1 or 0.
- isConnected[i][i] == 1
- isConnected[i][j] == isConnected[j][i]

---
Date: 2025-02-17  
Start time: 21:07  

## Problem statement confirmation

- Can n be 0? No.
- How large can n be? 200.
- Cities are always mutual connected. No uni-direction connection.

Time checkpoint: 21:11  

## Solution idea

I would use DFS approach:  
At the beginning, I get the 0th city and all its connected cities. I push all the connected cities to a stack, and then start to find their connected cities and the connected cities of their connected cities and so on....  
When the stack becomes empty, we find a complete province.  

Then, if there are some cities not in the found province, I will also perform "DFS province finding process" for them.  
To check if a city is in a found province, I need to use a hash set to store the visited cities.
After all cities are visited, return the number of the province.

Time checkpoint: 21:20  

## Complexity analysis

Assume that the number of the cities is N: 
- Time complexity: O(N^2) (?) because I go through all the cities and check their connection with all the other cities
- Space complexity: O(N) because I use a hash set to store the visited cities

Time checkpoint: 21:23  

## Implementation

```cpp
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        stack<int> st;
        unordered_set<int> visited;
        int n = isConnected.size();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (visited.find(i) != visited.end()) {
                continue;
            }

            visited.insert(i);
            st.push(i);
            ++ans;
            while (!st.empty()) {
                int current = st.top();
                st.pop();
                for (int j = 0; j < n; ++j) {
                    if (isConnected[current][j] == 1 && visited.find(j) == visited.end()) {
                        visited.insert(j);
                        st.push(j);
                    }
                }
            }
        }
        return ans;
    }
};
```

Time checkpoint: 21:34  

## Testing (dry run)

Example 1: Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]], Output: 2
- n = 3
- i = 0: st=[0], visited=[0], ans = 1
    - current = 0, push 1: st=[1], visited=[0,1]
    - current = 1, no need to push other cities
- i = 1: skip because 1 in visited
- i = 2: st=[2], visited=[2], ans = 2
    - current = 2, no need to push other cities
- Return 2

Example 2: Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]], Output: 3
- n = 3
- i = 0: st=[0], visited=[0], ans = 1
    - current = 0, no need to push other cities
- i = 1: st=[1], visited=[0,1], ans = 2
    - current = 1, no need to push other cities
- i = 2: st=[2], visited=[0,1,2], ans = 3
    - current = 2, no need to push other cities
- Return 3

End time: 21:43  

## Results

Time spent: 36m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: Accepted  

## Review

以前只學過 hash table 沒有學過 hash set，第一次用 hash set！