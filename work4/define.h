#include <stdio.h>
#include <string.h>

#include "stdlib.h"

#define TRUE 1             // 表示真值
#define FALSE 0            // 表示为假
#define OK 1               // 返回状态为已完成
#define ERROR 0            // 返回状态出错
#define INFEASIBLE -1      // 返回状态不合理
#define OVERFLOW -2        // 返回状态溢出
#define MAX_VERTEX_NUM 20  // 定义最大容量
typedef int status;        // 定义状态数据类型
typedef int KeyType;       // 定义关键字数据类型

typedef struct {
  KeyType key;      // 关键字
  char others[20];  // 结点名称
} VertexType;       // 顶点类型定义

typedef struct ArcNode {    // 表结点类型定义
  int adjvex;               // 顶点位置编号
  struct ArcNode* nextarc;  // 下一个表结点指针
} ArcNode;

typedef struct VNode {  // 头结点及其数组类型定义
  VertexType data;      // 顶点信息
  ArcNode* firstarc;    // 指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {       // 邻接表的类型定义
  AdjList vertices;    // 头结点数组
  int vexnum, arcnum;  // 顶点数、弧数
} ALGraph;

typedef struct QNode {  // 结点的队列
  VertexType data;      // 结点数据
  struct QNode* next;   // 指向下个结点的指针
} QNode, *Queue;

typedef struct {
  Queue front;  // 队列队头
  Queue rear;   // 队列队尾
} Linkqueue;    // 结点队列

typedef struct {  // 多图的管理表定义
  struct {
    char name[30];  // 单图的名称
    ALGraph G;      // 单图
  } elem[10];       // 10个多图
  int length;       // 定义当前多图的数量
} LISTS;            // 多图的定义

void print1(void);                          // 输出函数1
void print2(void);                          // 输出函数2
void print3(void);                          // 输出函数3
status JudgeV(VertexType V[], ALGraph& G);  // 查找V是否合法
status JudgeVR(VertexType V[], KeyType VR[][2], ALGraph& G);  // 查找VR是否合法
status CreateCraph(ALGraph& G, VertexType V[], KeyType VR[][2]);  // 创建无向图
status DestroyGraph(ALGraph& G);      // 销毁无向图
int LocateVex(ALGraph G, KeyType u);  // 查找顶点
int Compare(ALGraph G, KeyType u,
            VertexType value);  // 赋值操作辅助函数比较关键字唯一性
status PutVex(ALGraph& G, KeyType u, VertexType value);  // 顶点赋值
int FirstAdjVex(ALGraph G, KeyType u);               // 获得第一邻接点
int NextAdjVex(ALGraph G, KeyType v, KeyType w);     // 获得下一邻接点
status InsertVex(ALGraph& G, VertexType v);          // 插入顶点
status DeleteVex(ALGraph& G, KeyType v);             // 删除顶点
status InsertArc(ALGraph& G, KeyType v, KeyType w);  // 插入弧
status DeleteArc(ALGraph& G, KeyType v, KeyType w);  // 删除弧
void DFS(ALGraph G, int v, void (*visit)(VertexType),
         int visited[]);  // 深度遍历辅助函数
status DFSTraverse(ALGraph G, void (*visit)(VertexType));  // 深度遍历
status BFSTraverse(ALGraph G, void (*visit)(VertexType));  // 广度遍历
void visit(VertexType v);                                  // 输出函数
status SaveGraph(ALGraph G, char FileName[]);              // 保存文件
status LoadGraph(ALGraph& G, char FileName[]);             // 读取文件
status RemoveList(LISTS& Lists, char ListName[]);          // 多图移除
status LocateList(LISTS Lists, char ListName[]);           // 多图查找
status AddList(LISTS& Lists, char ListName[]);             // 多图表名创建
status MoreSaveGraph(ALGraph G, FILE* fp);                 // 多图文件保存
status MoreLoadGraph(ALGraph& G, FILE* fp);                // 多图文件读取
status InitQueue(Linkqueue& Q);                            // 创建图的队列
status QueueEmpty(Linkqueue Q);  // 判断图的队列是否为空
status enQueue(Linkqueue& Q, VertexType value);  // 将为value的结点入队
status deQueue(
    Linkqueue& Q,
    VertexType& value);  // 将结点出队，并将出队的结点数据保存在value中
