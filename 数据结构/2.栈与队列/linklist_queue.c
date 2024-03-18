#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 链表的准备 */
typedef struct Node{    //结点的结构定义
    int data;           //数据域
    struct Node *next;  //指针域
}Node;

typedef struct linklist{    //链表的结构定义
    int size;               //链表的尺寸
    Node head, *tail;       //头结点，和尾指针结点---》 有头链表
}linklist;

Node *getNewNode(int val){  //将值val封装到结点中
    Node * p = (Node *)malloc(sizeof(Node)); //为结点p开辟空间
    p->data = val;
    p->next = NULL;
    return p;
}

linklist *initlinklist(){   //链表初始化
    linklist *l = (linklist *)malloc(sizeof(linklist)); //为链表l开辟空间
    l->head.next = NULL;            //l的头指针的下一个为空
    l->tail = &(l->head);           //l的尾指针指向l的头
    return l;
}

int emptylinklist(linklist *l){ //链表判空
    return l->head.next == NULL;
}

int frontlinklist(linklist *l){ //返回链表首元素的数据
    if(emptylinklist(l)) return 0;
    return l->head.next->data;
}

int insertTail(linklist *l, int val){ //在尾部插入节点
    Node *node = getNewNode(val);     //给数val封装起来
    l->tail->next = node;             //在尾部接上新节点
    l->tail = node;                   //尾指针指向新的尾部
    return 1;
}

int eraseHead(linklist *l){ //头部结点删除
    if(emptylinklist(l)) return 0;
    Node *p = l->head.next;     //结点p暂存l首结点的地址
    l->head.next = l->head.next->next; //head指向第二个结点
    if( p == l->tail) l->tail = &(l->head); //如果head.next 和 tail 在一块了---》只有一个节点了
    free(p);
    return 1;
}

void clearlinklist(linklist *l){ //清空链表,链表里有结点空间和链表空间；先清空结点再清空链表
    Node *p = l->head.next, *q;  //q暂存p的下一个结点
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
    free(l);
    return;
}

/* 队列的准备 */
typedef struct Queue{
    linklist *l;    //数据存储区
    int count;  //为了避免假溢出问题
}Queue;

Queue *initQueue(){ //初始化队列
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->l = initlinklist();
    q->count = 0;
    return q;
}

int emptyQueue(Queue *q){   //队列判空
    return q->count == 0;
}

int frontQueue(Queue *q){   //查看队列首元素
    if(emptyQueue(q)) return 0;
    return frontlinklist(q->l);
}

int pushQueue(Queue *q, int val){ //入队
    insertTail(q->l, val);
    q->count += 1;
    return 1;
}

int popQueue(Queue *q){ //出队
    eraseHead(q->l);
    q->count -= 1;
    return 1;
}

void clearQueue(Queue *q){ //清空队列
    if(q == NULL) return;
    clearlinklist(q->l);
    free(q);
    return ;
}

void outputQueue(Queue *q)
{
    printf("Queue : ");
    Node *p = q->l->head.next;
    for (int i = 0; i < q->count; i++, p = p->next)
    {
        printf("%4d", p->data);
    }
    printf("\n\n");
    return;
}

int main(void)
{
    srand(time(0));
#define MAX_OP 10
    Queue *q = initQueue();
    for (int i = 0; i < MAX_OP; i++)
    {
        int OP = rand() % 5, val = rand() % 100;
        if (q->count == 0)
            OP = 4; // 如果队列为空，元素为插入
        switch (OP)
        {
        case 0:
        case 1:
            printf("front of queue : %d\n", frontQueue(q));
            popQueue(q);
            break;
        case 2:
        case 3:
        case 4:
            printf("push %d to queue\n", val);
            pushQueue(q, val);
            break;
        }
        outputQueue(q);
    }
    clearQueue(q);
    return 0;
}