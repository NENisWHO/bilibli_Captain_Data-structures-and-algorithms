#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 准备二叉树 */
typedef struct Node{
    char ch;
    int freq;
    struct Node* lchild, *rchild;
}Node;
Node *getNewNode(int freq, char ch){
    Node *node = (Node*) malloc(sizeof(Node));
    node->freq = freq;
    node->ch = ch;
    node->lchild = node->rchild = NULL;
    return node;
}
void clear(Node *root){
    if(root == NULL) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return;
}
/* 二叉树变为haffman二叉树 */
//交换节点
void swap_node(Node **node_arr, int min, int j){
    Node *temp = node_arr[min];
    node_arr[min] = node_arr[j];    //最小位置换到j位置上
    node_arr[j] = temp;
}
//找到freq低的节点
int find_min_node(Node **node_arr, int n){
    int ind = 0;
    for (int i = 1; i <= n; i++)
    {
        if(node_arr[ind]->freq > node_arr[i]->freq) ind = i;
    }
    return ind;
}
//建立haffman树 函数参数：一个存储二叉树节点的数组node_arr，经过n-1轮合并的n
Node *buildHaffmanTree(Node **node_arr, int n){
    for (int i = 1; i < n; i++)
    {
        //find tow minfreq nodes 找到两个出现频率低的结点
        int ind1 = find_min_node(node_arr, n-i);//freq最小的节点换到数组最后的下标位置
        swap_node(node_arr, ind1, n-i);
        int ind2 = find_min_node(node_arr, n-i-1);
        swap_node(node_arr, ind2, n-i-1);
        //merge two minfreq nodes 合并两个出现频率低的节点为新节点并传入node_arr数组中
        int new_freq = node_arr[n-i]->freq + node_arr[n-i-1]->freq;
        Node *node = getNewNode(new_freq, 0);
        node->lchild = node_arr[n-i-1];
        node->rchild = node_arr[n-i];
        node_arr[n-i-1] = node; //将新节点放到数组node_arr的n-i-1的位置上
    }
    return node_arr[0];
}

//提取haffman树的编码信息
#define MAX_CHAR_NUM 128
char *char_code[MAX_CHAR_NUM] = {0};
void extractHaffmanCode(Node *root, char buff[], int k){
    buff[k] = 0;
    if(root->lchild == NULL && root->rchild == NULL){
        char_code[root->ch] = strdup(buff);
        //printf("%c : %s\n",root->ch, buff);
        return ;
    }
    buff[k] = '0';
    extractHaffmanCode(root->lchild, buff, k+1);
    buff[k] = '1';
    extractHaffmanCode(root->rchild, buff, k+1);
    return ;
}

int main(void)
{
    char s[0]; //可存10个char字符
    int n, freq;
    scanf("%d", &n);
    Node **node_arr = (Node **)malloc(n*sizeof(Node *));
    for (int i = 0; i < n; i++)
    {
        scanf("%s%d", s, &freq);
        node_arr[i] = getNewNode(freq, s[0]);
    }
    Node *root = buildHaffmanTree(node_arr, n);

    char buff[1000];
    extractHaffmanCode(root, buff, 0);
    for (int i = 0; i < MAX_CHAR_NUM; i++)
    {
        if(char_code[i] == NULL) continue;
        printf("%c : %s\n", i, char_code[i]);//这里强行将int i 转换成char ASCII编码
    }
    clear(root);
    return 0;
}

//测试文件text.txt
/*
    右侧的freq小于左侧的 这是由函数buildHaffmanTree决定的
              mage3              100
             /     \
           mage2    a            50 50
          /     \
        mage1    b               30 20
        /  \
       d    c                    20 10
*/