/*矩阵加法

实现三元组表示的两个稀疏矩阵的加法。相关定义如下：

#define MAXSIZE 100          //假设非零元个数的最大值为100
typedef struct {
    int i,j;									//非零元的行下标和列下标，i 和 j 从 1 开始计数，与数学中矩阵元素的编号一致
    ElemType e;						//非零元的值
}Triple;

typedef struct {
    Triple data[MAXSIZE];			// 非零元三元组表
    int    m, n, len;							// 矩阵的行数、列数和非零元个数
}TSMatrix;
在三元组中，i 和 j 从 1 开始计数，与数学中矩阵元素的编号一致
矩阵加法函数的原型为：

bool add_matrix(const TSMatrix *pM, const TSMatrix *pN, TSMatrix *pQ);
pM, pN, pQ 分别指向三个矩阵，当 pM 和 pN 两个矩阵不可加时，函数返回 false，否则函数返回 true，且 pQ 指向两个矩阵的和。*/
#include <stdio.h>
#include <stdlib.h>
#include "tsmatrix.h"
//思路短浅了，不能只考虑相同位置都是非零元的问题，还得考虑位置分别有零元和非零元的问题。


bool add_matrix(const TSMatrix *pM, const TSMatrix *pN, TSMatrix *pQ)
{
   if (pM->m!=pN->m||pM->n!=pN->n)
   {
    return false;
   }
   pQ->m=pM->m;
   pQ->n=pN->n;

   int Qdata_pos=0;//代表pQ矩阵的非零元个数；
   int m=0;//扫描pM的个数
   int n=0;//扫描pN的个数
   int p=0;

   for (m  = 0; m < pM->len; m++)
   {
    pQ->data[Qdata_pos].e=pM->data[m].e;
    pQ->data[Qdata_pos].i=pM->data[m].i;
    pQ->data[Qdata_pos].j=pM->data[m].j;
    Qdata_pos++;
   }//把整个Pm复制在pQ中
   int NQdata_pos=0;//

   for (p = 0; p < pN->MAXSIZE; p++)
   {
    for(n=0;n<pN->len;n++)
    {
        if(pQ->data[p].i==pN->data[n].i&&pQ->data[p].j==pN->data[n].j)
        {
            pQ->data[p].e=pQ->data[p].e+pN->data[n].e;
        }
        else
        {   
            Qdata_pos=Qdata_pos+1;
            pQ->data[Qdata_pos].e=pN->data[n].e;
            pQ->data[Qdata_pos].i=pN->data[n].i;
            pQ->data[Qdata_pos].j=pN->data[n].j;
        }
    }
   }
    for (int q = 0; q <= pQ->Qdata_pos;q++) 
    {
        if (pQ->data[q].e == 0) 
        {
            for (int i = q; i <Qdata_pos; i++) 
            {
                pQ->data[i] = pQ->data[i + 1];
            }
            q--;
            Qdata_pos--;
        }
    }
    Pq->len=Qdata_pos;
    return true;  
}

