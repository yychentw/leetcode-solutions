# 933. Number of Recent Calls

## Question

You have a RecentCounter class which counts the number of recent requests within a certain time frame.  

Implement the RecentCounter class:  
- RecentCounter() Initializes the counter with zero recent requests.
- int ping(int t) Adds a new request at time t, where t represents some time in milliseconds, and returns the number of requests that has happened in the past 3000 milliseconds (including the new request). Specifically, return the number of requests that have happened in the inclusive range [t - 3000, t].

It is guaranteed that every call to ping uses a strictly larger value of t than the previous call.

Example 1:  
**Input**  
["RecentCounter", "ping", "ping", "ping", "ping"]  
[[], [1], [100], [3001], [3002]]  

**Output**  
[null, 1, 2, 3, 3]  

**Explanation**  
RecentCounter recentCounter = new RecentCounter();  
recentCounter.ping(1);     // requests = [1], range is [-2999,1], return 1  
recentCounter.ping(100);   // requests = [1, 100], range is [-2900,100], return 2  
recentCounter.ping(3001);  // requests = [1, 100, 3001], range is [1,3001], return 3  
recentCounter.ping(3002);  // requests = [1, 100, 3001, 3002], range is [2,3002], return 3  

Constraints:  
- 1 <= t <= 10^9
- Each test case will call ping with strictly increasing values of t.
- At most 10^4 calls will be made to ping.

---
Date: 2024-07-21  
Start time: 22:24  

## Problem statement confirmation

None.

Time checkpoint: 22:26 

## Solution idea

We can use queue to solve this problem:
- In RecentCounter(), initialize an empty queue. The size of the queue is the number of recent requests.
- In ping(int t), push t to the queue, keep checking if the front of the queue < t-3000 (if yes, pop it out), and finally return the size of the queue.

Time checkpoint: 22:30 

## Complexity analysis

Assume that the number of the calls is N.
- Time complexity (of `ping(int t)`): O(N) in the worst case? Because the queue may need to pop almost all the elements in the worst case.
- Space complexity: O(N), the size of the queue is related to the number of the calls.

Time checkpoint: 22:35 

## Implementation

```cpp
class RecentCounter {
public:
    queue<int> qu;

    RecentCounter() {
        while (!qu.empty()) {
            qu.pop();
        }
    }
    
    int ping(int t) {
        qu.push(t);
        while (qu.front() < t-3000) {
            qu.pop();
        }
        return qu.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
```

Time checkpoint: 22:39 

## Testing (dry run)

Example 1:  
**Input**  
["RecentCounter", "ping", "ping", "ping", "ping"]  
[[], [1], [100], [3001], [3002]]  
- `RecentCounter()`: null
- `ping(1)`: queue = [1], return 1
- `ping(100)`: queue = [1,100], return 2
- `ping(3001)`: queue = [1,100,3001], return 3
- `ping(100)`: queue = [100,3001,3002], return 3

End time: 22:41 

## Results

Time spent: 17m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: Accepted  

## Review

複習一下 C++ std::queue 語法：
- queue.empty()
- queue.size()
- queue.front(), queue.back()
- queue.push(), queue.pop()

基本上和 std::stack 差不多，但是 pop() 是移除 front()，另外 stack 存取元素的方法是 top()。