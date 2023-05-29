#include "define.h"

// 根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
void CreTree(BiTree &T, TElemType definition[], int tmp[]) {
  int i = 0;
  for (i = 0; i < 50; i++) {  // 找到第一个未被访问的结点
    if (tmp[i] == 0) {
      break;
    }
  }
  tmp[i] = 1;
  if (strcmp(definition[i].others, "null")) {  // 如果不是空结点
    T = (BiTree)malloc(sizeof(BiTNode));
    memcpy(&T->data, &definition[i], sizeof(TElemType));  // 复制结点数据
    CreTree(T->lchild, definition, tmp);  // 递归创建左子树
    CreTree(T->rchild, definition, tmp);  // 递归创建右子树
  } else {
    T = NULL;
  }
}
status CreateBiTree(BiTree &T, TElemType definition[]) {
  if (T) {
    return ERROR;
  }
  int tmp[50];
  int i = 0;
  while (definition[i].key != -1) {  // 检查是否有重复的key
    if (i == 0) {
      tmp[0] = definition[i].key;
    } else {  
      for (int j = 0; j < i; j++) {
        if (definition[i].key && tmp[j] == definition[i].key) {
          return ERROR;  // 如果有重复的key，返回ERROR
        }
      }
      tmp[i] = definition[i].key;
    }
    i++;
  }
  int tmp2[50] = {0};
  CreTree(T, definition, tmp2);  // 创建二叉树
  return OK;
}

// 将二叉树设置成空，并删除所有结点，释放结点空间
status ClearBiTree(BiTree &T) {
  if (T) {
    ClearBiTree(T->lchild);  // 递归删除左子树
    ClearBiTree(T->rchild);  // 递归删除右子树
    free(T); 
    T = NULL;
  } else {
  }
  return OK;
}

// 求二叉树T的深度
int BiTreeDepth(BiTree T) {
  if (T) {
    int left = BiTreeDepth(T->lchild);    // 递归求左子树
    int right = BiTreeDepth(T->rchild);  //递归求右子树
    if (left > right) {
      return left + 1;
    } else {
      return right + 1;
    }
  } else {
    return 0;
  }
}

// 查找结点
BiTNode *LocateNode(BiTree T, KeyType e) {
  if (T) {
    if (T->data.key == e) {
      return T;
    }
    BiTree tmp;
    if ((tmp = LocateNode(T->lchild, e))) {  //递归在左子树中查找
      return tmp;
    } else if ((tmp = LocateNode(T->rchild, e))) {  //递归在右子树中查找
      return tmp;
    }
  } else {
    return NULL;
  }
  return NULL;
}

// 实现结点赋值
status Assign(BiTree &T, KeyType e, TElemType value) {
  BiTree tmp;
  BiTree tmp2;
  tmp = LocateNode(T, e);
  tmp2 = LocateNode(T, value.key);
  if (tmp2 && tmp2 != tmp) {  //说明没找到
    return ERROR;
  }
  if (tmp) {  //找到，改写
    memcpy(&tmp->data, &value, sizeof(TElemType));
    return OK;
  } else {
    return ERROR;
  }
}

// 实现获得兄弟结点
BiTNode *GetSibling(BiTree T, KeyType e) {
  if (T) {
    if (T->data.key == e) {
      return NULL;
    }
    if (T->lchild && T->rchild) {  //两个孩子都存在，此处为单独判断根节点
      if (T->lchild->data.key == e) {
        return T->rchild;
      }
      if (T->rchild->data.key == e) {
        return T->lchild;
      }
    }
    BiTree tmp = GetSibling(T->lchild, e);  // 判断完成，递归寻找左子树和右子树
    if (tmp) {
      return tmp;
    } else {
      tmp = GetSibling(T->rchild, e);
      return tmp;
    }
  } else {
    return NULL;
  }
}

// 插入结点
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c) {
  BiTree tmp;
  BiTree tmp3 = LocateNode(T, c.key);
  tmp = LocateNode(T, e);
  if (tmp3) {
    return ERROR;
  }
  if (LR == -1) {
    tmp = (BiTree)malloc(sizeof(BiTNode));
    memcpy(&tmp->data, &c, sizeof(TElemType));
    tmp->rchild = T;
    T = tmp;
    T->lchild = NULL;
    return OK;
  }  // 以上为处理根节点
  if (tmp == NULL) {
    return ERROR;
  }
  BiTree tmp2;  //非根节点，按要求处理
  if (LR == 1) {
    tmp2 = (BiTree)malloc(sizeof(BiTNode));
    memcpy(&tmp2->data, &c, sizeof(TElemType));
    tmp2->rchild = tmp->rchild;
    tmp2->lchild = NULL;
    tmp->rchild = tmp2;
    return OK;
  } else if (LR == 0) {
    tmp2 = (BiTree)malloc(sizeof(BiTNode));
    memcpy(&tmp2->data, &c, sizeof(TElemType));
    tmp2->rchild = tmp->lchild;
    tmp2->lchild = NULL;
    tmp->lchild = tmp2;
    return OK;
  }
  return OK;
}

