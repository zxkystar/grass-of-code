/*顺序表 删除重复

编写算法，在一非递减的顺序表L中，删除所有值相等的多余元素。要求时间复杂度为O(n)，空间复杂度为O(1)。

函数原型如下：
void del_dupnum(SeqList *L)

相关定义如下：
struct _seqlist{
    ElemType elem[MAXSIZE];
    int last;
};
typedef struct _seqlist SeqList;*/
//这个题有拓展，就是他的重复元素是相邻的（顺序表）
//但是如果考虑一个无序的线性表，目前我还想不到一个时间复杂度为O1的算法
#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过

void del_dupnum(SeqList *L) {
    int prev = -1;  // 前指针
    int curr = 0;  // 当前指针

    while (curr <= L->last) {
        if (L->elem[prev] == L->elem[curr]) {
            curr++;  // 删除重复元素
        } else {
            prev++;
            L->elem[prev] = L->elem[curr];
            curr++;
        }
    }

    L->last = prev;  // 更新顺序表长度
}
