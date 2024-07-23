# 649. Dota2 Senate

## Question

In the world of Dota2, there are two parties: the Radiant and the Dire.  

The Dota2 senate consists of senators coming from two parties. Now the Senate wants to decide on a change in the Dota2 game. The voting for this change is a round-based procedure. In each round, each senator can exercise one of the two rights:  
- Ban one senator's right: A senator can make another senator lose all his rights in this and all the following rounds.
- Announce the victory: If this senator found the senators who still have rights to vote are all from the same party, he can announce the victory and decide on the change in the game.

Given a string senate representing each senator's party belonging. The character 'R' and 'D' represent the Radiant party and the Dire party. Then if there are n senators, the size of the given string will be n.  

The round-based procedure starts from the first senator to the last senator in the given order. This procedure will last until the end of voting. All the senators who have lost their rights will be skipped during the procedure.  

Suppose every senator is smart enough and will play the best strategy for his own party. Predict which party will finally announce the victory and change the Dota2 game. The output should be "Radiant" or "Dire".  

Example 1:  
Input: senate = "RD"  
Output: "Radiant"  
Explanation:  
The first senator comes from Radiant and he can just ban the next senator's right in round 1.  
And the second senator can't exercise any rights anymore since his right has been banned.  
And in round 2, the first senator can just announce the victory since he is the only guy in the senate who can vote.  

Example 2:  
Input: senate = "RDD"  
Output: "Dire"  
Explanation:   
The first senator comes from Radiant and he can just ban the next senator's right in round 1.   
And the second senator can't exercise any rights anymore since his right has been banned.   
And the third senator comes from Dire and he can ban the first senator's right in round 1.   
And in round 2, the third senator can just announce the victory since he is the only guy in the senate who can vote.  

Constraints:
- n == senate.length
- 1 <= n <= 10^4
- senate[i] is either 'R' or 'D'.

---
Date: 2024-07-23  
Start time: 07:52  

## Problem statement confirmation

Can it be a tie?  

Time checkpoint: 07:53 

## Solution idea

Is it true: when the senators coming from one party are more than the senators from another party, the first party will win.  
Or is it related to the order?  

My test case 1: 
Input: senate = "RRDDDR"  
First round: "RRD"  
Second round: "RR", "Radiant" wins!  
It's related to the order.

Now I only comes up with a complicated solution with 2 queues and 4 variables:  

2 queues: 
- `qu`: the main queue
- `temp`: the temporarily queue

4 variables:
- `num_r`
- `num_d`
- `ban_r`
- `ban_d`

Steps:  
- Firstly, save the string to the `qu`.
- Iteratively get the front of `qu` `s`, 
    - if `s` == "D", ++`num_d` and ++`ban_r`
    - if `s` == "R", ++`num_r` and ++`ban_d`
- However, the previous senators may ban the current senator's right, so I need to revise the rule above:
    - if `s` == "D", 
        - if `ban_d`, `s` is banned and popped.
        - else ++`num_d` and ++`ban_r`, push `s` to `temp`
    - similarly if `s` == "R", 
        - if `ban_r`, `s` is banned and popped.
        - else ++`num_r` and ++`ban_d`, push `s` to `temp`
- After each round, check if one of `num_d` and `num_r` is 0, "Radiant" wins if `num_d` == 0 and "Dire" wins if `num_r` == 0. Otherwise, start another round (`qu` = `temp`).  

Time checkpoint: 08:12 

## Complexity analysis

Assume that the length of the string is N.
- Time complexity: not quite sure because we may iterate through the string multiple times...
- Space complexity: O(N) because I use 2 queue to store the info of the string.

Time checkpoint: 08:16 

## Implementation

