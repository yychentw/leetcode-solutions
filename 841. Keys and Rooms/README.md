# 841. Keys and Rooms

## Question

There are n rooms labeled from 0 to n - 1 and all the rooms are locked except for room 0. Your goal is to visit all the rooms. However, you cannot enter a locked room without having its key.  

When you visit a room, you may find a set of distinct keys in it. Each key has a number on it, denoting which room it unlocks, and you can take all of them with you to unlock the other rooms.  

Given an array rooms where rooms[i] is the set of keys that you can obtain if you visited room i, return true if you can visit all the rooms, or false otherwise.  

**Example 1:**  
- Input: rooms = [[1],[2],[3],[]]
- Output: true
- Explanation: We visit room 0 and pick up key 1. We then visit room 1 and pick up key 2. We then visit room 2 and pick up key 3. We then visit room 3. Since we were able to visit every room, we return true.

**Example 2:**  
- Input: rooms = [[1,3],[3,0,1],[2],[0]]
- Output: false
- Explanation: We can not enter room number 2 since the only key that unlocks it is in that room.

**Constraints:**  
- n == rooms.length
- 2 <= n <= 1000
- 0 <= rooms[i].length <= 1000
- 1 <= sum(rooms[i].length) <= 3000
- 0 <= rooms[i][j] < n
- All the values of rooms[i] are unique.

---
Date: 2025-02-13  
Start time: 14:11  

## Problem statement confirmation

- Total number of the keys should be no larger than 3000.
- The keys to a room can be placed in multiple rooms.
- The key must correspond to an existing room.
- There are no less than 2 rooms. That is, there's at least a locked room.
- There may be no key in a room.

Time checkpoint: 14:14  

## Solution idea

It seems to be a graph traversing problem. I would use stack DFS to store the keys and visit the rooms. Also, I would use an a vector with size n to record if the rooms are visited.  

Time checkpoint: 14:20  

## Complexity analysis

Assume that the number of the rooms is N and the total number of the keys is M:
- Time complexity: O(M) because I would push all the keys obtained when visiting rooms to the stack, and then use the keys to visit the remaining rooms.
- Space complexity: O(N+M) because I use a vector of size N and a stack of size M.

Time checkpoint: 14:23  

## Implementation

```cpp
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        vector<int> visited(rooms.size(), 0);
        stack<int> keys;

        for (int k: rooms[0]) {
            keys.push(k);
        }
        visited[0] = 1;

        while (!keys.empty()) {
            int current_key = keys.top();
            keys.pop();
            if (visited[current_key] == 0) {
                for (int k: rooms[current_key]) {
                    keys.push(k);
                }
                visited[current_key] = 1;
            }
        }

        for (int v: visited) {
            if (v == 0) {
                return false;
            }
        }
        return true;
    }
};
```

Time checkpoint: 14:32  

## Testing (dry run)

Example 1: Input: rooms = [[1],[2],[3],[]], Output: true
- visit rooms[0]: keys = [1], visited = [1,0,0,0]
- current_key = 1, visit rooms[1]: keys = [2], visited = [1,1,0,0]
- current_key = 2, visit rooms[2]: keys = [3], visited = [1,1,1,0]
- current_key = 3, visit rooms[3]: keys = [], visited = [1,1,1,1]
- return true

Example 2: Input: rooms = [[1,3],[3,0,1],[2],[0]], Output: false
- visit rooms[0]: keys = [1,3], visited = [1,0,0,0]
- current_key = 3, visit rooms[3]: keys = [1,0], visited = [1,0,0,1]
- current_key = 0, but we have visited rooms[0]: keys = [1], visited = [1,0,0,1]
- current_key = 1, visit rooms[1]: keys = [3,0,1], visited = [1,1,0,1]
- current_key = 1, but we have visited rooms[1]: keys = [3,0], visited = [1,1,0,1]
- current_key = 0, but we have visited rooms[0]: keys = [3], visited = [1,1,0,1]
- current_key = 3, but we have visited rooms[3]: keys = [], visited = [1,1,0,1]
- return false because we have not visited rooms[2]

End time: 14:43  

## Results

Time spent: 32m   
Whether to refer to others' solutions: No  
Results of submission to Leetcode: Accepted  

## Review

None
