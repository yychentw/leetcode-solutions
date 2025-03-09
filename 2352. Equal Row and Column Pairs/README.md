# 2352. Equal Row and Column Pairs

## Question

Given a 0-indexed n x n integer matrix grid, return the number of pairs (ri, cj) such that row ri and column cj are equal.  

A row and column pair is considered equal if they contain the same elements in the same order (i.e., an equal array).  

**Example 1:**  
- Input: grid = [[3,2,1],[1,7,6],[2,7,7]]
- Output: 1
- Explanation: There is 1 equal row and column pair:
    - (Row 2, Column 1): [2,7,7]

**Example 2:**  
- Input: grid = [[3,1,2,2],[1,4,4,5],[2,4,2,2],[2,4,2,2]]
- Output: 3
- Explanation: There are 3 equal row and column pairs:
    - (Row 0, Column 0): [3,1,2,2]
    - (Row 2, Column 2): [2,4,2,2]
    - (Row 3, Column 2): [2,4,2,2]

**Constraints:**  
- n == grid.length == grid[i].length
- 1 <= n <= 200
- 1 <= grid[i][j] <= 10^5

---
Date: 2025-03-09  
Start time: 10:59  

## Problem statement confirmation

- n is at least 1.
- The grid value can be large.
- An equal row and column pair may not always exist.

Time checkpoint: 11:02  

## Solution idea

The basic idea is, I will use a hash map to store each row and check if any column is eqaul to them.  

However, a vector cannot be a key in the unordered_map, and the grid values can be large so that I cannot think of a way to encode a row into something like a string (and use it as a key).  

How about a vector of unordered_map? unordered_map[i] will store the ith column values as key and the row index as value. We can check if a column always has a matched value in the unordered_maps and if the row indexes are all the same, and then we can find the equal row and column pairs.  

Time checkpoint: 11:14  

## Complexity analysis

Assume that the number of rows and columns is N:
- Time complexity: O(N^2)
    - Build the hash maps: O(N^2)
    - Query the column: O(N^2)
- Space complexity: O(N^N) because I use a vector with size N to store N hash_maps, each hash_map may store N values.

Time checkpoint: 11:17  

## Implementation

```cpp
class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = grid.size();

        vector<unordered_map<int, unordered_set<int>>> umaps;
        for (int i = 0; i < n; i++) {
            unordered_map<int, unordered_set<int>> umap;
            umaps.push_back(umap);
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (umaps[j].find(grid[i][j]) == umaps[j].end()) {
                    umaps[j][grid[i][j]] = unordered_set<int>{i};
                }
                else {
                    umaps[j][grid[i][j]].insert(i);
                }
            }
        }

        int count = 0;
        for (int j = 0; j < n; j++) {
            // Check Column j
            unordered_set<int> candidates;
            for (int i = 0; i < n; i++) {
                if (umaps[i].find(grid[i][j]) == umaps[i].end()) {
                    candidates.clear();
                    continue;
                }
                else if (i == 0) {
                    candidates = umaps[i][grid[i][j]];
                }
                else {
                    vector<int> removed_list;
                    for (int cand: candidates) {
                        if (umaps[i][grid[i][j]].find(cand) == umaps[i][grid[i][j]].end()) {
                            removed_list.push_back(cand);
                        }
                    }
                    for (int r: removed_list) {
                        candidates.erase(r);
                    }
                    if (candidates.empty()) {
                        continue;
                    }
                }
            }
            count += candidates.size();
        }

        return count;
    }
};
```

Time checkpoint: 11:54  

## Testing (dry run)

Example 1: Input: grid = [[3,2,1],[1,7,6],[2,7,7]]; Output: 1
- n = 3
- Build umaps: [{3: {0}, 1: {1}, 2: {2}}, {2: {0}, 7: {1, 2}}, {1: {0}, 6: {1}, 7: {2}}]
- Query
    - [3,1,2]: candidates = {0} -> continue
    - [2,7,7]: candidates = {2} -> candidates = {2} -> candidates = {2} -> count = 1
    - [1,6,7]: candidates = {1} -> continue
- Return 1

Example 2: Input: grid = [[3,1,2,2],[1,4,4,5],[2,4,2,2],[2,4,2,2]]; Output: 3
- n = 4
- Build umaps: [{3: {0}, 1: {1}, 2: {2, 3}}, 
                {1: {0}, 4: {1, 2, 3}}, 
                {2: {0, 2, 3}, 4: {1}}, 
                {2: {0, 2, 3}, 5: {1}}]
- Query
    - [3,1,2,2]: candidates = {0} -> candidates = {0} -> candidates = {0} -> candidates = {0} -> count = 1
    - [1,4,4,4]: candidates = {1} -> candidates = {1} -> candidates = {1} -> continue
    - [2,4,2,2]: candidates = {2,3} -> candidates = {2,3} -> candidates = {2,3} -> candidates = {2,3} -> count = 3
    - [2,5,2,2]: candidates = {2,3} -> continue
- Return 3

End time: 12:05  

## Results

Time spent: 1h6m  
Whether to refer to others' solutions: No (但查了不少語法...)  
Results of submission to Leetcode: Accepted (但超慢...)  

## Review

雖然 unordered_map 不能以 vector 當 key，但 map 可以...。想得太複雜了。

```cpp
class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = grid.size();
        map<vector<int>, int> mp;
        for (int i = 0; i < n; i++) {
            mp[grid[i]]++;
        }

        int count = 0;
        for (int j = 0; j < n; j++) {
            vector<int> tmp(n, 0);
            for (int i = 0; i < n; i++) {
                tmp[i] = grid[i][j];
            }
            count += mp[tmp];
        }
        return count;
    }
};
```

- Time complexity: O(N^2)
- Space complexity: O(N^2)

另外值得注意的是當存取不存在的 key 時，unordered_map 和 map 會呼叫 default constructor，以 value 為 int 型別來說，預測會被設為 0。