#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 顺序表的结构定义+结构操作 */
typedef struct squlist
{
    int size;
    int *data;
} squlist;
// 初始化
squlist *init_squlist(int n)
{
    squlist *s = (squlist *)malloc(sizeof(squlist));
    s->size = n;
    s->data = (int *)malloc(sizeof(int) * n);
    return s;
}
// 清空顺序表
void clearsqulist(squlist *s)
{
    if (s == NULL)
        return;
    free(s->data);
    free(s);
    return;
}
// 寻找元素
int squlistSeek(squlist *s, int pos)
{
    if (pos < 0 || pos >= s->size)
        return -1;
    return s->data[pos];
}
// 插入顺序表
int insertsqulist(squlist *s, int pos, int val)
{
    if (pos < 0 || pos >= s->size)
        return -1;
    s->data[pos] = val;
    return 1;
}

/* 队列结构定义+结构操作 */
typedef struct Queue
{
    squlist *data;               // 队列的连续存储空间
    int size, head, tail, count; // 队列的空间总大小size,头/尾指针,为了解决假溢出问题添加的计数元素count
} Queue;
// 初始化队列
Queue *init_Queue(int n)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = init_squlist(n); // 队列的数据域初始化为顺序表
    q->size = n;
    q->head = q->tail = q->count = 0; // 空队列
    return q;
}
// 判断队列是否为空
int empty(Queue *q)
{
        return q->count == 0;
}
// 查看队首元素
int front(Queue *q)
{
    return squlistSeek(q->data, q->head);
}
// 元素入队
int push(Queue *q, int val)
{
    if (q->count == q->size)
        return 0; // 队满
    insertsqulist(q->data, q->tail, val);
    q->tail += 1;
    if (q->tail == q->size)
        q->tail = 0; // 如果尾指针到了队列的末尾，置0解决假溢出
    q->count += 1;
    return 1;
}
// 元素出队
int pop(Queue *q)
{
    if (empty(q))
        return 0;
    q->head += 1;
    if (q->head == q->size)
        q->head = 0; // 如果头指针到了队列的末尾，置0解决假溢出
    q->count -= 1;
    return 1;
}
// 清空队列
void clearQueue(Queue *q)
{
    if (q == NULL)
        return;
    clearsqulist(q->data);
    free(q);
    return;
}
// 输出队列
void outputQueue(Queue *q)
{
    printf("Queue : ");
    for (int i = 0; i < q->count; i++)
    {
        printf("%4d", squlistSeek(q->data, (q->head + i) % q->size));
    }
    printf("\n\n");
    return;
}

int main(void)
{
    srand(time(0));
    #define MAX_OP 10
    Queue *q = init_Queue(5);
    for (int i = 0; i < MAX_OP; i++)
    {
        int OP = rand() % 5, val = rand() % 100;
        if(q->count == 0) OP = 4;   //如果队列为空，元素为插入
        switch (OP)
        {
        case 0:
        case 1:
        case 2:
            printf("front of queue : %d\n", front(q));
            pop(q);
            break;
        case 3:
        case 4:
            printf("push %d to queue\n", val);
            push(q, val);
            break;
        }
        outputQueue(q);
    }
    clearQueue(q);
    return 0;
}