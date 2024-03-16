
/*
思路：
    如果再定义一个新的链表，实现链表元素的反转，其实这是对内存空间的浪费。
    其实只需要改变链表的next指针的指向，直接将链表反转 ，而不用重新定义一个新的链表。

双指针法：
    cur指针、pre指针、tem指针临时存储cur的下一个结点；
    通过cur、pre改变链表指向。
*/

class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        ListNode *tmp;  // 保存cur的下一个结点
        ListNode *pre = NULL;   //pre为空。链表反转后，之前的首地址可以指向空
        ListNode *cur = head;   //cur指向未反转前的首元素
        while(cur){
            tmp = cur->next;    //保存cur的下一个结点，因为接下来要改变cur->next的指向
            cur->next = pre;    //链表反转
            //更新pre和cur指针
            pre = cur;
            cur = tmp;
        }
        return pre;
    }
};