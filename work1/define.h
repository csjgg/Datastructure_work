/* Linear Table On Sequence Structure */
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType;  // 数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef struct {  // 顺序表（顺序结构）的定义
  ElemType *elem;
  int length;
  int listsize;
} SqList;
/*-----page 19 on textbook ---------*/
status InitList(SqList &L);
status DestroyList(SqList &L);
status ClearList(SqList &L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L, int i, ElemType &e);
status LocateElem(SqList L, ElemType e);  // 简化过
status PriorElem(SqList L, ElemType cur, ElemType &pre_e);
status NextElem(SqList L, ElemType cur, ElemType &next_e);
status ListInsert(SqList &L, int i, ElemType e);
status ListDelete(SqList &L, int i, ElemType &e);
status ListTrabverse(SqList L);  // 简化过
status MaxSubArray(SqList L); // 求最大连续子数组和 初始条件是线性表L已存在且非空
status SubArrayNum(SqList L,ElemType k);  // 初始条件是线性表L已存在且非空, 操作结果是该数组中和为k的连续子数组的个数；
status SortList(SqList &L);  //初始条件是线性表L已存在；操作结果是将L由小到大排序；
void swap(ElemType &a, ElemType &b);
status  SaveList(SqList L, char FileName[]);    //将线性表L保存到文件FileName中
status  LoadList(SqList &L, char FileName[]);   //从文件FileName中读取线性表L
/*--------------------------------------------*/