// 删除节点
BiTNode *Getfather(BiTree T, KeyType e) {  //删除节点需要先找到对应节点的父节点，所以单独写出
  if (T) {
    if (T->data.key == e) {  //根节点
      return NULL;
    }
    if (T->lchild && T->rchild) {
      if (T->lchild->data.key == e) {
        return T;
      }
      if (T->rchild->data.key == e) {
        return T;
      }
    } else if (T->lchild) {
      if (T->lchild->data.key == e) {
        return T;
      }
    } else if (T->rchild) {
      if (T->rchild->data.key == e) {
        return T;
      }
    }  // 以上为特殊情况
    //一下不特殊，直接遍历去找
    BiTree tmp = Getfather(T->lchild, e);
    if (tmp) {
      return tmp;
    } else {
      tmp = Getfather(T->rchild, e);
      return tmp;
    }
  } else {
    return NULL;
  }
}
status DeleteNode(BiTree &T, KeyType e) {
  BiTree tmp2;
  if (T->data.key == e) {  //删除根节点
    if (T->lchild && T->rchild) {
      tmp2 = T->lchild;
      while (tmp2 && tmp2->rchild) {  //找到左子树的最右节点
        tmp2 = tmp2->rchild;
      }
      tmp2->rchild = T->rchild;
      tmp2 = T->lchild;    
      free(T);
      T = tmp2;
      return OK;
//左右子树都存在，将左子树的最右节点的右孩子指向右子树，然后将左子树作为根节点
    } else if (T->lchild) {
      tmp2 = T->lchild;
      free(T);
      T = tmp2;
    } else {
      tmp2 = T->rchild;
      free(T);
      T = tmp2;
    }
  }
  BiTree tmp = Getfather(T, e);  //找到父节点
  if (tmp) {
    if (tmp->lchild && tmp->lchild->data.key == e) {  //判断是左孩子还是右孩子
      if (tmp->lchild->lchild) {  //左子树存在
        if (tmp->lchild->rchild) {  //左右子树都存在
          tmp2 = tmp->lchild->lchild;
          while (tmp2->rchild) {
            tmp2 = tmp2->rchild;
          }
          tmp2->rchild = tmp->lchild->rchild;
          tmp2 = tmp->lchild->lchild;
          free(tmp->lchild);
          tmp->lchild = tmp2;
          return OK;
        } else {  //左子树存在，右子树不存在
          tmp2 = tmp->lchild->lchild;
          free(tmp->lchild);
          tmp->lchild = tmp2;
          return OK;
        }
      } else {
        if (tmp->lchild->rchild) {  //左子树不存在，右子树存在
          tmp2 = tmp->lchild->rchild;
          free(tmp->lchild);
          tmp->lchild = tmp2;
          return OK;
        } else {  //左右子树都不存在
          free(tmp->lchild);
          tmp->lchild = NULL;
          return OK;
        }
      }

    } else {
      if (tmp->rchild->lchild) {  //判断是左孩子还是右孩子
        if (tmp->rchild->rchild) {  //左右子树都存在
          tmp2 = tmp->rchild->lchild;
          while (tmp2->rchild) {
            tmp2 = tmp2->rchild;
          }
          tmp2->rchild = tmp->rchild->rchild;
          tmp2 = tmp->rchild->lchild;
          free(tmp->rchild);
          tmp->rchild = tmp2;
          return OK;
        } else {  //只有左子树存在
          tmp2 = tmp->rchild->lchild;
          free(tmp->rchild);
          tmp->rchild = tmp2;
          return OK;
        }
      } else {  //左子树不存在
        if (tmp->rchild->rchild) {  //右子树存在
          tmp2 = tmp->rchild->rchild;
          free(tmp->rchild);
          tmp->rchild = tmp2;
          return OK;
        } else {  //左右子树都不存在
          free(tmp->rchild);
          tmp->rchild = NULL;
          return OK;
        }
      }
    }

  } else {  //没有找到父节点，说明没有这个节点
    return ERROR;
  }
}

void visit(BiTree t) { printf("%d %s\n", t->data.key, t->data.others); }

// 先序遍历二叉树T
status PreOrderTraverse(BiTree T, void (*visit)(BiTree)) {
  if (T) {
    visit(T);
    PreOrderTraverse(T->lchild, visit);
    PreOrderTraverse(T->rchild, visit);
  }
  return OK;
}

// 中序遍历二叉树T
status InOrderTraverse(BiTree T, void (*visit)(BiTree)) {
  if (T) {
    InOrderTraverse(T->lchild, visit);
    visit(T);
    InOrderTraverse(T->rchild, visit);
  }
  return OK;
}