status ConnectedComponentsNums(ALGraph G);  //
status ShortestPathLength(ALGraph G, KeyType v,
                          KeyType w);  // 两个顶点的最短路径
void VerticesSetLessThank(ALGraph G, KeyType v, KeyType k);

ALGraph G;    // 创建单图
LISTS Lists;  // 创建多图

int op;             // 操作序号
int number;         // 储存查找图的序号
char saveName[30];  // 暂存图名
int distance[21];   // 储存最短路径长度
int visited[100];   // 记录深搜时某个结点是否搜过
bool mark[21];      // 记录宽搜时某个结点是否搜过

/*函数*/
void print1(void) {
  printf(
      "\n-----------------单图操作菜单--------------------\n\
	1.创建图           2.销毁图             3.查找顶点\n\
	4.顶点赋值         5.获得第一邻接顶点   6.获得下一邻接点\n\
	7.插入顶点         8.删除顶点           9.插入弧\n\
	10.删除弧          11.深度优先搜索遍历  12.广度优先搜索遍历\n\
	13.文件保存        14.文件读取          15.距离小于k的顶点集合\n\
	16.顶点间最短路径和长度  17.连通分量     0.停止操作\n\
	请输入【0~17】\n\n请输入你需要的操作：");
}
void print2(void) {
  printf(
      "\n-----------------多图操作中的单图操作菜单--------------------\n\
	1.创建图           2.销毁图             3.查找顶点\n\
	4.顶点赋值         5.获得第一邻接顶点   6.获得下一邻接点\n\
	7.插入顶点         8.删除顶点           9.插入弧\n\
	10.删除弧          11.深度优先搜索遍历  12.广度优先搜索遍历\n\
	13.文件保存        14.文件读取          15.距离小于k的顶点集合\n\
	16.顶点间最短路径和长度  17.连通分量     18.返回多图菜单\n\
	0.停止操作\n\
	请输入【0~18】\n\n请输入你需要的操作：");
}
void print3(void) {
  printf(
      "\n-----------------多图操作菜单--------------------\n\
	1.创建多图        2.移除某图        3.查找某图\n\
	4.单独操作        5.遍历多图        6.清空多图\n\
	0.停止操作        请输入【0~6】\n\n请输入你需要的操作：");
}

status JudgeV(VertexType V[], ALGraph& G) {
  int i, j;
  for (i = 0; V[i].key != -1; i++) {
    for (j = i + 1; V[j].key != -1; j++) {
      if (V[i].key == V[j].key) return ERROR;
    }
  }
  if (i > 20)
    return ERROR;
  else {
    G.vexnum = i;
    return OK;
  }
}
// 比较V的合法性，不合法返回ERROR；

status JudgeVR(VertexType V[], KeyType VR[][2], ALGraph& G) {
  int i, j, m, n = 0;
  for (i = 0, j = 0; VR[i][j] != -1; i++) {
    for (m = 0; V[m].key != -1; m++) {
      if (VR[i][j] == V[m].key) n++;
      if (VR[i][j + 1] == V[m].key) n++;
    }
    if (n != 2) return ERROR;
    n = 0, j = 0;
  }
  G.arcnum = i;
  return OK;
}
// 比较VR的合法性，不合法返回ERROR；

