/*  用图邻接表表示实现的一些基本运算*/

#include<stdio.h>
#define MAXVEX 20
#define NON -1

typedef char VexType;
typedef float AdjType;
typedef int Vertex;

struct EdgeNode;
typedef struct EdgeNode * PEdgeNode;
typedef struct EdgeNode * EdgeList;

struct EdgeNode {
    int endvex;			/* 相邻顶点字段 */
    AdjType weight;		/* 边的权，非带权图可以省略 */
    PEdgeNode nextedge;	/* 链字段 */
};	                    /* 边表中的结点 */

typedef struct {
    VexType vertex;		/* 顶点信息 */
    EdgeList edgelist;	/* 边表头指针 */
} VexNode;               /* 顶点表中的结点 */

typedef struct {
    int n;				/* 图的顶点个数 */
    VexNode vexs[MAXVEX];
} GraphList;

int firstVertex(GraphList* pgraph) {
    return pgraph->n == 0 ? NON : 0;
}

int nextVertex(GraphList* pgraph,int n) {
    return n == pgraph->n-1 ? NON : n+1;
}

int firstAdjacent(GraphList* pgraph, int i) {
    if (pgraph->vexs[i].edgelist != NULL)
        return pgraph->vexs[i].edgelist->endvex;
    else return NON;
}

int nextAdjacent(GraphList* pgraph, int i, int j) {
    PEdgeNode p;
    for (p = pgraph->vexs[i].edgelist; p != NULL; p = p->nextedge)
        if (p->endvex == j) {
            if (p->nextedge != NULL)
                return p->nextedge->endvex;
            else
                return NON;
        }
    return NON;
}


int main() {
    return 0;
}
