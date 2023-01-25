#include "./includes/Solution.h"

ListNode* Solution::addTwoNumbers(ListNode* l1, ListNode* l2)
{
    ListNode* ret = new ListNode();
    ListNode* next = ret;

    int carry_fwd = 0;

    while(l1 != nullptr || l2 != nullptr || carry_fwd != 0)
    {
        int tot = 0;

        if (l1 != nullptr) {tot += l1->val; l1 = l1->next;}
        if (l2 != nullptr) {tot += l2->val; l2 = l2->next;}

        tot += carry_fwd;
        carry_fwd = tot / 10;
        tot = tot % 10;
        
        next->next = new ListNode(tot);
        next = next->next;
    }

    ListNode* dummy = ret;
    ret = ret->next;

    delete(dummy);

    return ret;
}