```cpp
class Solution {
public:
    string predictPartyVictory(string senate) {
        queue<char> qu;
        int num_d, num_r, ban_d, ban_r = 0;
        for (int i = 0; i < senate.size(); ++i) {
            qu.push(senate[i]);
        }
        while (1) {
            queue<char> temp;
            for (int i = 0; i < qu.size(); ++i) {
                if (qu.front() == 'R') {
                    if (ban_r > 0) {
                        --ban_r;
                        qu.pop();
                    }
                    else {
                        ++num_r;
                        ++ban_d;
                        temp.push(qu.front());
                        qu.pop();
                    }
                }
                else {
                    if (ban_d > 0) {
                        --ban_d;
                        qu.pop();
                    }
                    else {
                        ++num_d;
                        ++ban_r;
                        temp.push(qu.front());
                        qu.pop();
                    }
                }
            }
            if (num_d > 0 && num_r == 0) {
                return "Dire";
            }
            else if (num_r > 0 && num_d == 0) {
                return "Radiant";
            }
            num_d = 0;
            num_r = 0;
            qu = temp;
        }
    }
};
```

Time checkpoint: 08:24 

## Testing (dry run)

Example 1: Input: senate = "RD"  
- Round 1: 
    - "R", num_r = 1, num_d = 0, ban_r = 0, ban_d = 1
    - "D", popped, num_r = 1, num_d = 0, ban_r = 0, ban_d = 0
    - return "Radiant"

Example 2: Input: senate = "RDD"  
- Round 1:  
    - "R", num_r = 1, num_d = 0, ban_r = 0, ban_d = 1
    - "D", popped, num_r = 1, num_d = 0, ban_r = 0, ban_d = 0
    - "D", num_r = 1, num_d = 1, ban_r = 1, ban_d = 0
- Round 2: ban_r = 1, ban_d = 0  
    - "R", popped, num_r = 0, num_d = 0, ban_r = 0, ban_d = 0
    - "D", num_r = 0, num_d = 1, ban_r = 1, ban_d = 0
    - return "Dire"

My test case 1: Input: senate = "RRDDDR"  
- Round 1:  
    - "R", num_r = 1, num_d = 0, ban_r = 0, ban_d = 1
    - "R", num_r = 2, num_d = 0, ban_r = 0, ban_d = 2
    - "D", popped, num_r = 2, num_d = 0, ban_r = 0, ban_d = 1
    - "D", popped, num_r = 2, num_d = 0, ban_r = 0, ban_d = 0
    - "D", num_r = 2, num_d = 1, ban_r = 1, ban_d = 0
    - "R", popped, num_r = 2, num_d = 1, ban_r = 0, ban_d = 0
- Round 2: num_r = 0, num_d = 0, ban_r = 0, ban_d = 0, "RRD"
    - "R", num_r = 1, num_d = 0, ban_r = 0, ban_d = 1
    - "R", num_r = 2, num_d = 0, ban_r = 0, ban_d = 2
    - "D", popped, num_r = 2, num_d = 0, ban_r = 0, ban_d = 1
    - return "Radiant"

End time: 08:30 

## Results

Time spent: 38m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: TLE (QQ)  

## Review

Revised solution idea:  
- Still use two queues, but one stores the order of "R" and the other stores the order of "D", which represent the order of the senators who still have rights.
- The best strategy is, always ban the rights of the next senator from another party until there are only senators from their party.
- While both queues are not empty, get the fronts of the queues, pop them, and compare their values (orders). Increase the smaller order and push it to the original queue (the senator that will have rights in the next round). The larger order will not be pushed (because the senator's rights are banned).
- The game ends when one of the queue is empty. The party from which there are still unbanned senators wins.

Time complexity: O(N) in the best case, O(N^2) in the worst case?  
Space complexity: O(N)  

Implementation  
```cpp
class Solution {
public:
    string predictPartyVictory(string senate) {
        queue<int> qd;
        queue<int> qr;
        int num_senators = senate.size();
        for (int i = 0; i < num_senators; ++i) {
            if (senate[i] == 'D') {
                qd.push(i);
            }
            else {
                qr.push(i);
            }
        }

        while (!qd.empty() && !qr.empty()) {
            int d = qd.front();
            int r = qr.front();

            qd.pop();
            qr.pop();

            if (d < r) {
                qd.push(d+num_senators);
            }
            else if (d > r) {
                qr.push(r+num_senators);
            }
        }

        if (!qd.empty()) {
            return "Dire";
        }
        else {
            return "Radiant";
        }
    }
};
```

注意 std::stack 和 std::queue 都沒有 clear()（雖然這題實際上沒用到）。  