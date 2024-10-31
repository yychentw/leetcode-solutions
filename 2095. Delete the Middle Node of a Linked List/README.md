# 2095. Delete the Middle Node of a Linked List

## Question

You are given the head of a linked list. Delete the middle node, and return the head of the modified linked list.  

The middle node of a linked list of size n is the ⌊n / 2⌋th node from the start using 0-based indexing, where ⌊x⌋ denotes the largest integer less than or equal to x.  

For n = 1, 2, 3, 4, and 5, the middle nodes are 0, 1, 1, 2, and 2, respectively.  

Example 1:  
Input: head = [1,3,4,7,1,2,6]  
Output: [1,3,4,1,2,6]  
Explanation:  
Since n = 7, node 3 with value 7 is the middle node, which is marked in red.  
We return the new list after removing this node.  

Example 2:  
Input: head = [1,2,3,4]  
Output: [1,2,4]  
Explanation:  
For n = 4, node 2 with value 3 is the middle node.

Example 3:  
Input: head = [2,1]  
Output: [2]  
Explanation:  
For n = 2, node 1 with value 1 is the middle node.
Node 0 with value 2 is the only node remaining after removing node 1.

Constraints:  
- The number of nodes in the list is in the range [1, 10^5].
- 1 <= Node.val <= 10^5

---
Date: 2024-10-31  
Start time: 20:17  

## Problem statement confirmation

- It is possible that the link list becomes empty after the middle node is deleted. But how can I return the head of an empty linked list?
- The number of nodes can be large (10^5). I may need to come up with a solution with linear time complexity.

Time checkpoint: 20:24  

## Solution idea

Because I have no information about the length of the linked list, I need to first go through the whole linked list to get the number of the nodes.  

Then, calculate the index of the middle node.  

Again, go through the linked list until the node before the middle node, and make it point to the node after the middle node.

Finally, return the head of the linked list. Be sure to keep the head at the beginning.  

Time checkpoint: 20:32  

## Complexity analysis

Assume that the length of the linked list is N.  
- Time complexity: O(N) because I go through the linked list one and a half times.
- Space complexity: O(1) because I only need to save the head node, the current node, and the length of the linked list.

Time checkpoint: 20:35  

## Implementation

```cpp
// Definition of a linked list
struct ListNode {
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode* next): val(x), next(next) {}
};

class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        // count the number of the nodes
        int n = 1;
        ListNode* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
            n = n + 1;
        }

        // calculate the index of the middle node
        int mid = n / 2;
        
        // go the the node before the middle node
        curr = head;
        for (int i = 1; i < mid; ++i) {
            curr = curr->next;
        }

        // skip the middle node
        if (curr->next != nullptr) {
            curr->next = curr->next->next;
        }

        return head;
    }
};
```

Not sure if it can correctly handle a linked list with only one node....  

Time checkpoint: 22:49  

## Testing (dry run)

Example 1: Input: head = [1,3,4,7,1,2,6], Output: [1,3,4,1,2,6]  
- Count the number of the nodes: n = 7
- Calculate the index of the middle node: 7 // 2 = 3
- Go the the node before the middle node: 1 -> 3 -> 4 (curr)
- Skip the middle node: curr.next = curr.next.next (1) (skip 7)
- Return 1 -> 3 -> 4 -> 1 -> 2 -> 6

Example 2: Input: head = [1,2,3,4], Output: [1,2,4]  
- Count the number of the nodes: n = 4
- Calculate the index of the middle node: 4 // 2 = 2
- Go the the node before the middle node: 1 -> 2 (curr)
- Skip the middle node: curr.next = curr.next.next (4) (skip 3)
- Return 1 -> 2 -> 4

Example 3: Input: head = [2,1], Output: [2]  
- Count the number of the nodes: n = 2
- Calculate the index of the middle node: 2 // 2 = 1
- Go the the node before the middle node: 2 (curr)
- Skip the middle node: curr.next = curr.next.next (nullptr) (skip 1)
- Return 2

My test case 1: Input: head = [1]
- Count the number of the nodes: n = 1
- Calculate the index of the middle node: 1 // 2 = 0
- Go the the node before the middle node: 1 (curr)
- Skip the middle node: curr.next = nullptr (skip ???)
- Return 1 (or should I return nullptr???)

End time: 21:01  

## Results

Time spent: 44m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: WA (should return nullptr when handling a linked list with only one node...)  

## Review

Revised implementation: 
```cpp
// Definition of a linked list
struct ListNode {
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode* next): val(x), next(next) {}
};

class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        // special case: return nullptr if head->next == nullptr
        if (head->next == nullptr) {
            return nullptr;
        }

        // count the number of the nodes
        int n = 1;
        ListNode* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
            n = n + 1;
        }

        // calculate the index of the middle node
        int mid = n / 2;
        
        // go the the node before the middle node
        curr = head;
        for (int i = 1; i < mid; ++i) {
            curr = curr->next;
        }

        // skip the middle node
        curr->next = curr->next->next;

        return head;
    }
};
```

- 複習 C++ struct 寫法，要能實作與操作 linked list
- 久沒刷題，重複修改的情況多，要想好再動手
- 這題保證 linked list 至少有一個 node，不然要考慮處理空 linked list 的情況

### 更好的做法：fast and slow pointers  

基本想法是 fast pointer 和 slow pointer 都從 linked list 的 head 出發，fast pointer 一次移動兩個 nodes，slow pointer 一次移動一個 node，當 fast pointer 到 linked list 的最後時，slow pointer 就剛好到了 linked list 的中間。  

不過實際上我們希望 slow pointer 停在 middle node 的前一個 node，因此要從 head 的「前一個 node」出發。也就是說必須在 head 前接一個 dummy node 作為 slow pointer 的起始點，這也可以同時解決只有一個 node 的 linked list 要移除唯一的 node 的問題。

這個做法可以進一步降低 time complexity，因為只要 pass through 整個 linked list 一次。  

實作如下：
```cpp
// Definition of a linked list
struct ListNode {
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode* next): val(x), next(next) {}
};

class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        ListNode* prev = new ListNode(0, head);

        ListNode* fast = head;
        ListNode* slow = prev;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        slow->next = slow->next->next;

        return prev->next;
    }
};
```