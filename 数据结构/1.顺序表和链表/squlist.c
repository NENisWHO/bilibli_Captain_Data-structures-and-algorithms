#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//顺序表结构定义
typedef struct squlist{
    int size;   // 顺序表能存储的最大数据元素个数
    int count;  // 顺序表存目前储的数据元素个数
    int *data;  // 指针指向顺序表连续的存储区
}squlist;

//0.顺序表初始化
squlist *getNewsqulist(int val){
    squlist *q = (squlist *)malloc(sizeof(squlist)); // 为结构体指针开辟一个squlist的空间
    q->size = val;                                   // 顺序表能存储的最大数据元素个数为size个
    q->count = 0;                                    // 顺序表目前存储的数据元素个数为0
    q->data = (int *)malloc(sizeof(int) * val);      // 为v的data指针开辟一个size大小的空间用来存储数据元素
    return q;
}

//3.空间扩容
int expend_size(squlist *q){
    if(q == NULL)
        return 0; // 如果顺序表不存在返回0
    printf("expand q from %d to %d\n", q->size, 2 * q->size);

    int *p = (int *)realloc(q->data, sizeof(int)*2*q->size);
    // 定义一个新指针p让他从v->data的地址开始申请一个sizeof(int)*2*v->size的空间

    if(p == NULL)
        return 0; // 让v的data指针指向新的空间p
    q->data = p ;
    q->size = 2 * q->size; // 结构操作：维护数据结构
    return 1;
}
//2.插入数据元素
int insert(squlist *q,int pos,int val){
    // 在pos位置添加val数据元素
    if(pos < 0 || pos > q->count)
        return 0; // 先进行位置检查，查看插入位置是否合法；
                  // pos = v->count时，是在最后一个元素的下一位置(当count!=size时)
    if(q->size == q->count && !expend_size(q)) return 0;
    for (int i = q->count - 1; i >= pos; i--) // count对应个数，pos对应数组下标；要统一两个量的意义
    {
        q->data[i + 1] = q->data[i]; // 逆序遍历，集体向后移动一个位置
    }
    q->data[pos] = val;
    q->count += 1;
    return 1;
}

//4.删除元素
int erase_eml(squlist *q,int pos){
    // 前序遍历，集体向前移动一个位置
    // count对应个数，pos对应数组下标；要统一两个量的意义。此处i = pos+1避免超出容量的元素赋值给data。
    if (pos < 0 || pos >= q->count) return 0;
    if(q->count == 0) return 0;
    for (int i = pos + 1; i < q->count; i++)
    {
        q->data[i - 1] = q->data[i];
    }
    q->count -= 1;
    return 1;
}

//5.输出顺序表
void output_squlist(squlist *q){
    int len = 0;
    for (int i = 0; i < q->size; i++)
    {
        len += printf("%3d", i);
    }
    printf("\n");
    for (int i = 0; i < len; i++)
    {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < q->count; i++)
    {
        printf("%3d", q->data[i]);
    }
    printf("\n\n\n");
    return ;
}

//1.销毁顺序表
void destroy(squlist *q){
    if(q == NULL)
        return; // 如果顺序表不存在就返回
    free(q->data); // 先释放v中指针data的空间
    free(q);       // 再释放v的空间
    return;
}

int main(void){
    srand(time(0));
    #define MAX_OP 10
    squlist *q = getNewsqulist(2);
    for (int i = 0; i < MAX_OP; i++)
    {
        int op = rand() % 4, val, pos, ret;
        switch (op)
        {
        case 0:
        case 1:
        case 2:
            val = rand() % 100;
            pos = rand() % (q->count + 2);
            ret = insert(q, pos, val);
            printf("insert %d at %d to suqulist = %d\n", val, pos, ret);
            break;
        case 3:
            pos = rand() % (q->count + 2);
            ret = erase_eml(q, pos);
            printf("erase items at %d in suqulist = %d\n", pos, ret);
            break;
        }
        output_squlist(q);
    }
    destroy(q);
    return 0;
}