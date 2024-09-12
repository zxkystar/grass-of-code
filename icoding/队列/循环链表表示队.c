/*队列 循环链表表示队列

假设以带头结点的循环链表表示队列，并且只设一个指针指向队尾元素结点（注意不设头指针），请完成下列任务：


1: 队列初始化，成功返回真，否则返回假： bool init_queue(LinkQueue *LQ);

2: 入队列，成功返回真，否则返回假： bool enter_queue(LinkQueue *LQ, ElemType x);

3: 出队列，成功返回真，且*x为出队的值，否则返回假 bool leave_queue(LinkQueue *LQ, ElemType *x);

相关定义如下：

typedef struct _QueueNode {
    ElemType data;          // 数据域
    struct _QueueNode *next;      // 指针域
}LinkQueueNode, *LinkQueue;*/
#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过

bool init_queue(LinkQueue *LQ)
{
	*LQ=(LinkQueue)malloc(sizeof(LinkQueueNode));
    if(*LQ==NULL)
    {
        return false;
    }
    (LQ*)->next=*LQ;//头指针的结点指向自己，表示空结点
    return true;
}

bool enter_queue(LinkQueue *LQ, ElemType x)
{
	LinkQueueNode *newNode=(LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    if(newNode==NULL)
    {
        return false;
    }
    newNode->data=x;
    newNode->next=(*LQ)->next;
    (*LQ)->next=newNode;
    return true;
}

bool leave_queue(LinkQueue *LQ, ElemType *x) {
    if ((*LQ)->next == *LQ) {  // 队列为空
        return false;
    }
    LinkQueueNode *firstNode = (*LQ)->next->next;  // 第一个结点
    *x = firstNode->data;                          // 获取第一个结点的值
    (*LQ)->next->next = firstNode->next;           // 头结点的next指针指向第二个结点
    if (firstNode == *LQ) {                        // 如果出队列的是最后一个结点
        *LQ = (*LQ)->next;                          // 队尾指针指向头结点
    }
    free(firstNode);                               // 释放第一个结点的内存
    return true;
}