status CreateCraph(ALGraph& G, VertexType V[], KeyType VR[][2]) {
  G.vexnum = 0, G.arcnum = 0;
  if (JudgeV(V, G) == ERROR)
    return ERROR;
  else {
    int i;
    for (i = 0; i < G.vexnum; i++) {
      G.vertices[i].data.key = V[i].key;
      strcpy(G.vertices[i].data.others, V[i].others);
      G.vertices[i].firstarc = NULL;
    }
    if (JudgeVR(V, VR, G) == ERROR) {
      G.vexnum = 0, G.arcnum = 0;
      return ERROR;
    }

    int j;
    for (j = 0; j < G.arcnum; j++) {
      ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
      p->adjvex = LocateVex(G, VR[j][1]);
      p->nextarc = G.vertices[LocateVex(G, VR[j][0])].firstarc;
      G.vertices[LocateVex(G, VR[j][0])].firstarc = p;

      ArcNode* q = (ArcNode*)malloc(sizeof(ArcNode));
      q->adjvex = LocateVex(G, VR[j][0]);
      q->nextarc = G.vertices[LocateVex(G, VR[j][1])].firstarc;
      G.vertices[LocateVex(G, VR[j][1])].firstarc = q;
    }
  }
  return OK;
}
// 根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR，如果有相同的关键字，返回ERROR。

void visit(VertexType v) { printf(" %d %s", v.key, v.others); }
// 输出函数

status DestroyGraph(ALGraph& G) {
  int i;
  ArcNode *p, *q;
  for (i = 0; i < G.vexnum; i++) {
    p = G.vertices[i].firstarc;
    while (p) {
      q = p->nextarc;
      free(p);
      p = q;
    }
  }
  G.vexnum = 0;
  G.arcnum = 0;
  return OK;
}
// 销毁图

int LocateVex(ALGraph G, KeyType u) {
  int i;
  for (i = 0; i < G.vexnum; i++) {
    if (u == G.vertices[i].data.key) return i;
  }
  return -1;
}
// 根据u在图G中查找顶点，查找成功返回位序，否则返回-1

int Compare(ALGraph G, KeyType u, VertexType value) {
  int i, NOu = -1, NOvalue = -1;
  for (i = 0; i < G.vexnum; i++) {
    if (G.vertices[i].data.key == u) NOu = i;
    if (G.vertices[i].data.key == value.key) NOvalue = i;
  }
  if (NOu == -1) return -1;
  if (NOvalue != -1 && NOu != NOvalue) return -1;
  return NOu;
}
// 比较赋值操作是否违反关键字唯一性

status PutVex(ALGraph& G, KeyType u, VertexType value) {
  int n;
  if ((n = Compare(G, u, value)) == -1) return ERROR;
  G.vertices[n].data.key = value.key;
  strcpy(G.vertices[n].data.others, value.others);
  return OK;
}
// 根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；如果查找失败或关键字不唯一，返回ERROR

int FirstAdjVex(ALGraph G, KeyType u) {
  int n;
  if ((n = LocateVex(G, u)) == -1) return -1;  // 查找失败返回-1
  if (G.vertices[n].firstarc == NULL)
    return -2;  // 如果查找成功但没有第一邻接点则返回-2
  return G.vertices[n].firstarc->adjvex;
}
// 根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；

int NextAdjVex(ALGraph G, KeyType v, KeyType w) {
  int iv, iw;
  if ((iv = LocateVex(G, v)) == -1) return -1;
  if ((iw = LocateVex(G, w)) == -1) return -1;

  ArcNode* p = G.vertices[iv].firstarc;
  while (p) {
    if (p->adjvex == iw && p->nextarc != NULL) return p->nextarc->adjvex;
    p = p->nextarc;
  }
  return -1;
}
// 根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；

status InsertVex(ALGraph& G, VertexType v) {
  if (LocateVex(G, v.key) != -1) return ERROR;
  if (G.vexnum == MAX_VERTEX_NUM) return ERROR;
  G.vertices[G.vexnum].data.key = v.key;
  strcpy(G.vertices[G.vexnum].data.others, v.others);
  G.vertices[G.vexnum].firstarc = NULL;
  G.vexnum++;
  return OK;
}
// 在图G中插入顶点v，成功返回OK,否则返回ERROR

