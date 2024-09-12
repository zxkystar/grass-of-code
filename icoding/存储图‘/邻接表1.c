/*邻接表2

试在邻接表存储结构上实现图的基本操作 del_vertex，相关定义如下：

typedef int VertexType;

typedef enum{
    DG, UDG
}GraphType;

typedef struct ArcNode{
    int adjvex;
    InfoPtr *info;
    struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode{
    VertexType data;
    ArcNode *firstarc;
}VNode;
typedef struct{
    VNode vertex[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphType type;
}ListGraph;

int locate_vertex(ListGraph *G, VertexType v); //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool del_vertex(ListGraph *G, VertexType v); //删除顶点 v
当成功删除顶点或边时，函数返回true，否则（如顶点或边不存在、删除边时顶点v或w不存在）返回false。*/

#include <stdio.h>
#include "graph.h" //请勿删除，否则检查不通过


bool del_vertex(ListGraph *G, VertexType v){
  int v1=locate_vertex(G, v);
  if(v1==-1)
  {
      return false;
  }
  ArcNode* p1=G->vertex[v1].firstarc;
  while(p1!=NULL)
  {
      ArcNode*tem=p1;
      G->vertex[v1].firstarc=p1->nextarc;
      p1=p1->nextarc;
      free(temp);
      G->arcnum__;
  }
  for(i=v1;i<G->vexnum;i++)
  {
      G->vertex[i]=G->vertex[i+1];
  }
  G->vexnum--;
  ArcNode*p;
  for(int i=0;i<G->vexnum;i++)
  {
      p=G->vertex[i].firstarc;
      while(p!=NULL)
      {
          if(p->adjvex>v1)
          {
              p->adjvex--;
              p=p->nextarc;
          }
          else if(p->adjvex==v1)
          {
              if(G->vertex[i].firstarc==p)
              {
                  ArcNode*temp=p;
                  G->vertex[i].firstarc=p->nextarc;
                  p=p->nextarc;
                  free(temp);
              }
              else
              {
                  ArcNode* pre=G->vertex[i].firstarc;
                  while(pre->nextarc!=p)
                  {
                      pre=pre->nextarc;
                   }
                  ArcNode*temp=p;
                  pre->nextarc=p->nextarc;
                  p=p->nextarc;
                  free(temp);
               }
           G->arcnum--;
          }
          else
          {
              p=p->nextarc;
          }
      }
  
  }

    return ture;
}