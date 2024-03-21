/*
    广义表序列化二叉树
    反广义表序列化
    A(,B(C,D))
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define KEY(n) (n ? n->key : -1) //n是否存在啊，存在的话返回n->key 不存在就返回-1
#define MAX_NODE 10

/* 生成二叉树 */
typedef struct Node{
    int key;
    struct Node *lchild, *rchild;
}Node;
Node *getNewNode(int key){
    Node *n = (Node *)malloc(sizeof(Node));
    n->key = key;
    n->lchild = n->rchild = NULL;
    return n;
}
Node *insert(Node *root, int key){
    if(root == NULL) return root = getNewNode(key);
    if(rand() % 2) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    return root;
}
Node *getRandomBinaryTree(int n){
    Node *root = NULL;
    for (int i = 0; i < n; i++)
    {
        root = insert(root, rand() % 100);
    }
    return root;
}
void clear(Node *root){
    if(root == NULL) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return;
}
void print(Node *node)
{
    printf("%d(%d,%d)\n", KEY(node),
           KEY(node->lchild),
           KEY(node->rchild));
    return;
}
void output(Node *root)
{
    if (root == NULL)
        return;
    print(root);
    output(root->lchild);
    output(root->rchild);
    return;
}
/* 二叉树->广义表 */
char buff[1000]; //存储字符串的数组
int len = 0;    //广义表的长度

void __serialize(Node *root){   //根 左 右类似于前序遍历
    if (root == NULL) return;
    // C 库函数 int snprintf(char *str, size_t size, const char *format, ...)
    // 设将可变参数(...)按照 format 格式化成字符串，
    // 并将字符串复制到 str 中，size 为要写入的字符的最大数目，超过 size 会被截断，最多写入 size-1 个字符。
    len += snprintf(buff + len, 100,"%d", root->key);   //开始传入的为根节点的值
    if(root->lchild == NULL && root->rchild == NULL) return ;   //根节点无孩子节点返回函数
    len += snprintf(buff + len , 100, "(");
    __serialize(root->lchild);                                  //序列化左孩子
    if(root->rchild){
        len += snprintf(buff + len , 100, ",");
        __serialize(root->rchild);                              //序列化右孩子
    }
    len += snprintf(buff + len , 100, ")");
    return ;
}
//
void serialize(Node *root){
    memset(buff, 0, sizeof(buff));
    // C 库函数 void *memset(void *str, int c, size_t n)
    //复制字符 c（一个无符号字符）到参数 str 所指向的字符串的前 n 个字符。
    len = 0;
    __serialize(root);
    return ;
}

/* 逆序列化 */
Node *deserialize(char *buff, int n){   //插入一个长为n的字符串数组
    Node **s = (Node **)malloc(sizeof(Node *) * MAX_NODE);  //s保存的是Node*类型的变量
    int top = -1, flag = 0 , scode = 0; // top栈顶指针；flag=0左孩子=1右孩子；scode是状态
    //1遇到关键字->生成新的节点
    //2遇到"("->将刚生成的新节点压入栈
    //3遇到","->标记当前处理的为右子树
    //4遇到")"->将栈顶结点出栈
    //5每生成新节点->根据flag设置左右子树
    Node *p = NULL, *root = NULL; //p永远是指向最后生成的结点，root最后被出栈的结点
    for(int i = 0; buff[i]; i++){
        switch(scode){
            case 0:{
                if (buff[i] >= '0' && buff[i] <= '9') scode = 1;
                else if (buff[i] == '(') scode = 2;
                else if (buff[i] == ',') scode = 3;
                else scode = 4;
                i -= 1;
            }break;
            case 1:{
                int key = 0;
                while(buff[i] <='9' && buff[i] >= '0'){
                    key = key * 10 + (buff[i] - '0');
                    i += 1;
                }
                p = getNewNode(key);    //生成新结点
                if(top >= 0 && flag == 0) s[top]->lchild = p;   //栈顶指针的左/右孩子是新节点p
                if(top >= 0 && flag == 1) s[top]->rchild = p;
                i -= 1;
                scode = 0;
            }break;
            case 2:{
                s[++top] = p;   //遇到'(' p压入栈中
                flag = 0;       //左
                scode = 0;
            }break;
            case 3:{
                flag = 1;       //右
                scode = 0;
            }break;
            case 4:{
                root = s[top];  //出栈
                top -= 1;
                scode = 0;
            }break;
        }
    }
    return root;
}


int main(void) {
    srand(time(0));
    Node *root = getRandomBinaryTree(MAX_NODE);
    serialize(root);
    output(root);
    printf("Buff[] : %s\n", buff);
    Node *new_root = deserialize(buff,len);
    output(new_root);
    return 0;
}