status DeleteVex(ALGraph& G, KeyType v) {
  int n, i;
  if ((n = LocateVex(G, v)) == -1 || G.vexnum == 1 || G.vexnum == 0)
    return ERROR;
  ArcNode *p = G.vertices[n].firstarc, *q, *save, *delt;
  while (p) {
    q = p->nextarc;
    save = G.vertices[p->adjvex].firstarc;
    if (save->adjvex == n)
      G.vertices[p->adjvex].firstarc = save->nextarc;
    else {
      while (save->nextarc) {  // 删除其他结点的相关边
        if (save->nextarc->adjvex == n) {
          delt = save->nextarc;
          save->nextarc = save->nextarc->nextarc;
          free(delt);
          break;
        }
        save = save->nextarc;
      }
    }
    free(p);
    p = q;
  }
  for (i = n + 1; i < G.vexnum; i++) {
    G.vertices[i - 1] = G.vertices[i];
  }
  G.vexnum--;
  for (i = 0; i < G.vexnum; i++) {
    p = G.vertices[i].firstarc;
    while (p) {
      if (p->adjvex >= n) p->adjvex--;
      p = p->nextarc;
    }
  }
  return OK;
}
// 在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR

status InsertArc(ALGraph& G, KeyType v, KeyType w) {
  int i, j;
  ArcNode *p, *q;
  if ((i = LocateVex(G, v)) == -1 || (j = LocateVex(G, w)) == -1) return ERROR;
  p = G.vertices[i].firstarc;

  while (p) {
    if (p->adjvex == j) {
      return ERROR;
    }
    p = p->nextarc;
  }
  p = (ArcNode*)malloc(sizeof(ArcNode));
  q = (ArcNode*)malloc(sizeof(ArcNode));
  p->adjvex = i;
  q->adjvex = j;
  p->nextarc = G.vertices[j].firstarc;
  G.vertices[j].firstarc = p;
  q->nextarc = G.vertices[i].firstarc;
  G.vertices[i].firstarc = q;

  return OK;
}
// 在图G中增加弧<v,w>，成功返回OK,否则返回ERROR

status DeleteArc(ALGraph& G, KeyType v, KeyType w) {
  int i, j, n = 0;
  ArcNode *p, *q;
  if ((i = LocateVex(G, v)) == -1 || (j = LocateVex(G, w)) == -1) return ERROR;
  p = G.vertices[i].firstarc;

  if (p->adjvex == j) {
    G.vertices[i].firstarc = p->nextarc;
    free(p);
  } else {
    while (p->nextarc) {
      if (p->nextarc->adjvex == j) {
        q = p->nextarc;
        p->nextarc = p->nextarc->nextarc;
        free(q);
        n++;
        break;
      }
      p = p->nextarc;
    }
    if (n == 0) return ERROR;
  }

  q = G.vertices[j].firstarc;
  if (q->adjvex == i) {
    G.vertices[j].firstarc = q->nextarc;
    free(q);
  } else {
    while (q->nextarc) {
      if (q->nextarc->adjvex == i) {
        p = q->nextarc;
        q->nextarc = q->nextarc->nextarc;
        free(p);
        break;
      }
      q = q->nextarc;
    }
  }
  return OK;
}
// 在图G中删除弧<v,w>，成功返回OK,否则返回ERROR

void DFS(ALGraph G, int v, void (*visit)(VertexType), int visited[]) {
  int w;
  visited[v] = 1;
  visit(G.vertices[v].data);
  for (w = FirstAdjVex(G, G.vertices[v].data.key); w >= 0;
       w = NextAdjVex(G, G.vertices[v].data.key, G.vertices[w].data.key))
    if (!visited[w])  // 处理所有未访问的邻接顶点
      DFS(G, w, visit, visited);
}

status DFSTraverse(ALGraph G, void (*visit)(VertexType)) {
  int v;
  for (v = 0; v < G.vexnum; v++)  // 初始化各顶点未访问状态
    visited[v] = 0;
  for (v = 0; v < G.vexnum; v++)
    if (!visited[v])  // 从一个未访问的顶点开始
      DFS(G, v, visit, visited);
  return OK;
}
// 对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次

