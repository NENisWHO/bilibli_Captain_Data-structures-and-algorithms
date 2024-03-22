
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//二叉树结构定义
typedef struct Node{
    int key; // 树存储的关键值
    struct Node* lchild, *rchild; //树结点的左右孩子
}Node;

//二叉树初始化
Node* getNewNode(int key){
    Node *p = (Node*)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}

//二叉树的插入 递归插入
Node* insert(Node *root, int key){
    if(root == NULL) return getNewNode(key); //递归的边界条件，结点为空就生成新的结点
    if(rand() % 2)
    {
        root->lchild = insert(root->lchild, key);
        //含义：左子树指针接受insert函数的返回值
        //递归下去直到左子树结点为空<触碰到了边界条件>那么key封装成新的结点挂在->lchild上
    }
    else
    {
        root->rchild = insert(root->rchild, key);
    }
    return root;
}

//二叉树的销毁 递归销毁
void clear(Node *root){
    if(root == NULL) return;
    clear(root->lchild);    //子无牵挂析构法
    clear(root->rchild);
    free(root);
    return;
}

//广度遍历二叉树--也叫层序遍历
#define MAX_NODE 10
Node *queue[MAX_NODE + 5];  //用数组指针来代表队列吧
int head, tail;             //头指针，尾指针

void bfs(Node *root){
    head = tail = 0;
    if(root == NULL) return;
    queue[tail++] = root; //把根压入队列，tail此时为1，head=0，root在queue[0处
    while(head < tail){
        Node *node = queue[head];   //每循环一次，取队列中head位置的元素
        printf("\nnode: %d\n", node->key);
        if(node->lchild){
            queue[tail++] = node->lchild;
            printf("\t%d->%d (left)\n", node->key, node->lchild->key);
        }
        if(node->rchild){
            queue[tail++] = node->rchild;
            printf("\t%d->%d (right)\n", node->key, node->rchild->key);
        }

        head++;
    }
    return;
}
//深度遍历二叉树
int tot = 0;
void dfs(Node *root){
    if(root == NULL) return;
    int start = 0, end = 0;
    tot += 1;
    start = tot;    //每个结点开始的时间戳
    if(root->lchild) dfs(root->lchild);
    if(root->rchild) dfs(root->rchild);
    tot += 1;
    end = tot;      //每个结点结束的时间戳
    printf("%d : [%d,%d]\n", root->key, start, end);
    return;
}

int main(void){
    srand(time(0));
    Node *root = NULL;
    for (int i = 0; i < MAX_NODE; i++)
    {
        root = insert(root, rand() % 100);
    }
    bfs(root);
    dfs(root);
    return 0;
}