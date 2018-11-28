#include<stdio.h>
#define MAXVEX 6
#define MAX 1e+8
typedef char VexType;
typedef float AdjType;

typedef struct {
    int n;                          // 图的顶点个数
    //    VexType vexs[MAXVEX];         //顶点信息
    AdjType arcs[MAXVEX][MAXVEX];   // 边信息
}GraphMatrix;

typedef struct{
    int start_vex, stop_vex;        //边的起点和终点
    AdjType weight;                 //边的权
}Edge;

Edge mst[5];

void prim(GraphMatrix * pgraph, Edge mst[]) {
    int i, j, min, vx, vy;
    float weight, minweight; Edge edge;

    for (i = 0; i < pgraph->n-1; i++) {
        mst[i].start_vex = 0;
        mst[i].stop_vex = i+1;
        mst[i].weight = pgraph->arcs[0][i+1];
    }
    for (i = 0; i < pgraph->n-1; i++) {               //共n-1条边
        minweight = MAX;  min = i;
        for (j = i; j < pgraph->n-1; j++)// 从所有边(vx,vy)(vx∈U,vy∈V-U)中选出最短的边 
            if(mst[j].weight < minweight) {
                minweight = mst[j].weight;
                min = j;
            }

        // mst[min]是最短的边(vx,vy)(vx∈U, vy∈V-U)，将mst[min]加入最小生成树
        edge = mst[min];
        mst[min] = mst[i];
        mst[i] = edge;
        vx = mst[i].stop_vex;            // vx为刚加入最小生成树的顶点的下标 a
        for(j = i+1; j < pgraph->n-1; j++) { // 调整mst[i+1]到mst[n-1]
            vy=mst[j].stop_vex; weight = pgraph->arcs[vx][vy];
            if (weight < mst[j].weight) {
                mst[j].weight = weight;
                mst[j].start_vex = vx;
            }
        }
    }
}


GraphMatrix graph = {
    6,
    {{0,10,MAX,MAX,19,21},
        {10,0,5,6,MAX,11},
        {MAX,5,0,6,MAX,MAX},
        {MAX,6,6,0,18,14},
        {19,MAX,MAX,18,0,33},
        {21,11,MAX,14,33,0}
    }
};

int main()
{
    int i;
    prim(&graph,mst);
    for (i = 0; i < graph.n-1; i++)
        printf("(%d %d %.0f)\n", mst[i].start_vex,
                mst[i].stop_vex, mst[i].weight);

    return 0;
}
