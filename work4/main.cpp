#include "define.h"

int main() {
  printf(
      "-----------------基于邻接表的无向图系统--------------------\n\n");  // 一级菜单
  printf("1.单图操作\t\t2.多图操作\t\t0.停止操作\n\n请输入你需要的操作：");

  scanf("%d", &op);  // 输入操作数
  if (op == 1) {     // 单图操作（二级菜单）
    printf(
        "\n-----------------单图操作菜单--------------------\n\
		1.创建图           2.销毁图             3.查找顶点\n\
		4.顶点赋值         5.获得第一邻接顶点   6.获得下一邻接点\n\
		7.插入顶点         8.删除顶点           9.插入弧\n\
		10.删除弧          11.深度优先搜索遍历  12.广度优先搜索遍历\n\
		13.文件保存        14.文件读取          15.距离小于k的顶点集合\n\
		16.顶点间最短路径和长度  17.连通分量     0.停止操作\n\
		请输入【0~17】\n\n请输入你需要的操作：");
    G.vexnum = 0, G.arcnum = 0;  // 初始化顶点数和边数
    scanf("%d", &op);            // 输入操作
    while (op) {
      switch (op) {
        case 1: {  // 创建图
          if (G.vexnum == 0) {
            VertexType V[30];    // 暂存顶点数据
            KeyType VR[100][2];  // 暂存弧的数据
            int ans, i = 0;
            printf("请输入顶点数据【以-1为结尾】：");
            do {  // 输入顶点数据
              scanf("%d%s", &V[i].key, V[i].others);
            } while (V[i++].key != -1);
            printf("请输入弧数据【以-1为结尾】：");
            i = 0;
            do {  // 输入弧的数据
              scanf("%d%d", &VR[i][0], &VR[i][1]);
            } while (VR[i++][0] != -1);
            ans = CreateCraph(G, V, VR);  // 创建无向图
            if (ans == OK) {
              printf("无向图创建成功！遍历为：\n");
              for (i = 0; i < G.vexnum; i++) {
                ArcNode* p = G.vertices[i].firstarc;
                printf("%d %s", G.vertices[i].data.key,
                       G.vertices[i].data.others);
                while (p) {
                  printf(" %d", p->adjvex);
                  p = p->nextarc;
                }
                printf("\n");
              }
              printf("\n");
            } else
              printf("无向图创建失败！\n");
          } else
            printf("无向图图存在，无法创建！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 2: {  // 销毁图
          if (G.vexnum != 0) {
            DestroyGraph(G);  // 调用销毁图的函数
            printf("无向图销毁成功！\n");
          } else
            printf("无向图为空，无需销毁！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 3: {  // 查找顶点
          if (G.vexnum != 0) {
            int e, ans;
            printf("请输入你想查找结点的关键字：");
            scanf("%d", &e);
            ans = LocateVex(G, e);  // 调用查找结点函数
            if (ans == -1)
              printf("查找失败！\n");
            else
              printf("对应结点为 %d,%s\n", G.vertices[ans].data.key,
                     G.vertices[ans].data.others);
          } else
            printf("无向图为空，查找失败！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 4: {  // 顶点赋值
          if (G.vexnum != 0) {
            VertexType e;
            int ans, key;
            printf("输入替换的顶点关键字：");
            scanf("%d", &key);
            printf("输入赋值：");
            scanf("%d%s", &e.key, e.others);

            ans = PutVex(G, key, e);  // 调用赋值结点函数
            if (ans == OK) {
              printf("赋值成功，深度搜索遍历为：");
              BFSTraverse(G, visit);
              printf("\n");
            } else
              printf("赋值操作失败！有可能是结点不存在！\n");

          } else
            printf("无向图图为空，赋值操作失败！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 5: {  // 获得第一邻接点
          if (G.vexnum != 0) {
            int key, ans;
            printf("请输入需要获得第一邻接顶点的关键字：");
            scanf("%d", &key);
            ans = FirstAdjVex(G, key);  // 调用查找第一邻接点的函数
            if (ans == -2) printf("顶点无第一邻接顶点\n");
            if (ans == -1) printf("无该顶点!\n");
            if (ans >= 0)
              printf("%d结点的第一邻接点是%d,%s\n", key,
                     G.vertices[ans].data.key, G.vertices[ans].data.others);
          } else
            printf("无向图为空！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 6: {  // 获得下一邻接点
          if (G.vexnum != 0) {
            int key, relat, ans;
            printf("输入待查找结点和相对结点：");
            scanf("%d%d", &key, &relat);
            ans = NextAdjVex(G, key, relat);  // 调用查找相对节点的函数
            if (ans == -1)
              printf("获取失败！\n");
            else {
              printf("%d相对于%d的顶点为%d,%s\n", key, relat,
                     G.vertices[ans].data.key, G.vertices[ans].data.others);
            }
          } else
            printf("无向图为空，获取失败！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 7: {  // 插入顶点
          if (G.vexnum != 0) {
            VertexType e;
            int ans, i;
            printf("输入待插入的顶点数据：");
            scanf("%d%s", &e.key, e.others);
            ans = InsertVex(G, e);  // 调用插入函数
            if (ans == OK) {
              printf("插入成功，遍历为：\n");
              for (i = 0; i < G.vexnum; i++) {
                ArcNode* p = G.vertices[i].firstarc;
                printf("%d %s", G.vertices[i].data.key,
                       G.vertices[i].data.others);
                while (p) {
                  printf(" %d", p->adjvex);
                  p = p->nextarc;
                }
                printf("\n");
              }
              printf("\n");
            } else
              printf("插入操作失败！\n");
          } else
            printf("无向图为空，请先创建图！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 8: {  // 删除顶点
          if (G.vexnum != 0) {
            int e, ans, i;
            printf("请输入删除结点：");
            scanf("%d", &e);
            ans = DeleteVex(G, e);  // 调用删除顶点函数
            if (ans == OK) {
              printf("删除成功，遍历为：\n");
              for (i = 0; i < G.vexnum; i++) {
                ArcNode* p = G.vertices[i].firstarc;
                printf("%d %s", G.vertices[i].data.key,
                       G.vertices[i].data.others);
                while (p) {
                  printf(" %d", p->adjvex);
                  p = p->nextarc;
                }
                printf("\n");
              }
              printf("\n");
            } else
              printf("删除操作失败！\n");
          } else
            printf("图为空，删除操作失败！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 9: {  // 添加弧
          if (G.vexnum != 0) {
            int ans, i, v, w;
            printf("输入待插入的弧数据：");
            scanf("%d%d", &v, &w);
            ans = InsertArc(G, v, w);  // 调用添加弧的函数
            if (ans == OK) {
              printf("添加成功，遍历为：\n");  // 添加成功就直接遍历
              for (i = 0; i < G.vexnum; i++) {
                ArcNode* p = G.vertices[i].firstarc;
                printf("%d %s", G.vertices[i].data.key,
                       G.vertices[i].data.others);
                while (p) {
                  printf(" %d", p->adjvex);
                  p = p->nextarc;
                }
                printf("\n");
              }
              printf("\n");
            } else
              printf("插入操作失败！\n");
          } else
            printf("无向图为空，请先创建图！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 10: {  // 删除弧
          if (G.vexnum != 0) {
            int v, w, ans, i;
            printf("请输入删除弧：");
            scanf("%d%d", &v, &w);
            ans = DeleteArc(G, v, w);  // 调用删除弧的函数
            if (ans == OK) {
              printf("删除成功，遍历为：\n");
              for (i = 0; i < G.vexnum; i++) {
                ArcNode* p = G.vertices[i].firstarc;
                printf("%d %s", G.vertices[i].data.key,
                       G.vertices[i].data.others);
                while (p) {
                  printf(" %d", p->adjvex);
                  p = p->nextarc;
                }
                printf("\n");
              }
              printf("\n");
            } else
              printf("删除操作失败！\n");
          } else
            printf("图为空，删除操作失败！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 11: {  // 深度遍历
          if (G.vexnum != 0) {
            printf("深度优先搜索遍历：");
            DFSTraverse(G, visit);  // 调用深度优先遍历函数
            putchar('\n');
          } else
            printf("无向图不存在！遍历为空！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 12: {  // 广度遍历
          if (G.vexnum != 0) {
            printf("广度优先搜索遍历：");
            BFSTraverse(G, visit);  // 调用广度优先边路函数
            putchar('\n');
          } else
            printf("无向图不存在！遍历为空！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 13: {  // 文件保存
          if (G.vexnum != 0) {
            char FileName[30];  // 目标文件名
            printf("请输入要保存的文件名:\n");
            scanf("%s", FileName);
            if (SaveGraph(G, FileName) == OK)
              printf("保存成功！\n");  // 调用文件保存函数
          } else
            printf("图为空，保存失败！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 14: {  // 文件读取
          if (G.vexnum == 0) {
            char FileName[30];  // 目标文件名
            printf("请输入要读取的文件名:\n");
            scanf("%s", FileName);
            if (LoadGraph(G, FileName) == OK)
              printf("读取成功！\n");  // 调用文件读取函数
          } else
            printf("图不为空，无法读取文件！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 15: {  // 查找与顶点距离小于K的顶点
          if (G.vexnum != 0) {
            int v, k;
            printf("请输入顶点的关键字及查找距离！\n");
            scanf("%d%d", &v, &k);
            printf("与顶点距离小于%d的顶点有\n", k);
            VerticesSetLessThank(G, v, k);  // 调用查找与顶点距离小于k的点的函数
          } else
            printf("无向图为空!\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 16: {  // 输出两个顶点的最短路径
          if (G.vexnum != 0) {
            int v, w, k;
            printf("请输入两个顶点的关键字!\n");
            scanf("%d%d", &v, &w);
            k = ShortestPathLength(G, v, w);  // 调用求两个顶点的最短路径的长度
            printf("这两个顶点间的最短路径是%d", k);
          } else
            printf("无向图为空!\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 17: {  // 求图的连通分量
          if (G.vexnum != 0) {
            printf("图的连通分量有%d个！\n",
                   ConnectedComponentsNums(G));  // 调用求图的连通分量的函数
          } else
            printf("无向图为空!\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        default: {
          printf("输入错误，请重新输入！\n");
          getchar();
          getchar();
          system("cls");
        }
      }
      print1();
      scanf("%d", &op);
    }
  }

  if (op == 2) {       // 多图操作（二级菜单）
    Lists.length = 0;  // 初始化Lists长度
  A:;
    printf(
        "\n-----------------多图操作菜单--------------------\n\
		1.创建多图        2.移除某图        3.查找某图\n\
		4.单独操作        5.遍历多图        6.清空多图\n\
		0.停止操作        请输入【0~6】\n\n请输入你需要的操作：");
    scanf("%d", &op);
    while (op) {
      switch (op) {
        case 1: {  // 创建多图中的单图
          printf("输入创建图的名称：");
          scanf("%s", saveName);

          VertexType V[30];    // 暂时储存顶点数据的数组
          KeyType VR[100][2];  // 暂时储存边的数据的数组
          int ans, i = 0;
          printf("请输入顶点数据【以-1为结尾】：");
          do {
            scanf("%d%s", &V[i].key, V[i].others);
          } while (V[i++].key != -1);
          printf("请输入弧数据【以-1为结尾】：");
          i = 0;
          do {
            scanf("%d%d", &VR[i][0], &VR[i][1]);
          } while (VR[i++][0] != -1);
          ans = CreateCraph(Lists.elem[Lists.length].G, V, VR);
          if (ans == OK) {
            AddList(Lists, saveName);
            printf("创建成功！");
            putchar('\n');
          } else
            printf("创建失败！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 2: {  // 移除某图
          printf("输入你想移除图的名称：");
          scanf("%s", saveName);
          if (RemoveList(Lists, saveName) == ERROR) {
            printf("无该名的无向图！\n");
          } else
            printf("删除成功！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 3: {  // 查找某图
          printf("输入你想查找树的名称：");
          scanf("%s", saveName);
          if ((number = LocateList(Lists, saveName)) == ERROR) {
            printf("无该名的无向图！\n");
            getchar();
            getchar();
            system("cls");
            break;
          }  // 调用查找树的函数
          printf("查找成功：%s \n", saveName);

          if (Lists.elem[number - 1].G.vexnum == 0) {
            printf("无数据！\n");
          } else {
            printf("广度搜索遍历：");
            BFSTraverse(Lists.elem[number - 1].G, visit);
            putchar('\n');
          }
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 4: {  // 单独操作
          printf("输入你想单独操作图的名称：");
          scanf("%s", saveName);
          if ((number = LocateList(Lists, saveName)) == ERROR) {
            printf("无该名称的无向图！\n");
            getchar();
            getchar();
            system("cls");
            break;
          }  // 三级菜单
          printf(
              "\n-----------------单图操作菜单--------------------\n\
				1.创建图           2.销毁图             3.查找顶点\n\
				4.顶点赋值         5.获得第一邻接顶点   6.获得下一邻接点\n\
				7.插入顶点         8.删除顶点           9.插入弧\n\
				10.删除弧          11.深度优先搜索遍历  12.广度优先搜索遍历\n\
				13.文件保存        14.文件读取          15.距离小于k的顶点集合\n\
				16.顶点间最短路径和长度  17.连通分量     18.返回多图菜单\n\
				0.停止操作\n\
				请输入【0~17】\n\n请输入你需要的操作：");
          scanf("%d", &op);  // 输入操作
          while (op) {
            switch (op) {
              case 1: {  // 创建图
                if (Lists.elem[number - 1].G.vexnum == 0) {
                  VertexType V[30];    // 暂时储存顶点的数据
                  KeyType VR[100][2];  // 暂时储存边的数据
                  int ans, i = 0;
                  printf("请输入结点数据【以-1为结尾】：");
                  do {
                    scanf("%d%s", &V[i].key, V[i].others);
                  } while (V[i++].key != -1);
                  printf("请输入弧数据【以-1为结尾】：");
                  i = 0;
                  do {
                    scanf("%d%d", &VR[i][0], &VR[i][1]);
                  } while (VR[i++][0] != -1);
                  ans = CreateCraph(Lists.elem[number - 1].G, V, VR);
                  if (ans == OK) {
                    printf("无向图创建成功！遍历为：\n");
                    for (i = 0; i < Lists.elem[number - 1].G.vexnum; i++) {
                      ArcNode* p =
                          Lists.elem[number - 1].G.vertices[i].firstarc;
                      printf("%d %s",
                             Lists.elem[number - 1].G.vertices[i].data.key,
                             Lists.elem[number - 1].G.vertices[i].data.others);
                      while (p) {
                        printf(" %d", p->adjvex);
                        p = p->nextarc;
                      }
                      printf("\n");
                    }
                    printf("\n");
                  } else
                    printf("无向图创建失败！\n");
                } else
                  printf("无向图图存在，无法创建！\n");
                getchar();
                getchar();
                system("cls");
                break;
              }
              case 2: {  // 销毁图
                if (Lists.elem[number - 1].G.vexnum != 0) {
                  DestroyGraph(Lists.elem[number - 1].G);  // 调用销毁图的函数
                  printf("无向图销毁成功！\n");
                } else
                  printf("无向图为空，无需销毁！\n");
                getchar();
                getchar();
                system("cls");
                break;
              }
              case 3: {  // 查找顶点
                if (Lists.elem[number - 1].G.vexnum != 0) {
                  int e, ans;
                  printf("请输入你想查找结点的关键字：");
                  scanf("%d", &e);
                  ans = LocateVex(Lists.elem[number - 1].G,
                                  e);  // 调用查找顶点的函数
                  if (ans == -1)
                    printf("查找失败！\n");
                  else
                    printf("对应结点为 %d,%s\n",
                           Lists.elem[number - 1].G.vertices[ans].data.key,
                           Lists.elem[number - 1].G.vertices[ans].data.others);
                } else
                  printf("无向图为空，查找失败！\n");
                getchar();
                getchar();
                system("cls");
                break;
              }
              case 4: {  // 顶点赋值
                if (Lists.elem[number - 1].G.vexnum != 0) {
                  VertexType e;
                  int ans, key;
                  printf("输入替换的顶点关键字：");
                  scanf("%d", &key);
                  printf("输入赋值：");
                  scanf("%d%s", &e.key, e.others);

                  ans = PutVex(Lists.elem[number - 1].G, key,
                               e);  // 调用查找顶点的函数
                  if (ans == OK) {
                    printf("赋值成功，深度搜索遍历为：");
                    BFSTraverse(Lists.elem[number - 1].G, visit);
                    printf("\n");
                  } else
                    printf("赋值操作失败！\n");

                } else
                  printf("无向图图为空，赋值操作失败！\n");
                getchar();
                getchar();
                system("cls");
                break;
              }
              case 5: {  // 获得第一邻接点
                if (Lists.elem[number - 1].G.vexnum != 0) {
                  int key, ans;
                  printf("请输入需要获得第一邻接顶点的关键字：");
                  scanf("%d", &key);
                  ans = FirstAdjVex(Lists.elem[number - 1].G,
                                    key);  // 调用求第一邻接点的函数
                  if (ans == -2) printf("顶点无第一邻接顶点\n");
                  if (ans == -1) printf("无该顶点!\n");
                  if (ans >= 0)
                    printf("%d结点的第一邻接点是%d,%s\n", key,
                           Lists.elem[number - 1].G.vertices[ans].data.key,
                           Lists.elem[number - 1].G.vertices[ans].data.others);
                } else
                  printf("无向图为空！\n");
                getchar();
                getchar();
                system("cls");
                break;
              }
              case 6: {  // 获得下一邻接点
                if (Lists.elem[number - 1].G.vexnum != 0) {
                  int key, relat, ans;
                  printf("输入待查找结点和相对结点：");
                  scanf("%d%d", &key, &relat);
                  ans = NextAdjVex(Lists.elem[number - 1].G, key,
                                   relat);  // 调用获取下一邻接点的函数
                  if (ans == -1)
                    printf("获取失败！\n");
                  else {
                    printf("%d相对于%d的顶点为%d,%s\n", key, relat,
                           Lists.elem[number - 1].G.vertices[ans].data.key,
                           Lists.elem[number - 1].G.vertices[ans].data.others);
                  }
                } else
                  printf("无向图为空，获取失败！\n");
                getchar();
                getchar();
                system("cls");
                break;
              }
              case 7: {  // 插入顶点
                if (Lists.elem[number - 1].G.vexnum != 0) {
                  VertexType e;
                  int ans, i;
                  printf("输入待插入的顶点数据：");
                  scanf("%d%s", &e.key, e.others);
                  ans = InsertVex(Lists.elem[number - 1].G,
                                  e);  // 调用插入节点的函数
                  if (ans == OK) {
                    printf("插入成功，遍历为：\n");
                    for (i = 0; i < Lists.elem[number - 1].G.vexnum; i++) {
                      ArcNode* p =
                          Lists.elem[number - 1].G.vertices[i].firstarc;
                      printf("%d %s",
                             Lists.elem[number - 1].G.vertices[i].data.key,
                             Lists.elem[number - 1].G.vertices[i].data.others);
                      while (p) {
                        printf(" %d", p->adjvex);
                        p = p->nextarc;
                      }
                      printf("\n");
                    }
                    printf("\n");
                  } else
                    printf("插入操作失败！\n");
                } else
                  printf("无向图为空，请先创建图！\n");
                getchar();
                getchar();
                system("cls");
                break;
              }
              case 8: {  // 删除顶点
                if (Lists.elem[number - 1].G.vexnum != 0) {
                  int e, ans, i;
                  printf("请输入删除结点：");
                  scanf("%d", &e);
                  ans = DeleteVex(Lists.elem[number - 1].G,
                                  e);  // 调用删除顶点的函数
                  if (ans == OK) {
                    printf("删除成功，遍历为：\n");
                    for (i = 0; i < Lists.elem[number - 1].G.vexnum; i++) {
                      ArcNode* p =
                          Lists.elem[number - 1].G.vertices[i].firstarc;
                      printf("%d %s",
                             Lists.elem[number - 1].G.vertices[i].data.key,
                             Lists.elem[number - 1].G.vertices[i].data.others);
                      while (p) {
                        printf(" %d", p->adjvex);
                        p = p->nextarc;
                      }
                      printf("\n");
                    }
                    printf("\n");
                  } else
                    printf("删除操作失败！\n");
                } else
                  printf("图为空，删除操作失败！\n");
                getchar();
                getchar();
                system("cls");
                break;
              }
              case 9: {  // 添加弧
                if (Lists.elem[number - 1].G.vexnum != 0) {
                  int ans, i, v, w;
                  printf("输入待插入的弧数据：");
                  scanf("%d%d", &v, &w);
                  ans = InsertArc(Lists.elem[number - 1].G, v,
                                  w);  // 调用添加弧的函数
                  if (ans == OK) {
                    printf("添加成功，遍历为：\n");
                    for (i = 0; i < Lists.elem[number - 1].G.vexnum; i++) {
                      ArcNode* p =
                          Lists.elem[number - 1].G.vertices[i].firstarc;
                      printf("%d %s",
                             Lists.elem[number - 1].G.vertices[i].data.key,
                             Lists.elem[number - 1].G.vertices[i].data.others);
                      while (p) {
                        printf(" %d", p->adjvex);
                        p = p->nextarc;
                      }
                      printf("\n");
                    }
                    printf("\n");
                  } else
                    printf("插入操作失败！\n");
                } else
                  printf("无向图为空，请先创建图！\n");
                getchar();
                getchar();
                system("cls");
                break;
              }
              case 10: {  // 删除弧
                if (Lists.elem[number - 1].G.vexnum != 0) {
                  int v, w, ans, i;
                  printf("请输入删除弧：");
                  scanf("%d%d", &v, &w);
                  ans = DeleteArc(Lists.elem[number - 1].G, v,
                                  w);  // 调用删除弧的函数
                  if (ans == OK) {
                    printf("删除成功，遍历为：\n");
                    for (i = 0; i < Lists.elem[number - 1].G.vexnum; i++) {
                      ArcNode* p =
                          Lists.elem[number - 1].G.vertices[i].firstarc;
                      printf("%d %s",
                             Lists.elem[number - 1].G.vertices[i].data.key,
                             Lists.elem[number - 1].G.vertices[i].data.others);
                      while (p) {
                        printf(" %d", p->adjvex);
                        p = p->nextarc;
                      }
                      printf("\n");
                    }
                    printf("\n");
                  } else
                    printf("删除操作失败！\n");
                } else
                  printf("图为空，删除操作失败！\n");
                getchar();
                getchar();
                system("cls");
                break;
              }
              case 11: {  // 深度遍历
                if (Lists.elem[number - 1].G.vexnum != 0) {
                  printf("深度优先搜索遍历：");
                  DFSTraverse(Lists.elem[number - 1].G,
                              visit);  // 调用深度优先遍历的函数
                  putchar('\n');
                } else
                  printf("遍历为空！\n");
                getchar();
                getchar();
                system("cls");
                break;
              }
              case 12: {  // 广度遍历
                if (Lists.elem[number - 1].G.vexnum != 0) {
                  printf("广度优先搜索遍历：");
                  BFSTraverse(Lists.elem[number - 1].G,
                              visit);  // 调用广度优先遍历的函数
                  putchar('\n');
                } else
                  printf("遍历为空！\n");
                getchar();
                getchar();
                system("cls");
                break;
              }
              case 13: {  // 文件保存
                if (Lists.elem[number - 1].G.vexnum != 0) {
                  char FileName[30];  // 目标文件名
                  printf("请输入要保存的文件名:\n");
                  scanf("%s", FileName);
                  if (SaveGraph(Lists.elem[number - 1].G, FileName) == OK)
                    printf("保存成功！\n");  // 调用保存文件的函数
                } else
                  printf("图为空，保存失败！\n");
                getchar();
                getchar();
                system("cls");
                break;
              }
              case 14: {  // 文件读取
                if (Lists.elem[number - 1].G.vexnum == 0) {
                  char FileName[30];  // 目标文件名
                  printf("请输入要读取的文件名:\n");
                  scanf("%s", FileName);
                  if (LoadGraph(Lists.elem[number - 1].G, FileName) == OK)
                    printf("读取成功！\n");  // 调用读取文件的函数
                } else
                  printf("图不为空，无法读取文件！\n");
                getchar();
                getchar();
                system("cls");
                break;
              }
              case 15: {  // 查找与顶点距离小于k的顶点
                if (Lists.elem[number - 1].G.vexnum !=
                    0) {  // 检查无向图是否为空
                  int v, k;
                  printf("请输入顶点的关键字及查找距离！\n");
                  scanf("%d%d", &v, &k);
                  printf("与顶点距离小于%d的顶点有", k);
                  VerticesSetLessThank(Lists.elem[number - 1].G, v,
                                       k);  // 调用函数查找与顶点距离小于k的顶点
                } else
                  printf("无向图为空!\n");
                getchar();
                getchar();
                system("cls");
                break;
              }
              case 16: {  // 计算两个顶点的最短路径
                if (Lists.elem[number - 1].G.vexnum != 0) {
                  int v, w, k;
                  printf("请输入两个顶点的关键字!\n");
                  scanf("%d%d", &v, &w);
                  k = ShortestPathLength(Lists.elem[number - 1].G, v,
                                         w);  // 调用计算两个顶点最短路径的函数
                  printf("这两个顶点间的最短路径是%d", k);
                } else
                  printf("无向图为空!\n");
                getchar();
                getchar();
                break;
              }
              case 17: {  // 求图的连通分量
                if (Lists.elem[number - 1].G.vexnum != 0) {
                  printf("图的连通分量有%d个！\n",
                         ConnectedComponentsNums(
                             Lists.elem[number - 1]
                                 .G));  // 调用求图的联通分量的函数
                } else
                  printf("无向图为空!\n");
                getchar();
                getchar();
                system("cls");
                break;
              }
              case 18: {
                system("cls");
                goto A;
                break;
              }
              default: {
                printf("输入错误，请重新输入！\n");
                getchar();
                getchar();
                system("cls");
              }
            }
            print2();
            scanf("%d", &op);
          }
        }
        case 5: {  // 遍历多图
          if (Lists.length == 0) {
            printf("多图无数据！\n");
            getchar();
            getchar();
            system("cls");
            break;
          }
          int i;
          for (i = 0; i < Lists.length; i++) {
            printf("%s ", Lists.elem[i].name);
            if (Lists.elem[i].G.vexnum == 0) {
              printf("无数据！\n");
              continue;
            } else {
              printf("广度优先遍历：");
              BFSTraverse(Lists.elem[i].G, visit);
              putchar('\n');
            }
          }
          getchar();
          getchar();
          system("cls");
          break;
        }
        case 6: {  // 清空多图
          if (Lists.length == 0) {
            printf("多图已为空！！\n");
            getchar();
            getchar();
            system("cls");
            break;
          }
          Lists.length = 0;
          printf("清空成功！\n");
          getchar();
          getchar();
          system("cls");
          break;
        }
        default: {
          printf("输入错误，请重新输入！\n");
          getchar();
          getchar();
          system("cls");
        }
      }
      print3();
      scanf("%d", &op);
    }
  }

  if (op == 0) {  // 停止操作
    printf("系统停止！\n");
    return 0;
  }

  printf("输入错误！\n");
  return 0;
}