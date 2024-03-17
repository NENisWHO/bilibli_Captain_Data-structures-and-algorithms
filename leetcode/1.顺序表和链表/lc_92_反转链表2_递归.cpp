/*
给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。
请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。

示例 1：
输入：head = [1,2,3,4,5], left = 2, right = 4
输出：[1,4,3,2,5]

示例 2：
输入：head = [5], left = 1, right = 1
输出：[5]
*/

class Solution
{
public:
    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        if(left == 1 && right == 1) return head; //没意义直接返回原链表
        /*
            递归大链表-》小链表
            1->2-><3>-><4>->5->NULL     l=3 r=4
               2-><3>-><4>->5->NULL     l=2 r=3
                  <3>-><4>->5->NULL     l=1 r=2
                                        

        */
        if(left != 1){
            // 递归 不用操心函数怎么实现的，只知道函数是用来干啥的————用来反转链表的
            // 左右同时-1说明还没到待反转区域，，将子链表挂在当前头节点的后面
            head->next = reverseBetween(head->next, left-1, right-1);
        }else {
            ListNode *tail = head->next, *new_head;
            new_head = reverseBetween(head->next, left, right - 1);

            head->next = tail->next;    //这两步是实现反转
            tail->next = head;

            head = new_head;
        }
        return head;
    }
};