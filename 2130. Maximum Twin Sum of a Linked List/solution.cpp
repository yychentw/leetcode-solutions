struct ListNode {
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode* next): val(x), next(next) {}
};

class Solution {
public: 
    int pairSum(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }

        ListNode* reversed_head = nullptr;
        while (slow != nullptr) {
            ListNode* temp = slow->next;
            slow->next = reversed_head;
            reversed_head = slow;
            slow = temp;
        }

        int max_twin_sum = 0;
        while (reversed_head != nullptr) {
            int twin_sum = head->val + reversed_head->val;
            if (twin_sum > max_twin_sum) {
                max_twin_sum = twin_sum;
            }
            head = head->next;
            reversed_head = reversed_head->next;
        }

        return max_twin_sum;
    }
};