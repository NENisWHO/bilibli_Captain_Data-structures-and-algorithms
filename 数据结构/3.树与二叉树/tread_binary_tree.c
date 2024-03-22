
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 二叉树 */
//结构定义
typedef struct Node{
    int key;
    int ltag, rtag;  //结点的左右孩子指针不空为0，空为1；；也就是说是线索为1，是实际的边为0
    struct Node *lchild, *rchild;
}Node;
//初始化
Node *getNewNode(int key){
    Node *n = (Node *)malloc(sizeof(Node));
    n->key = key;
    n->ltag = n->rtag = 0;      //初始化假设为实际的边
    n->lchild = n->rchild = NULL;
    return n;
}
//插入
Node *insert(Node *root, int key){
    if(root == NULL) return getNewNode(key);
    if( rand() % 2) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    return root;
}
//清空
void clear(Node *root){
    if(root == NULL) return;
    if(root->ltag == 0) clear(root->lchild);    //是实际的边才清空
    if(root->rtag == 0) clear(root->rchild);
    free(root);
    return;
}
/* 二叉树的三种遍历方式 */
//前序遍历
void preced_order(Node *root){
    if(root == NULL) return;
    //根 左 右
    printf("%d ", root->key);
    if(root->ltag == 0) preced_order(root->lchild);
    if(root->rtag == 0) preced_order(root->rchild);
    return;
}
//中序遍历
void in_order(Node *root){
    if(root == NULL) return;
    //左 根 右
    if (root->ltag == 0) in_order(root->lchild);
    printf("%d ", root->key);
    if (root->rtag == 0) in_order(root->rchild);
    return;
}
//后序遍历
void post_order(Node *root){
    if(root == NULL) return;
    //左 右 根
    if (root->ltag == 0) post_order(root->lchild);
    if (root->ltag == 0) post_order(root->rchild);
    printf("%d ", root->key);
    return ;
}

/* 中序遍历线索化 */
//    前驱节点          中序遍历的第一个节点
Node *pre_Node = NULL, *inorder_root = NULL;
void __build_inorder_thread(Node *root)
{
    if (root == NULL) return;
    // 左 根 右
    if (root->ltag == 0) __build_inorder_thread(root->lchild);
    //
    if (inorder_root == NULL) inorder_root = root;
    if (root->lchild == NULL) { // 当前节点的左孩子指向前驱前驱
        root->lchild = pre_Node;
        root->ltag = 1;
    }
    if (pre_Node && pre_Node->rchild == NULL) { // 前一个节点的右孩子指向后继节点
        pre_Node->rchild = root;
        pre_Node->rtag = 1;
    }
    pre_Node = root;    //将当前节点赋值给前一个节点
    //
    if (root->rtag == 0) __build_inorder_thread(root->rchild);
    return;
}
//解决最后一个节点右孩子无后继的问题
void build_inorder_thread(Node *root) {
    __build_inorder_thread(root);
    pre_Node->rchild = NULL;
    pre_Node->rtag = 1;
    return ;
}
//线索话遍历节点
Node *getNext(Node *root) {
    if(root->rtag == 1) return root->rchild;    //中序遍历最左边的节点一定没有左孩子
    root = root->rchild;
    while(root->ltag == 0 && root->lchild) root = root-> lchild;
    return root;
}

int main(void) {

    srand(time(0));
    Node *root = NULL;
    #define MAX_NODES 10
    for (int i = 0; i < MAX_NODES; i++){
        root = insert(root, rand() % 100);
    }

    preced_order(root);
    printf("\n");
    in_order(root);
    printf(" <- \n");
    post_order(root);
    printf("\n");

    //线索化遍历
    pre_Node = inorder_root = NULL;
    build_inorder_thread(root);
    Node *node = inorder_root;
    while(node){
        printf("%d ",node->key);
        node = getNext(node);
    }
    printf(" <- \n");
    clear(root);
    return 0;
}