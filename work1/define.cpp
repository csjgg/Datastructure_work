#include "define.h"

// function definition
status InitList(SqList &L) {
  L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
  if (!L.elem) exit(OVERFLOW);
  L.length = 0;
  L.listsize = LIST_INIT_SIZE;
  return OK;
}

status DestroyList(SqList &L) {  //销毁线性表
  if (L.elem != NULL) {    // 线性表存在
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
  } else {  // 线性表不存在
    return INFEASIBLE;
  }
}

status ClearList(SqList &L) {
  if (L.elem != NULL) {  // 线性表存在
    L.length = 0;
    return OK;
  } else {
    return INFEASIBLE;
  }
}

status ListEmpty(SqList L) {  // 判断线性表是否为空
  if (L.elem != NULL) {
    if (L.length == 0) {  // 线性表为空
      return TRUE;
    } else {
      return FALSE;
    }
  } else {   // 线性表不存在
    return INFEASIBLE;
  }
}

status ListLength(SqList L) {   // 返回线性表的长度
  if (L.elem) {  // 线性表存在
    return L.length;
  } else {
    return INFEASIBLE;
  }
}
status GetElem(SqList L, int i, ElemType &e) {  // 用e返回L中第i个数据元素的值
  if (L.elem) {   // 线性表存在
    if (i > L.length || i < 1) {
      return ERROR;
    } else {
      e = L.elem[i - 1];
      return OK;
    }
  } else {
    return INFEASIBLE;
  }
}
status LocateElem(SqList L, ElemType e) {  
  if (L.elem) {
    int i;
    for (i = 0; i < L.length; i++) {
      if (L.elem[i] == e) {
        return i + 1;
      }
    }
    return 0;
  } else {
    return INFEASIBLE;
  }
}
status PriorElem(SqList L, ElemType cur, ElemType &pre_e) {  // 返回cur的前驱
  if (L.elem) {
    int i;
    for (i = 0; i < L.length; i++) {
      if (L.elem[i] == pre_e) {  // 找到cur
        if (i == 0) {
          return ERROR;  // cur为第一个元素
        } else {
          pre_e = L.elem[i - 1];
          return OK; 
        }
      }
    }
    return ERROR;     // 未找到cur
  } else {
    return INFEASIBLE;
  }
}
status NextElem(SqList L, ElemType cur, ElemType &next_e) {  // 返回cur的后继
  if (L.elem) {
    int i;
    for (i = 0; i < L.length; i++) {
      if (L.elem[i] == cur) {
        if (i == L.length - 1) {  // cur为最后一个元素
          return ERROR;
        } else {  // cur不是最后一个元素
          next_e = L.elem[i + 1];
          return OK;
        }
      }
    }
    return ERROR;
  } else {
    return INFEASIBLE;
  }
}
status ListInsert(SqList &L, int i, ElemType e) { // 在第i个位置插入元素e
  if (L.elem) {     // 线性表存在
    if (i < 1 || i > L.length + 1) {
      return ERROR;
    } else {
      if (L.length == L.listsize) {  // 线性表已满
        ElemType *tem =
            (ElemType *)realloc(L.elem, sizeof(ElemType) * L.listsize * 2);
        if (tem) {
          L.elem = tem;  // 重新分配内存
          L.listsize *= 2;
        }
      }

      int t;
      if (L.length != 0 && i != L.length + 1) {  // 插入位置不在表尾
        for (t = L.length - 1; t >= i - 1; t--) {  // 将插入位置后的元素后移
          L.elem[t + 1] = L.elem[t];
        }
        L.elem[i - 1] = e;
      } else {
        L.elem[i - 1] = e;
      }
      L.length++;
      return OK;
    }
  } else {  // 线性表不存在
    return INFEASIBLE;
  }
}
status ListDelete(SqList &L, int i, ElemType &e) {  // 删除第i个元素
  if (L.elem) {
    if (L.length >= i && i > 0) {  // 线性表存在
      e = L.elem[i - 1];
      for (int j = i - 1; j < L.length - 1; j++) {  // 将删除位置后的元素前移
        L.elem[j] = L.elem[j + 1];
      }
      L.length--;
      return OK;
    } else {
      return ERROR;
    }
  } else {
    return INFEASIBLE;  // 线性表不存在
  }
}
status ListTrabverse(SqList L) {  // 遍历线性表
  int i;
  printf("\n-----------all elements -----------------------\n");
  for (i = 0; i < L.length; i++) printf("%d ", L.elem[i]);
  printf("\n------------------ end ------------------------\n");
  return L.length;
}

status MaxSubArray(SqList L) {  // 求最大子序列和
  if (L.elem == NULL) return INFEASIBLE;
  int i, j, k, max, sum;
  int start, end;
  max = 0;
  for (i = 0; i < L.length; i++) {  // 简单遍历
    sum = 0;
    for (j = i; j < L.length; j++) {  // 简单遍历
      sum += L.elem[j];   // 求和
      if (sum > max) {  // 比较
        max = sum;
        start = i;
        end = j;
      }
    }
  }
  printf("最大子序列和为%d，其下标为%d到%d\n", max, start, end);
  return OK;
}

status SubArrayNum(SqList L, ElemType k) {  // 求和为k的子序列个数
  if (L.elem == NULL) return INFEASIBLE;
  int i, j, sum;
  int count = 0;
  for (i = 0; i < L.length; i++) {  // 简单遍历
    sum = 0;
    for (j = i; j < L.length; j++) {
      sum += L.elem[j];
      if (sum == k) {  // 比较
        count++;
      }
    }
  }
  printf("和为%d的子序列个数为%d\n", k, count);
  return OK;
}

status SortList(SqList &L) {
  if (L.elem == NULL) return INFEASIBLE;  // 线性表不存在
  int i, j, min;  
  for (i = 0; i < L.length; i++) {  // 简单遍历
    min = i;
    for (j = i + 1; j < L.length; j++) {  // 简单遍历
      if (L.elem[j] < L.elem[min]) {
        min = j;
      }
    }
    if (min != i) {
      swap(L.elem[i], L.elem[min]);
    }
  }
  return OK;
}

void swap(ElemType &a, ElemType &b) {  // 交换两个元素
  ElemType temp = a;
  a = b;
  b = temp;
}

status  SaveList(SqList L, char FileName[]) {  // 保存线性表
	if (!L.elem)
		return INFEASIBLE;
	else {
		FILE *fp;
		fp = fopen(FileName, "w");  // 打开文件
		for (int i = 0; i < L.length; i++)
			fprintf(fp, "%d ", L.elem[i]);
		fclose(fp);
		return OK;
	}
}

status  LoadList(SqList &L, char FileName[]) {  // 读取线性表
	if (L.elem)  // 线性表已存在
		return INFEASIBLE;
	else {
		FILE *fp;
		fp = fopen(FileName, "r");
    if(fp == NULL) return ERROR;
		L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
		int len = 0;
		while (!feof(fp))
			fscanf(fp, "%d", &L.elem[len++]);
		L.length = len - 1;
		fclose(fp);
		return OK;
	}
}
