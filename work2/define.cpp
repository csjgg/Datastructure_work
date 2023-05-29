#include "define.h"
// 函数定义

// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
status InitList(LinkList &L) {
  if (L == NULL) {  // 不存在
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    return OK;
  } else {  // 存在
    return INFEASIBLE;
  }
}

// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
status DestroyList(LinkList &L) {
  if (L == NULL) {  //不存在
    return INFEASIBLE;
  } else {
    LinkList tmp;
    while (L->next != NULL) {  // 递归地找下一个，并依次free掉
      tmp = L->next;
      free(L);
      L = tmp;
    }
    free(L);  // free掉最后一个
    L = NULL;
    return OK;
  }
}

// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
status ClearList(LinkList &L) {
  if (L) {  //存在
    LinkList tmp;
    LinkList temp;
    tmp = L->next;  // 保留头节点，从第二个开始
    L->next = NULL;
    if(tmp == NULL){
      return ERROR;
    }
    while (tmp->next) {  //依次销毁
      temp = tmp->next;
      free(tmp);
      tmp = temp;
    }
    free(tmp);
    tmp = NULL;
    return OK;
  } else {
    return INFEASIBLE;
  }
}

// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
status ListEmpty(LinkList L) {
  if (L) {
    if (L->next) {
      return FALSE;
    } else {
      return TRUE;
    }
  } else {
    return INFEASIBLE;
  }
}

// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
int ListLength(LinkList L) {
  if (L) {
    int i = 0;
    LinkList tmp;
    tmp = L;
    while (tmp->next) {  //依次递归数有几个
      i++;
      tmp = tmp->next;
    }
    return i;
  } else {
    return INFEASIBLE;
  }
}

// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status GetElem(LinkList L, int i, ElemType &e) {
  if (L) {
    LinkList tmp = L;
    int num = 0;
    while (tmp->next) {  //递归遍历
      num++;
      tmp = tmp->next;
      if (i == num) {  //找到了
        e = tmp->data;
        return OK;
      }
    }
    return ERROR;
  } else {
    return INFEASIBLE;
  }
}

// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
status LocateElem(LinkList L, ElemType e) {
  if (L) {  // 存在
    LinkList tmp = L;
    int num = 0;
    while (tmp->next) {  // 递归遍历
      num++;
      tmp = tmp->next;
      if (tmp->data == e) {  //找到
        return num;
      }
    }
    return ERROR;
  } else {
    return INFEASIBLE;
  }
}

// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status PriorElem(LinkList L, ElemType e, ElemType &pre) {
  if (L) {
    LinkList tmp = L->next;
    while (tmp && tmp->next) {  //递归遍历
      L = tmp;
      tmp = tmp->next;
      if (tmp->data == e) {  // 找到
        pre = L->data;
        return OK;
      }
    }
    return ERROR;
  } else {
    return INFEASIBLE;
  }
}

// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status NextElem(LinkList L, ElemType e, ElemType &next) {
  if (L) {  // 线性表存在
    LinkList tmp = L;
    while (tmp->next) {
      tmp = tmp->next;
      if (tmp->data == e) {
        if (tmp->next) {
          next = tmp->next->data;  // 看后继
          return OK;
        } else {
          return ERROR;
        }
      }
    }
    return ERROR;
  } else {
    return INFEASIBLE;
  }
}

// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status ListInsert(LinkList &L, int i, ElemType e) {
  if (L) {
    LinkList tmp = L;
    int num = 0;
    while (tmp->next) {
      num++;
      if (num == i) {  // 一般情况
        LinkList temp = (LinkList)malloc(sizeof(LNode));
        temp->next = tmp->next;  // 先连上后面
        temp->data = e;
        tmp->next = temp;  // 再连上前面
        return OK;
      }
      tmp = tmp->next;
    }
    if (num + 1 == i) {  // 特殊情况
      LinkList temp = (LinkList)malloc(sizeof(LNode));
      temp->next = tmp->next;
      temp->data = e;
      tmp->next = temp;
      return OK;
    }
    return ERROR;
  } else {
    return INFEASIBLE;
  }
}

// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status ListDelete(LinkList &L, int i, ElemType &e) {
  if (L) {  // 存在
    LinkList tmp = L;
    int num = 0;
    while (tmp->next) {
      num++;
      if (num == i) {   //找到第i个
        LinkList temp = tmp->next->next;
        e = tmp->next->data;
        free(tmp->next);
        tmp->next = temp;
        return OK;
      }
      tmp = tmp->next;
    }
    return ERROR;
  } else {
    return INFEASIBLE;
  }
}

// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
status ListTraverse(LinkList L) {
  if (L) {
    L = L->next;
    while (L && L->next) {  //依次遍历
      printf("%d ", L->data);
      L = L->next;
    }
    if (L != NULL) printf("%d", L->data);
    return OK;
  } else {
    return INFEASIBLE;
  }
}

// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
status SaveList(LinkList L, char FileName[]) {
  if (L) {
    FILE *fp = fopen(FileName, "w");
    L = L->next;
    while (L && L->next) {  // 仍为依次遍历，只是写入文件
      fprintf(fp, "%d ", L->data);
      L = L->next;
    }
    if (L != NULL) fprintf(fp, "%d\n", L->data);
    fclose(fp);
    return OK;
  } else {
    return INFEASIBLE;
  }
}

// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
status LoadList(LinkList &L, char FileName[]) {
  if (L == NULL) {
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    LinkList tmp = L;
    FILE *fp = fopen(FileName, "r");
    if(fp == NULL){
      return ERROR;
    }
    int elem;
    while (fscanf(fp, "%d", &elem) != EOF) {   // 依次读入即可
      tmp->next = (LinkList)malloc(sizeof(LNode));
      tmp = tmp->next;
      tmp->next = NULL;
      tmp->data = elem;
    }
    fclose(fp);
    return OK;
  } else {
    return INFEASIBLE;
  }
}

// 逆置线性表
status reverseList(LinkList &L){
  if(L){
    LinkList tmp = L->next;
    L->next = NULL;
    while(tmp){
      LinkList temp = tmp->next;
      tmp->next = L->next;
      L->next = tmp;
      tmp = temp;
    }
    return OK;
  }else{
    return INFEASIBLE;
  }
}

// 删除倒数第n个元素
status RemoveNthFromEnd(LinkList L,int n){
  if(L){
    LinkList tmp = L->next;
    int num = 0;
    while(tmp){
      num++;
      tmp = tmp->next;
    }
    if(num < n){
      return ERROR;
    }else{
      tmp = L;
      for(int i = 0;i < num - n;i++){
        tmp = tmp->next;
      }
      LinkList temp = tmp->next->next;
      free(tmp->next);
      tmp->next = temp;
      return OK;
    }
  }else{
    return INFEASIBLE;
  }
}
// 从小到大排序
status sortList(LinkList L){
  if(L){
    LinkList tmp = L->next;
    while(tmp){
      LinkList temp = tmp->next;
      while(temp){
        if(tmp->data > temp->data){
          ElemType e = tmp->data;
          tmp->data = temp->data;
          temp->data = e;
        }
        temp = temp->next;
      }
      tmp = tmp->next;
    }
    return OK;
  }else{
    return INFEASIBLE;
  }
}
