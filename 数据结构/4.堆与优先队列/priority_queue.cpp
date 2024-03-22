/*
    优先队列 -- 完全二叉树 -- 堆
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define cmp >
#define ROOT 1
#define FATHRE(i) ((i) / 2)
#define LEFT(i) ((i) * 2)
#define RIGHT(i) ((i) * 2 + 1)
#define swap(a,b) { \
    printf("swap(%d, %d)\n", a, b); \
    __typeof(a) __c = (a); \
    (a) = (b); \
    (b) = __c; \
}

//结构定义
typedef struct priorityQueue {
    int *__data, *data; //__data是队列存储数据的空间；data是为了优化代码设置的：F = i，L = 2*i，R=2*i+；
    int size, n;        //优先队列的总空间大小size，现在存储的数据个数n
}priorityQueue;

//初始化优先队列
priorityQueue *initpriorityQueue(int size) {
    priorityQueue *p = (priorityQueue *)malloc(sizeof(priorityQueue));
    p->__data = (int *)malloc(sizeof(int)*size);
    p->data = p->__data - ROOT;
    /*
            ()[][][][][]
    __data    0 1 2 3 4
      data  0 1 2 3 4 5
    */
    p->size = size;
    p->n = 0;
    return p;
}
//判空
int empty(priorityQueue *p) {
    return p->n == 0;
}
//判满
int full(priorityQueue *p) {
    return p->n == p->size;
}
//返回队列头元素
int top(priorityQueue *p) {
    return p->data[ROOT];
}

//向上调整  参数：一个指针数组，一个代表着位置的i
void up_update(int *data, int i) {
    printf("\nUP update: %d\n", data[i]);   //向上调整的是i位置的值
    while (i > ROOT && data[i] cmp data[FATHRE(i)] ) //当位置还没到根并且i位置的值大于父亲i位置的值
    {
        swap(data[i], data[FATHRE(i)]);
        i = FATHRE(i);
    }
    printf("\n");
    return;
}
//向下调整  参数：一个指针数组，数组位置i，队列现在的存储的数据的大小n
void down_update(int *data, int i, int n) {
    printf("\nDown update: %d\n", data[i]);
    while(LEFT(i) <= n) {
        int ind = i, l = LEFT(i), r = RIGHT(i); // ind为三元组中最大的值的下标
        if(data[l] cmp data[ind]) ind = l;
        if(r <= n && data[r] cmp data[ind]) ind = r;
        if(ind == i) break;
        swap(data[i], data[ind]);
        i = ind;
    }
    printf("\n");
    return;
}

//插入数据
int push(priorityQueue *p, int x){
    if(full(p)) return 0;
    p->n += 1;
    p->data[p->n] = x;
    up_update(p->data, p->n);   //n位置的数据向上调整
    return 1;
}
//弹出数据
int pop(priorityQueue *p) {
    if(empty(p)) return 0;
    p->data[ROOT] = p->data[p->n];
    p->n -= 1;
    down_update(p->data, ROOT, p->n);
    return 1;
}

//清空队列
void clearQu(priorityQueue *p) {
    if(p == NULL) return;
    free(p->data);
    free(p);
    return;
}

//输出队列
void output(priorityQueue *p) {
    printf("PQ(%d): ", p->n);
    for (int i = 1; i <= p->n; i++)
    {
        printf(" %d ", p->data[i]);
    }
    printf("\n");
    return;
}

int main(void) {
    int op, x;
    #define MAX_OP 10
    priorityQueue *p = initpriorityQueue(MAX_OP);
    while(~scanf("%d", &op)) {
        if(op == 1){
            scanf("%d", &x);
            printf("insert %d to priorityQueue : \n", x);
            push(p, x);
            output(p);
        }else {
            printf("pop : %d\n", top(p));
            pop(p);
            output(p);
        }
        printf("------\n");
    }
    clearQu(p);
    return 0;
}