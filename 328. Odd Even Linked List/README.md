# 328. Odd Even Linked List

## Question

Given the head of a singly linked list, group all the nodes with odd indices together followed by the nodes with even indices, and return the reordered list.  

The first node is considered odd, and the second node is even, and so on.  

Note that the relative order inside both the even and odd groups should remain as it was in the input.  

You must solve the problem in O(1) extra space complexity and O(n) time complexity.  

**Example 1:**  
Input: head = [1,2,3,4,5]  
Output: [1,3,5,2,4]  

**Example 2:**  
Input: head = [2,1,3,5,6,4,7]  
Output: [2,3,6,7,1,5,4]  

**Constraints:**  
- The number of nodes in the linked list is in the range [0, 10^4].
- -10^6 <= Node.val <= 10^6

---
Date: 2024-11-04  
Start time: 22:16  

## Problem statement confirmation

- Note that the number of the nodes in the linked list can be 0. In this case, return the empty linked list.
- The time and space complexity requirements are provided. 

Time checkpoint: 22:19  

## Solution idea

I will use 3 pointers: odd pointer, even pointer, and current pointer.
- The odd pointer starts from the first node, and go to the next next node each time.
- The even pointer starts from the dummy node before the head, and go to the next next node each time.
- The current pointer starts from the head. It is firstly followed by the nodes that the odd pointer visits, and then by the nodes that the even pointer visits.

Special cases: 
- The number of the nodes = 0: Return an empty linked list.
- The number of the nodes = 1: Return the original linked list.
- The number of the nodes = 2: Return the original linked list.

The reordering happens when the number of the nodes > 2.  

Time checkpoint: 22:29  

## Complexity analysis

Assume that the number of the nodes in the linked list is N.  
- Time complexity: O(N/2+N/2+N) ~= O(N) because the odd and even pointers go through half of the linked list respectively, and the current pointer should go through all the nodes in the linked list.
- Space complexity: O(3) ~= O(1) because I use 3 pointers.

Time checkpoint: 10:32  

## Implementation

```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode* next): val(x), next(next) {}
};

class Solution {
public: 
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode* odd = head;
        ListNode* even = new ListNode(0, head);
        ListNode* curr = head;

        while (odd->next != nullptr && odd->next->next != nullptr) {
            odd = odd->next->next;
            curr->next = odd;
            curr = curr->next;
        }

        while (even->next != nullptr && even->next->next != nullptr) {
            even = even->next->next;
            curr->next = even;
            curr = curr->next;
        }

        curr->next = nullptr;

        return head;
    }
};
```

Time checkpoint: 22:46  

## Testing (dry run)

Example 1: Input: head = [1,2,3,4,5], Output: [1,3,5,2,4]  
- head != nullptr, head->next != nullptr
- odd = head (node "1"), even = prev (node before "1"), curr = head (node "1")
- odd node iteration
    - odd = node "3", curr->next = odd (node "3"), curr = curr->next: 1->3 (curr)->4->5
    - odd = node "5", curr->next = odd (node "5"), curr = curr->next: 1->3->5 (curr)
- even node iteration
    - even = node "2", curr->next = even (node "2"), curr = curr->next: 1->3->5->2 (curr)->3 (loop)
    - even = node "4", curr->next = even (node "4"), curr = curr->next: 1->3->5->2->4 (curr)->5 (loop)
- Make sure the next node of the last even node is nullptr. Return 1->3->5->2->4.

Example 2: Input: head = [2,1,3,5,6,4,7], Output: [2,3,6,7,1,5,4]
- head != nullptr, head->next != nullptr
- odd = head (node "2"), even = prev (node before "2"), curr = head (node "2")
- odd node iteration
    - odd = node "3", curr->next = odd (node "3"), curr = curr->next: 2->3 (curr)->5->6->4->7
    - odd = node "6", curr->next = odd (node "6"), curr = curr->next: 2->3->6 (curr)->4->7
    - odd = node "7", curr->next = odd (node "7"), curr = curr->next: 2->3->6->7 (curr)
- even node iteration
    - even = node "1", curr->next = even (node "1"), curr = curr->next: 2->3->6->7->1 (curr)->3 (loop)
    - even = node "5", curr->next = even (node "5"), curr = curr->next: 2->3->6->7->1->5 (curr)->6 (loop)
    - even = node "4", curr->next = even (node "4"), curr = curr->next: 2->3->6->7->1->5->4 (curr)->7 (loop)
- Make sure the next node of the last even node is nullptr. Return 2->3->6->7->1->5->4.

Test case 1: Input: head = [], Output: []
- head == nullptr, return head.

Test case 2: Input: head = [1], Output: [1]
- head->next == nullptr, return head.

Test case 3: Input: head = [1,2], Output: [1,2]
- head != nullptr, head->next != nullptr
- odd = head (node "1"), even = prev (node before "1"), curr = head (node "1")
- odd node iteration
- even node iteration
    - even = node "2", curr->next = even (node "2"), curr = curr->next: 1->2 (curr)
- Make sure the next node of the last even node is nullptr. Return 1->2.

End time: 23:08  

## Results

Time spent: 52m  
Whether to refer to others' solutions: No  
Results of submission to Leetcode: TLE  

## Review

可能有地方陷入無窮迴圈了  

三個 pointers 的解題方向沒錯，但解題思路可以更簡單一點：
- odd pointer：把 odd nodes 串起來
- even pointer：把 even nodes 串起來
- temp pointer：記錄 even head，最後接在 odd linked list 後面

修改實作如下：
```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode* next): val(x), next(next) {}
};

class Solution {
public: 
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode* odd = head;
        ListNode* even = head->next;
        ListNode* temp = even;

        while (even != nullptr && even->next != nullptr) {
            odd->next = odd->next->next;
            even->next = even->next->next;
            odd = odd->next;
            even = even->next;
        }

        odd->next = temp;

        return head;
    }
};
```

為什麼是檢查 even 和 even->next 是否為 nullptr？
- 假設 node 有偶數個，最後會檢查到 even->next 為 nullptr，而此時 odd linked list 剛好接完，可以接 even linked list，且確保結尾是 nullptr
- 假設 node 有奇數個，最後會檢查到 even 為 nullptr，，而此時 odd linked list 剛好接完，可以接 even linked list，且確保結尾是 nullptr

如果檢查 odd 和 odd->next 是否為 nullptr 呢？
- 假設 node 有偶數個，還沒檢查到 odd 和 odd->next 是 nullptr，even->next->next 就已經 invalid
- 假設 node 有奇數個，最後會檢查到 odd->next 是 nullptr，even 已經是 nullptr，此時 odd linked list 接上 even linked list 是可以的

重點應該是，應該檢查後面的 pointer，因為它會最靠近邊界