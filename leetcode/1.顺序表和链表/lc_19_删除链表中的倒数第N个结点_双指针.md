

```c++
class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode new_head;
        ListNode *fast = &new_head, *slow = &new_head;
        new_head.next = head;  //虚拟头节点，方便返回新链表
        for (int i = 0; i <= n; i++) fast = fast->next; //快的先走n+1步
        while (fast) fast = fast->next, slow = slow->next;  //再同步走
        slow->next = slow->next->next;  //慢的将要删除的结点断开
        return new_head.next;
    }
};
```