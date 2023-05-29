#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int KeyType;
typedef struct {
  KeyType key;
  char others[20];
} TElemType;  // 二叉树结点类型定义

typedef struct BiTNode {  // 二叉链表结点的定义
  TElemType data;
  struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 函数声明

void visit(BiTree t);  // 用于遍历输出
void CreTree(BiTree &T, TElemType definition[], int tmp[]);  // 用于创建二叉树
status CreateBiTree(BiTree &T, TElemType definition[]);  // 用于创建二叉树
status ClearBiTree(BiTree &T);             // 用于销毁二叉树
int BiTreeDepth(BiTree T);                 // 用于求二叉树深度
BiTNode *LocateNode(BiTree T, KeyType e);  // 用于查找结点
status Assign(BiTree &T, KeyType e, TElemType value);  // 用于修改结点
BiTNode *GetSibling(BiTree T, KeyType e);  // 用于求结点的兄弟结点
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);  // 用于插入结点
BiTNode *Getfather(BiTree T, KeyType e);  // 用于求结点的父结点
status DeleteNode(BiTree &T, KeyType e);  // 用于删除结点
status PreOrderTraverse(BiTree T, void (*visit)(BiTree));  // 用于先序遍历
status InOrderTraverse(BiTree T, void (*visit)(BiTree));   // 用于中序遍历
status PostOrderTraverse(BiTree T, void (*visit)(BiTree));  // 用于后序遍历
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));  // 用于层序遍历
status SaveBiTree(BiTree T, char FileName[]);   // 用于保存二叉树
status LoadBiTree(BiTree &T, char FileName[]);  // 用于加载二叉树
int MaxPathSum(BiTree T);  // 用于求二叉树中的最大路径和
BiTree LowestCommonAncestor(BiTree T, int e1,
                            int e2);  // 用于求二叉树中两个结点的最近公共祖先
int InvertTree(BiTree T);  // 用于求二叉树的镜像
