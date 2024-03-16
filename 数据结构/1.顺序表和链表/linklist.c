#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//0.链表结构定义
typedef struct Node
{
    int data;   //数据域
    int *next;  //指针域
}Node;

//1.链表的初始化
Node *getNewNode(int val){  //得到一个数据为val，指向NULL的结点。
    Node *p = (Node *)malloc(sizeof(Node)); //为Node指针p开辟一个Node的空间
    p->data = val;
    p->next = NULL;
    return p;
}

//2.链表的插入
Node *insertNode(Node *head,int val,int pos){
    // 虚拟头节点方便程序内部操作，移动指针用来找到插入位置，给插入节点传入值val
    Node new_head, *p = &new_head, *node = getNewNode(val);
    new_head.next = head;   //让虚拟头结点的指针域指向链表的首地址
    for (int i = 0; i < pos; i++)
    {
        p = p->next;    //p指向要插入位置的前一个结点
    }
    node->next = p->next;
    p->next = node;
    return new_head.next;   //返回虚拟头节点后面的链表
}

//3.销毁链表
void clear_list(Node *head){
    if(head == NULL) return;
    for ( Node * p = head, *q; p; p = q)
    {   //结点p指向链表首地址；让q临时记录p的下一个结点，然后删除p，再让p被q赋值；p为空循环结束
        q = p->next;
        free(p);
    }
    return;
}

//4.打印链表元素
void output_linklist(Node *head){
    int n = 0;
    for (Node* p = head; p; p = p->next) n +=1;
    for(int i = 0; i < n; i++)
    {
        printf("%3d",i);
        printf("  ");
    }
    printf("\n");
    for(Node* p = head; p; p = p->next)
    {
        printf("%3d",p->data);
        printf("->");
    }
    printf("\n\n");
    return;
}

//5.查找元素
int find_val(Node *head, int val){
    Node *p = head;
    int n = 0;
    while(p){
        if(p->data == val){
            output_linklist(head);
            int len = n*(3 + 2) + 2;
            for(int i = 0; i < len; i++) printf(" ");
            printf("^\n");
            for(int i = 0; i < len; i++) printf(" ");
            printf("|\n");
            return 1;
        }
        n += 1;
        p = p->next;
    }
    return 0;
}

int main(void) {
    srand(time(0));
    #define MAX_OP 7
    Node *head = NULL; //新的空节点
    for (int i = 0; i < MAX_OP; i++)
    {
        int pos = rand() % (i+1), val = rand() % 100;   //得到插入位置和插入的值
        printf("insert %d at %d to linklist\n",val,pos);
        head = insertNode(head,val,pos);
        output_linklist(head);
    }

    int val;
    //printf("please inter the val:");
    while(~scanf("%d",&val)){ //千万别忘了 & 符号
        if(!find_val(head,val)){
            printf("not found");
            return -1;
        }
    }

    clear_list(head);
    return 0;
}