// 后序遍历二叉树T
status PostOrderTraverse(BiTree T, void (*visit)(BiTree)) {
  if (T) {
    PostOrderTraverse(T->lchild, visit);
    PostOrderTraverse(T->rchild, visit);
    visit(T);
  }
  return OK;
}

// 按层遍历二叉树T
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree)) {
  int begin, end;
  begin = end = 0;
  BiTree arr[50];
  if (T == NULL) {  //如果树为空，返回错误
    return ERROR;
  }
  arr[end++] = T;
  while (begin != end) {  //如果begin等于end，说明队列为空，结束循环
    visit(arr[begin]);
    if (arr[begin]->lchild) {
      arr[end++] = arr[begin]->lchild;
    }
    if (arr[begin]->rchild) {
      arr[end++] = arr[begin]->rchild;
    }
    begin++;
  }
  return OK;
}

// 将二叉树的结点数据写入到文件FileName中
status SaveBiTree(BiTree T, char FileName[]) {
  FILE *fd = fopen(FileName, "w");
  if (T) {
    BiTree p = T;
    BiTree stack[50];  //定义一个栈 
    int num = 0;
    while (NULL != p || num > 0) {  //如果p不为空或者栈不为空，循环
      while (NULL != p) {
        fprintf(fd, "%d %s\n", p->data.key, p->data.others);  //写入文件
        stack[num++] = p;
        p = p->lchild;
      }
      if (p == NULL) {   // 特殊情况，写入一个null
        fprintf(fd, "%d %s\n", 0, "null");
      }
      num--;
      p = stack[num];
      p = p->rchild;
    }
    fprintf(fd, "%d %s\n", 0, "null");  
    fclose(fd);
    return OK;
  } else {
    return ERROR;
  }
}
// 读入文件FileName的结点数据，创建二叉树
status LoadBiTree(BiTree &T, char FileName[]) {
  FILE *fd = fopen(FileName, "r");
  BiTree stack[50];  // 也是需要一个栈
  int top = 0;
  int key;
  char others[20];  
  if (T == NULL) {
    BiTree tmp;
    BiTree node;
    T = (BiTree)malloc(sizeof(BiTNode));
    T->lchild = NULL;
    T->rchild = NULL;
    fscanf(fd, "%d %s", &key, others);
    T->data.key = key;
    strcpy(T->data.others, others);
    stack[top] = T;
    tmp = T;
    int lr = 0;
    while (top >= 0) {  // 栈不空，依次读取，并写入栈，
      if (fscanf(fd, "%d %s", &key, others) == EOF) {
        break;
      }
      if (strcmp(others, "null") == 0) {
        if (lr == 0) {
          tmp->lchild = NULL;
          lr = 1;
        } else {
          if (tmp->rchild) {
          } else {
            tmp->rchild = NULL;
          }
          top--;
          if (top < 0) {
            break;
          }
          tmp = stack[top];
          lr = 1;
        }

      } else {
        node = (BiTree)malloc(sizeof(BiTNode));
        node->data.key = key;
        strcpy(node->data.others, others);
        node->lchild = NULL;
        node->rchild = NULL;
        if (lr == 0) {
          tmp->lchild = node;
          stack[++top] = tmp->lchild;
          tmp = tmp->lchild;
        } else {
          tmp->rchild = node;
          stack[++top] = tmp->rchild;
          tmp = tmp->rchild;
          lr = 0;
        }
      }
    }
    return OK;
  } else {
    return ERROR;
  }
}

// 二叉树从根节点开始的最大路径和
int MaxPathSum(BiTree T) {
  int max = 0;
  int tmp = 0;
  if (T) {
    tmp = T->data.key;
    max = tmp;
    if (T->lchild) {
      tmp += MaxPathSum(T->lchild);  //递归寻找
    }
    if (T->rchild) {
      max += MaxPathSum(T->rchild);
    }
    if (tmp > max) {
      max = tmp;
    }
  }
  return max;
}

// 两节点的最近公共祖先
BiTree LowestCommonAncestor(BiTree T, int e1, int e2) {
  if (T) {
    if (T->data.key == e1 || T->data.key == e2) {
      return T;
    }    // 也是用到递归
    BiTree l = LowestCommonAncestor(T->lchild, e1, e2);
    BiTree r = LowestCommonAncestor(T->rchild, e1, e2);
    if (l && r) {
      return T;
    } else if (l) {
      return l;
    } else if (r) {
      return r;
    } else {
      return NULL;
    }
  } else {
    return NULL;
  }
}

// 翻转二叉树，互换所有左右节点
int InvertTree(BiTree T) {
  if (T) {
    BiTree tmp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = tmp;
    InvertTree(T->lchild);
    InvertTree(T->rchild);
  }
  return OK;
}
