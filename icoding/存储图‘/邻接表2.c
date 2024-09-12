
typedef int VertexType;

typedef enum{
    DG, UDG
}GraphType;

typedef struct ArcNode
{
    int adjvex;
    InfoPtr *info;
    struct ArcNode *nextarc;

}ArcNode;

typedef struct VNode
{
    VertexType data;
    ArcNode *firstarc;
}VNode;
typedef struct
{
    VNode vertex[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphType type;
}ListGraph;

/*试在邻接表存储结构上实现图的基本操作 insert_vertex 和 insert_arc，相关定义如下：
int locate_vertex(ListGraph* G, VertexType v); //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool insert_vertex(ListGraph *G, VertexType v);
bool insert_arc(ListGraph *G, VertexType v, VertexType w);
当成功插入顶点或边时，函数返回true，否则（如顶点或边已存在、插入边时顶点v或w不存在）返回false。*/
#include <stdio.h>
#include "graph.h" //请勿删除，否则检查不通过

bool insert_vertex(ListGraph *G, VertexType v)
{
   int v1=locate_vertex(G,v);
   if(v1!=-1)
   {
    return false;
   }
   G->vexnum++;
   G->vertex[G->vexnum-1].data=v;
   G->vertex[G->vexnum-1].firstarc=NULL;
   return true;
}


bool insert_arc(ListGraph *G, VertexType v, VertexType w)
{
  int v1=locate_vertex(G,v);
  int v2=locate_vertex(G,w);
  if(v1==-1||v2==-1)
  {
    return false;
  }
  ArcNode*p=G->vertex[v1].firstarc;
  ArcNode*pre=G->vertex[v1].firstarc;
  while(p!=NULL)//该循环过后pre为vertex[]中的最后以个边结点
  {
    pre=p;
    if(p->adjvex==v2)
    {
       return false;
    }
    p=p->nextarc;
  }
  ArcNode*New=(ArcNode*)malloc(sizeof(ArcNode));
  if(New==NULL)
  {
    return false;
  }
  New->adjvex=v2;
  New->nextarc=NULL;
  if(pre==NULL)
  {
    G->vertex[v1].firstarc=New;
  }
  else
  {
    pre->nextarc=New;
  }
  if(G->type==UDG)
  {
    ArcNode*pre1=G->vertex[v2].firstarc;
    ArcNode*p1=G->vertex[v2].firstarc;
    while(p!=NULL)
    {
        pre=p;
        if(p->adjvex==v1)
        {
            return false;
        }
        p=p->nextarc;
    }
    ArcNode *New1=(ArcNode*)malloc(sizeof(ArcNode));
    if(New1==NULL)
    {
        return false;
    }
    New1->adjvex=v1;
    New1->nextarc=NULL;
    if(pre1==NULL)
    {
      G->vertex[v2].firstarc=New1;
    }
    else
    {
        pre1->nextarc=New1;
    }
   }
   G->arcnum++;
   return true;
}
