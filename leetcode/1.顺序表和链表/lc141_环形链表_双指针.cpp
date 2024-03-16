

class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        ListNode *fast = head, *slow = head; //双指针--快慢指针
        while (fast && fast->next)           //fast指针不为空或者指向不为空，循环继续
        {
            slow = slow->next;               //慢指针走一步
            fast = fast->next->next;         //快指针走两步
            if(fast == slow){
                return true;                 //两指针相遇->有环，返回真
            }
        }
        return false;   //无环返回假
    }
};