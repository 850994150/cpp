/***********************************************************
* Author       : M_Kepler
* EMail        : m_kepler@foxmail.com
* Last modified: 2016-11-06 22:37:32
* Filename     : prime.cpp
* Description  :
**********************************************************/

#include <iostream>
using namespace std;

#define MAXVEX 100/* 最大顶点数，应由用户定义 */
#define INFINITY  65535 /* 表示权值的无穷*/
typedef int EdgeType;/* 边上的权值类型应由用户定义 */
typedef char VertexType;/* 顶点类型应由用户定义  */

typedef struct {
    EdgeType start_vex, stop_vex;
    EdgeType weight;
}Edge;

/*
 * Edge类型的数组
 * |start_vex|stop_vex|weight|
 * |start_vex|stop_vex|weight|
 * |start_vex|stop_vex|weight|
 * |start_vex|stop_vex|weight|
 */
typedef struct
{
    VertexType vexs[MAXVEX];/* 顶点表 */
    EdgeType arc[MAXVEX][MAXVEX];/* 邻接矩阵，可看作边表 */
    int n, numEdges;/* 图中当前的顶点数和边数  */
} GraphMatrix;

void prime(GraphMatrix *pgraph, Edge *mst){
    int i, j, min, vx, vy;
    float weight, minweight;
    Edge edge;
    // 初始化Edge
    for (i = 0; i < pgraph->n; ++i) {
        mst[i].start_vex=0;
        mst[i].stop_vex=i+1;
        mst[i].weight=pgraph->arc[0][i+1];
    }
    //找到Edge数组里权重最小的边
    for (i = 0; i < pgraph->n; ++i) {
        minweight=MAXVEX;
        min = i;
        for (j = i; j < pgraph->n; ++j) {
            if(mst[j].weight < minweight){
                minweight = mst[j].weight;
                min = j;
            }
        }
        //
        edge = mst[min]; mst[min] = mst[i]; mst[i] = edge;
        // 取权重最小的边的终点，作为新的起点
        vx = mst[i].stop_vex;
        // 比较新加入的点到其他未加入的点的距离和Edge数组里存的到其他点的距离,
        // 来更新Edge数组
        for (j = i+1; j < pgraph->n; ++j) {
            vy = mst[j].stop_vex;
            weight = pgraph->arc[vx][vy];
            mst[j].start_vex = vx;
        }
    }
}

