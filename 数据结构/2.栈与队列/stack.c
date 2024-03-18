#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//栈的结构定义
typedef struct Stack{
    int *data;  //数据域
    int size, top;  //空间大小， 和栈顶指针
}Stack;
//初始化栈
Stack* initStack(int n){
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * n);
    s->size = n;
    s->top = -1;    //空栈
    return s;
}
//判空
int emptyStack(Stack * s){
    return s->top == -1;
}
//判满
int fullStack(Stack *s){
    return s->top +1 == s->size;
}
//查看栈顶元素
int topStack(Stack *s){
    if(emptyStack(s)) return 0;
    return s->data[s->top];
}
//入栈
int push(Stack *s, int val){
    if(s->top + 1 == s->size) return 0; //栈满
    s->top += 1;
    s->data[s->top] = val;
    return 1;
}
//出栈
int pop(Stack *s){
    if(emptyStack(s)) return 0;
    s->top -= 1;
    return 1;
}
//清空栈
void clearStack(Stack *s){
    if(s == NULL) return;
    free(s->data);
    free(s);
    return;
}
//输出栈元素
void outputStack(Stack *s){
    printf("Stack : ");
    for (int i = s->top; i >= 0; i--)
    {
        printf("%4d",s->data[i]);
    }
    printf("\n\n");
    return;
}

int main(void){
    srand(time(0));
    #define MAX_OP 10
    Stack *s = initStack(5);
    for (int i = 0; i < MAX_OP; i++)
    {
        if(fullStack(s)) return 0; //栈满结束循环
        int op = rand() % 3 , val = rand() % 100;
        if(emptyStack(s)) op = 2;
        switch (op)
        {
        case 0:
            printf("pop stack, item = %d\n", topStack(s));
            pop(s);
            break;
        case 1:
        case 2:
            printf("push stack, item = %d\n", val);
            push(s, val);
            break;
        }
        outputStack(s);
    }
    clearStack(s);
    return 0;
}