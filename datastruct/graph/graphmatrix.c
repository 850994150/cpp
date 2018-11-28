/*  用图邻接矩阵表示实现的一些基本运算*/
#define MAXVEX 20
#define NON -1

typedef char VexType;
typedef float AdjType;
typedef struct {
    int n;                                 /* 图的顶点个数 */
    VexType vexs[MAXVEX];                 /*  顶点信息 顶点数组*/
    AdjType arcs[MAXVEX][MAXVEX];           /* 边信息 二维矩阵*/
} GraphMatrix;

int firstVertex(GraphMatrix* pgraph) {
    return pgraph->n == 0 ? NON : 0;
}

int nextVertex(GraphMatrix* pgraph,int n) {
    return n == pgraph->n-1 ? NON : n+1;
}

int firstAdjacent(GraphMatrix* pgraph, int i) {
    int k;
    for (k = 0; k < pgraph->n; k++)
        if(pgraph->arcs[i][k] != 0) return k;
    return NON;
}

int  nextAdjacent(GraphMatrix* pgraph, int i, int j) {
    int k;
    for (k = j+1; k < pgraph->n; k++)
        if (pgraph->arcs[i][k] != 0) return k;
    return NON;
}


int main() {
    return 0;
}

