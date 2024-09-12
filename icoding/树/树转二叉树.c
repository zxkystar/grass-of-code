/*树转二叉树

使用队列，编写transfrom函数，将普通树转换成对应的二叉树。二叉树的相关定义如下：

typedef int DataType;

typedef struct Node{
    DataType data;
    struct Node* left;
    struct Node* right;
}BiTNode, *BiTree;
普通树节点的定义如下：

#define MAX_CHILDREN_NUM 5
struct _CSNode
{
    DataType data;
    struct _CSNode *children[MAX_CHILDREN_NUM];
};
typedef struct _CSNode CSNode;
其中，子树的根节点的指针存放在children数组的前k个元素中，即如果children[i]的值为NULL，而children[i-1]不为NULL，则表明该结点只有i棵子树，子树根结点分别保存在children[0]至children[i-1]中。

队列相关定义及操作如下：

struct __Queue
{
    int i, j; //指向数组内元素的游标
    void **array;
};
typedef struct __Queue Queue;

Queue* create_queue(); //创建队列
bool is_empty_queue(Queue *tree); //队为空返回true,不为空时返回false
void* del_queue(Queue *tree); //结点指针出队
void add_queue(Queue *tree, void *node); //结点指针入队
void free_queue(Queue *tree); //释放队列
transform函数定义如下：

BiTNode* transform(CSNode *root);
其中 root 为普通树的根结点，函数返回该树对应二叉树的根结点。*/
typedef int DataType;

typedef struct Node{
    DataType data;
    struct Node* left;
    struct Node* right;
}BiTNode, *BiTree;

#define MAX_CHILDREN_NUM 5
struct _CSNode
{
    DataType data;
    struct _CSNode *children[MAX_CHILDREN_NUM];
};
typedef struct _CSNode CSNode;

struct __Queue
{
    int i, j; //指向数组内元素的游标
    void **array;
};
typedef struct __Queue Queue;

Queue* create_queue(); //创建队列
bool is_empty_queue(Queue *tree); //队为空返回true,不为空时返回false
void* del_queue(Queue *tree); //结点指针出队
void add_queue(Queue *tree, void *node); //结点指针入队
void free_queue(Queue *tree); //释放队列

#include <stdlib.h>
#include <stdio.h>
#include "bitree.h" //请不要删除，否则检查不通过


BiTNode* transform(CSNode *root)
{
    if (root==NULL)
    {
        return NULL;
    }
    BiTNode* H=(BiTNode*)malloc(sizeof(BiTNode));//创建一个二叉树节点
    if (H==NULL)
    {
        return NULL;
    }
    H->data=root->data;
    H->left=NULL;
    H->right=NULL;
    Queue * Q=create_queue();
    add_queue(Q,root);
    add_queue(Q,H);
    
    //将二叉树结点和根节点入栈，然后开始遍历树节点然后转换成二叉树结点
    while (!is_empty_queue(Q))//这个条件很重要，
    {
        //依次取出树中的树节点和二叉树结点
        CSNode* TreeNode=(CSNode*)del_queue(Q);//注意队列是先进先出的类型，所以上面的入队顺序很重要
        BiTNode* BNode=(BiTNode*)del_queue(Q);
        BiTNode *pre=NULL;//辅助
        for (int i = 0; TreeNode->children[i]!=NULL; i++)
        {
            BiTNode *New =(BiTNode*)malloc(sizeof(BiTNode));
            if (New==NULL)
            {
                exit(0);
            }//每次申请空间之后都要记得检查
            
            New->data=TreeNode->children[i]->data;
            New->left=NULL;
            New->right=NULL;

            if (i==0)//第一个结点作为二叉树的左孩子
            {
                BNode->left=New;
                pre=New
            }
            else
            {
                pre->right=New;
                pre=New;
            }
            //完成一次操作之后要记得将两个结点按顺序加入到队列之中好完成遍历
            add_queue(Q,TreeNode->children[i]);
            add_queue(Q,New);
        }
         
    }

    //释放队列空间   
    free(Q->array);
    free(Q);
    // 返回转换后的二叉树
    return H;
}