status BFSTraverse(ALGraph G, void (*visit)(VertexType)) {
  int v, w, u;
  for (v = 0; v < G.vexnum; v++) visited[v] = 0;
  int Que[100], in = 0, out = 0;

  for (v = 0; v < G.vexnum; v++)  // 按顶点位置序号依次选择顶点
    if (!visited[v]) {            // 遇到未访问过的顶点开始遍历
      visited[v] = 1;
      visit(G.vertices[v].data);
      Que[in] = v;
      in++;
      while (in != out) {
        u = Que[out];
        out++;
        for (w = FirstAdjVex(G, G.vertices[u].data.key); w >= 0;
             w = NextAdjVex(G, G.vertices[u].data.key, G.vertices[w].data.key))
          if (!visited[w]) {
            visited[w] = 1;
            visit(G.vertices[w].data);
            Que[in] = w;
            in++;
          }
      }
    }
  return OK;
}
// 对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次

status SaveGraph(ALGraph G, char FileName[]) {
  FILE* fp = fopen(FileName, "w");
  int i, j;
  for (i = 0; i < G.vexnum; i++) {
    fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
  }
  fprintf(fp, "-1 nil ");
  int VR[20][20];

  for (i = 0; i < G.vexnum; i++) {
    ArcNode* p = G.vertices[i].firstarc;
    while (p) {
      VR[i][p->adjvex] = 1;
      p = p->nextarc;
    }
  }
  for (i = 0; i < G.vexnum; i++) {
    for (j = i; j < G.vexnum; j++) {
      if (VR[i][j] == 1)
        fprintf(fp, "%d %d ", G.vertices[i].data.key, G.vertices[j].data.key);
    }
  }
  fprintf(fp, "-1 -1 ");
  fclose(fp);
  return OK;
}
// 将图的数据写入到文件FileName中

status LoadGraph(ALGraph& G, char FileName[]) {
  FILE* fp = fopen(FileName, "r");
  VertexType V[10];
  KeyType VR[100][2];
  int i = 0, n = 0;
  do {
    fscanf(fp, "%d%s", &V[i].key, V[i].others);
  } while (V[i++].key != -1);

  do {
    fscanf(fp, "%d%d", &VR[n][0], &VR[n][1]);
  } while (VR[n++][0] != -1);

  if (CreateCraph(G, V, VR) == ERROR) {
    fclose(fp);
    return ERROR;
  }
  fclose(fp);
  return OK;
}
// 读入文件FileName的图数据，创建图的邻接表

status RemoveList(LISTS& L, char ListName[]) {
  int n;
  for (n = 0; n < Lists.length; n++) {
    if (!strcmp(Lists.elem[n].name, ListName)) {
      for (; n < Lists.length - 1; n++) {
        Lists.elem[n] = Lists.elem[n + 1];
      }
      Lists.length--;
      return OK;
    }
  }
  return ERROR;
}

status LocateList(
    LISTS Lists,
    char ListName
        [])  // 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回ERROR
{
  int n;
  for (n = 0; n < Lists.length; n++) {
    if (!strcmp(Lists.elem[n].name, ListName)) return (n + 1);
  }
  return ERROR;
}

status AddList(LISTS& Lists, char ListName[])  // 创建表名
{
  strcpy(Lists.elem[Lists.length].name, ListName);
  Lists.length++;
  return OK;
}

status MoreSaveGraph(ALGraph G, FILE* fp) {
  int i, j;
  for (i = 0; i < G.vexnum; i++) {
    fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
  }
  fprintf(fp, "-1 nil ");
  int VR[20][20];

  for (i = 0; i < G.vexnum; i++) {
    ArcNode* p = G.vertices[i].firstarc;
    while (p) {
      VR[i][p->adjvex] = 1;
      p = p->nextarc;
    }
  }
  for (i = 0; i < G.vexnum; i++) {
    for (j = i; j < G.vexnum; j++) {
      if (VR[i][j] == 1)
        fprintf(fp, "%d %d ", G.vertices[i].data.key, G.vertices[j].data.key);
    }
  }
  fprintf(fp, "-1 -1");
  return OK;
}

