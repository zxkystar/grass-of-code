/*共同祖先
假设二叉树采用二叉链表方式存储， root指向根结点，p所指结点和q所指结点为二叉树中的两个结点，编写一个计算它们的最近的共同祖先，函数定义如下：*/
BiTNode * nearest_ancestor(BiTree root, BiTNode *p, BiTNode *q);
/*其中 root 指向二叉树的根结点，p 和 q 分别指向二叉树中的两个结点。
提示：在完成本题时，可利用 path 函数获取p和q两个结点到根结点之间的路径，之后再计算两条公共路径得出最近的共同祖先。path函数及栈相关定义如下：*/
bool path(BiTNode* root, BiTNode* node, Stack* s);

#define Stack_Size 50
typedef BiTNode* ElemType;
typedef struct{
    ElemType elem[Stack_Size];
    int top;
}Stack;

void init_stack(Stack *S); // 初始化栈
bool push(Stack* S, ElemType x); //x 入栈
bool pop(Stack* S, ElemType *px); //出栈，元素保存到px所指的单元，函数返回true,栈为空时返回 false
bool top(Stack* S, ElemType *px); //获取栈顶元素，将其保存到px所指的单元，函数返回true，栈满时返回 false
bool is_empty(Stack* S);  // 栈为空时返回 true，否则返回 false

#include <stdlib.h>
#include <stdio.h>
#include "bitree.h" //请不要删除，否则检查不通过

//这块就两个问题
//1.关于栈的函数是否都是用取地址的方式传参：个人认为大概率是这样的
//因为栈的存储说白了就是按照位置的关系来一一存储这些东西的
//2.对于path函数，这个函数是通过三个参数，树的根节点，树的某一结点，和一个栈来解决路径问题的
//即把从根节点到该节点的路径用栈存储起来。
BiTNode * nearest_ancestor(BiTree root, BiTNode *p, BiTNode *q)
{
    Stack Sq,Sp;//分别用来存储pq结点的路径
    init_stack(&Sq);
    init_stack(&Sp);
    path(root,p,&Sp);
    path(root q,&Sq);


}


#include <stdlib.h>
#include <stdio.h>
#include "bitree.h" //请不要删除，否则检查不通过


BiTNode * nearest_ancestor(BiTree root, BiTNode *p, BiTNode *q){
    // 分别用栈Sp和Sq记录从根节点到节点p和q的路径
    Stack Sp, Sq;
    init_stack(&Sp);
    init_stack(&Sq);
    path(root, p, &Sp);
    path(root, q, &Sq);

    // 由于公共祖先一定在同一层，所以先让两个栈的栈顶在同一层
    while (Sp.top != Sq.top) {
        if (Sq.top > Sp.top) {
            Sq.top--;
        }
        else {
            Sp.top--;
        }
    }//没看懂这一步是干嘛的，但是其他的思路大体上是弄明白了

    // 依次弹出栈顶元素进行比较，找到最近公共祖先
    while (!is_empty(&Sq)) {
        BiTNode* pop_q = NULL;
        pop(&Sq, &pop_q);
        BiTNode* pop_p = NULL;
        pop(&Sp, &pop_p);
        if (pop_p == pop_q) {
            // 如果栈顶元素相等，则说明找到了最近公共祖先
            return pop_q;
        }
    }    
    // 如果没有找到最近公共祖先，则返回NULL
    return NULL;
}
