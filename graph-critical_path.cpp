/*
最早开始时间等于最晚完成时间的节点序列是关键路径
正逆向拓扑排序
最早开始：
  排完序之后按照拓扑序列摆放，前面的节点往后面所有有边的节点，如果当前节点的时间加上边权大于目前的最早开始时间，更新
最晚结束：
  最早开始倒过来
找所有最早开始和最晚结束相等的节点，连成关键路径
*/

#include <iostream>
#include "Stack.h"
#include <malloc.h>
using namespace std;

#define  MAXVEX   10
#define  MAXEDGE  13

// 全局栈
SeqStack<int> sQ2;

typedef struct EdgeNode
{
    int adjvex;    // 邻接点域，存储该顶点对应的下标
    int weight; // 边的权值
    struct EdgeNode* next; // 链域
} EdgeNode;

typedef struct VertexNode
{
    int inNum;    // 顶点入度值
    int data;    // 顶点数值欲
    EdgeNode* firstedge; // 边表头指针
} VertexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;
    int numVertexes, numEdges; // 图中当前顶点数和边数（对于本案例，已经存在宏定义）
} graphAdjList, *GraphAdjList;

// 构建节点
EdgeNode* BuyNode()
{
    EdgeNode* p = (EdgeNode*)malloc(sizeof(EdgeNode));
    p->adjvex = -1;
    p->next = NULL;
    return p;
}
// 初始化图
void InitGraph(graphAdjList& g)
{
    for (int i = 0; i < MAXVEX; ++i)
    {
        g.adjList[i].firstedge = NULL;
    }
}
// 创建图
void CreateGraph(graphAdjList& g)
{
    int i = 0, begin = 0, end = 0, weight = 0;
    EdgeNode *pNode = NULL;
    cout << "输入10个顶点信息（顶点 入度）:" << endl;
    for (i = 0; i < MAXVEX; ++i)
    {
        cin >> g.adjList[i].data >> g.adjList[i].inNum;
    }
    cout << "输入13条弧的信息（起点 终点 权值）：" << endl;
    for (i = 0; i < MAXEDGE; ++i)
    {
        cin >> begin >> end >> weight;
        pNode = BuyNode();
        pNode->adjvex = end;
        pNode->weight = weight;
        pNode->next = g.adjList[begin].firstedge;
        g.adjList[begin].firstedge = pNode;
    }
}
// 打印输入信息的逻辑图
void PrintGraph(graphAdjList &g)
{
    cout << "打印AOE网的邻接表逻辑图：" << endl;
    for (int i = 0; i < MAXVEX; ++i)
    {
        cout << " " << g.adjList[i].inNum << " " << g.adjList[i].data << " ";
        EdgeNode* p = g.adjList[i].firstedge;
        cout << "-->";
        while (p != NULL)
        {
            int index = p->adjvex;
            cout << "[" << g.adjList[index].data << " " << p->weight << "] " ;
            p = p->next;
        }
        cout << endl;
    }
}
// 求拓扑序列
bool TopologicalSort(graphAdjList g, int* pEtv)
{
    EdgeNode* pNode = NULL;
    int i = 0, k = 0, gettop = 0;
    int nCnt = 0;
    SeqStack<int> sQ1;
    for (i = 0; i < MAXVEX; ++i)
    {
        if (0 == g.adjList[i].inNum)
            sQ1.Push(i);
    }
    for (i = 0; i < MAXVEX; ++i)
    {
        pEtv[i] = 0;
    }
    while (!sQ1.IsEmpty())
    {
        sQ1.Pop(gettop);
        ++nCnt;
        sQ2.Push(gettop); // 将弹出的顶点序号压入拓扑序列的栈
        if (MAXVEX == nCnt)
        {    //去掉拓扑路径后面的-->
            cout << g.adjList[gettop].data << endl;
            break;
        }
        cout << g.adjList[gettop].data << "-->";
        pNode = g.adjList[gettop].firstedge;
        while (pNode != NULL)
        {
            k = pNode->adjvex;
            --g.adjList[k].inNum;
            if (0 == g.adjList[k].inNum)
                sQ1.Push(k);
            if (pEtv[gettop] + pNode->weight > pEtv[k])
                pEtv[k] = pEtv[gettop] + pNode->weight;
            pNode = pNode->next;
        }
    }
    return nCnt != MAXVEX;
}
// 关键路径
void CriticalPath(graphAdjList g, int* pEtv, int* pLtv)
{
    // pEtv  事件最早发生时间
    // PLtv  事件最迟发生时间
    EdgeNode* pNode = NULL;
    int i = 0, gettop = 0, k =0, j = 0;
    int ete = 0, lte = 0; // 声明活动最早发生时间和最迟发生时间变量
    for (i = 0; i < MAXVEX; ++i)
    {
        pLtv[i] = pEtv[MAXVEX-1]; // 初始化
    }
    while (!sQ2.IsEmpty())
    {
        sQ2.Pop(gettop); // 将拓扑序列出栈，后进先出
        pNode = g.adjList[gettop].firstedge;
        while (pNode != NULL)
        {    // 求各顶点事件的最迟发生时间pLtv值
            k = pNode->adjvex;
            if (pLtv[k] - pNode->weight < pLtv[gettop])
                pLtv[gettop] = pLtv[k] - pNode->weight;
            pNode = pNode->next;
        }
    }
    // 求 ete, lte, 和 关键路径
    for (j = 0; j < MAXVEX; ++j)
    {
        pNode = g.adjList[j].firstedge;
        while (pNode != NULL)
        {
            k = pNode->adjvex;
            ete = pEtv[j]; // 活动最早发生时间
            lte = pLtv[k] - pNode->weight; // 活动最迟发生时间
            if (ete == lte)
                cout << "<V" << g.adjList[j].data << ",V" << g.adjList[k].data << "> :" << pNode->weight << endl;
            pNode = pNode->next;
        }
    }
}
void main()
{
    graphAdjList myg;
    InitGraph(myg);
    cout << "创建图：" << endl;
    CreateGraph(myg);
    cout << "打印图的邻接表逻辑结构：" << endl;
    PrintGraph(myg);

    int* pEtv = new int[MAXVEX];
    int* pLtv = new int[MAXVEX];

    cout << "求拓扑序列(全局栈sQ2的值)：" << endl;
    TopologicalSort(myg, pEtv);
    cout << "打印数组pEtv(各个事件的最早发生时间)：" << endl;
    for(int i = 0; i < MAXVEX; ++i)
    {
        cout << pEtv[i] << " ";
    }
    cout << endl << "关键路径：" << endl;

    CriticalPath(myg, pEtv, pLtv);
    cout << endl;
}
/*
创建图：
输入10个顶点信息（顶点 入度）:
0 0
1 1
2 1
3 2
4 2
5 1
6 1
7 2
8 1
9 2
输入13条弧的信息（起点 终点 权值）：
0 1 3
0 2 4
1 3 5
1 4 6
2 3 8
2 5 7
3 4 3
4 6 9
4 7 4
5 7 6
6 9 2
7 8 5
8 9 3
打印图的邻接表逻辑结构：
打印AOE网的邻接表逻辑图：
0 0 -->[2 4] [1 3]
1 1 -->[4 6] [3 5]
1 2 -->[5 7] [3 8]
2 3 -->[4 3]
2 4 -->[7 4] [6 9]
1 5 -->[7 6]
1 6 -->[9 2]
2 7 -->[8 5]
1 8 -->[9 3]
2 9 -->
求拓扑序列(全局栈sQ2的值)：
0-->1-->2-->3-->4-->6-->5-->7-->8-->9
打印数组pEtv(各个事件的最早发生时间)：
0 3 4 12 15 11 24 19 24 27
关键路径：
<V0,V2> :4
<V2,V3> :8
<V3,V4> :3
<V4,V7> :4
<V7,V8> :5
<V8,V9> :3
 */