status MoreLoadGraph(ALGraph& G, FILE* fp) {
  VertexType V[10];
  KeyType VR[100][2];
  int i = 0, n = 0;
  do {
    fscanf(fp, "%d%s", &V[i].key, V[i].others);
  } while (V[i++].key != -1);

  do {
    fscanf(fp, "%d%d", &VR[n][0], &VR[n][1]);
  } while (VR[n++][0] != -1);

  if (CreateCraph(G, V, VR) == ERROR) return ERROR;
  return OK;
}

status InitQueue(Linkqueue& Q) {
  Q.front = Q.rear = (QNode*)malloc(sizeof(QNode));
  if (!Q.front) return ERROR;
  Q.front->next = NULL;
  return OK;
}

status QueueEmpty(Linkqueue Q) {
  if (Q.front == Q.rear)
    return TRUE;
  else
    return FALSE;
}

status enQueue(Linkqueue& Q, VertexType value) {
  Queue p = (Queue)malloc(sizeof(QNode));
  if (!p) return ERROR;
  p->data = value;
  p->next = NULL;
  Q.rear->next = p;
  Q.rear = p;
  return OK;
}

status deQueue(Linkqueue& Q, VertexType& value) {
  if (Q.front == Q.rear) return ERROR;
  Queue p = Q.front->next;
  value = p->data;
  Q.front->next = p->next;
  if (Q.rear == p) Q.rear = Q.front;
  free(p);
  return OK;
}

status ShortestPathLength(ALGraph G, KeyType v,
                          KeyType w)  // 返回顶点v与顶点w的最短路径长度
{
  int i, j, n;
  VertexType top;
  top.key = v;
  Linkqueue Q;
  InitQueue(Q);
  for (i = 0; i < G.vexnum; i++) distance[G.vertices[i].data.key] = 20;
  distance[v] = 0;
  int k = LocateVex(G, v);
  enQueue(Q, G.vertices[k].data);
  while (!QueueEmpty(Q)) {
    deQueue(Q, top);
    if (top.key == w) break;
    for (j = FirstAdjVex(G, top.key); j >= 0;
         j = NextAdjVex(G, top.key, G.vertices[j].data.key))  // 返回位序
    {
      if (distance[G.vertices[j].data.key] == 20) {
        distance[G.vertices[j].data.key] = distance[top.key] + 1;
        enQueue(Q, G.vertices[j].data);
      }
    }
  }
  n = distance[w];
  return n;
}

void VerticesSetLessThank(ALGraph G, KeyType v,
                          KeyType k)  // 返回与顶点v距离小于k的顶点集合
{
  int i, j, flag = 0;
  for (i = 0; i < G.vexnum; i++) {
    if (G.vertices[i].data.key == v) continue;
    j = ShortestPathLength(G, v, G.vertices[i].data.key);
    if (j < k) {
      printf("%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
      flag = 1;
    }
  }
  if (flag == 0) printf("不存在！");
}

void dfs(ALGraph& G, KeyType v) {
  mark[v] = TRUE;
  for (int w = FirstAdjVex(G, v); w >= 0;
       w = NextAdjVex(G, v, G.vertices[w].data.key)) {
    if (!mark[G.vertices[w].data.key]) dfs(G, G.vertices[w].data.key);
  }
}

status ConnectedComponentsNums(ALGraph G)  // 求图中连通分量个数
{
  int count = 0, i;
  for (i = 0; i < G.vexnum; i++)
    mark[G.vertices[i].data.key] = FALSE;  // 标记数组记录关键字
  for (i = 0; i < G.vexnum; i++) {
    if (!mark[G.vertices[i].data.key]) {
      dfs(G, G.vertices[i].data.key);
      count++;
    }
  }
  return count;
}
