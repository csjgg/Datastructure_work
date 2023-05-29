#include "define.h"

// main
int main(void)
{
  LinkList arr[30] = {NULL};
  int num = 0;
  int statuss;
  char filename[20];
  int len;
  int i;
  int e;
  int n;
  int op = 1;
  while (op)
  {
    // system("cls");
    printf("\n\n");
    // 打印菜单
    printf("      Menu for Linear Table On List Structure \n");
    printf("-------------------------------------------------\n");
    printf("    	  1. 初始化                7. 查找元素位置\n");
    printf("    	  2. 摧毁                  8. 求元素的前驱\n");
    printf("    	  3. 清空                  9. 求元素后继 \n");
    printf("    	  4. 判断是否为空          10. 插入元素\n");
    printf("    	  5. 求长度                11. 删除元素\n");
    printf("    	  6. 获取元素              12. 打印元素\n");
    printf("    	  13. 逆置链表             14. 删除倒数第n个元素\n");
    printf("    	  15. 元素排序             16. 保存到文件\n");
    printf("    	  17. 从文件读取           18. 切换链表\n");
    printf("    	  0. 退出\n");
    printf("-------------------------------------------------\n");
    printf("    请选择你的操作[0~18]:");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
      // 创建线性表
      if (InitList(arr[num]) == OK)
        printf("线性表创建成功！\n");
      else
        printf("线性表已经存在\n");
      getchar();
      getchar();
      break;
    case 2:
      // 销毁线性表
      if (DestroyList(arr[num]) == OK)
      {
        printf("线性表销毁成功！\n");
        arr[num] = NULL;
      }
      else
      {
        printf("线性表不存在\n");
      }
      getchar();
      getchar();
      break;
    case 3:
      // 清空线性表
      if (ClearList(arr[num]) == OK)
      {
        printf("线性表清空成功！\n");
      }
      else if (ClearList(arr[num]) == ERROR)
      {
        printf("线性表为空\n");
      }
      else
      {
        printf("线性表不存在\n");
      }
      getchar();
      getchar();
      break;
    case 4:
      // 判断线性表是否为空
      if (ListEmpty(arr[num]) == TRUE)
      {
        printf("线性表为空！\n");
      }
      else if (ListEmpty(arr[num]) == FALSE)
      {
        printf("线性表不为空！\n");
      }
      else
      {
        printf("线性表不存在！\n");
      }
      getchar();
      getchar();
      break;
    case 5:
      // 求线性表长度
      len;
      if ((len = ListLength(arr[num])) == -1)
      {
        printf("线性表不存在！\n");
      }
      else
      {
        printf("线性表长度为%d\n", len);
      }
      getchar();
      getchar();
      break;
    case 6:
      // 获取元素
      printf("输入要获取的元素位置：");
      scanf("%d", &i);
      statuss = GetElem(arr[num], i, e);
      if (statuss == OK)
      {
        printf("元素是：%d\n", e);
      }
      else if (statuss == ERROR)
      {
        printf("位置错误\n");
      }
      else
      {
        printf("线性表不存在！\n");
      }
      getchar();
      getchar();
      break;
    case 7:
      // 获取元素位置
      int elem;
      printf("请输入想获取位置的元素：");
      scanf("%d", &elem);
      statuss = LocateElem(arr[num], elem);
      if (statuss == ERROR)
      {
        printf("未找到该元素\n");
      }
      else if (statuss == INFEASIBLE)
      {
        printf("线性表不存在！\n");
      }
      else
      {
        printf("位置是：%d\n", statuss);
      }
      getchar();
      getchar();
      break;
    case 8:
      // 获取元素前驱
      int pre, pre_v;
      printf("请输入想获取前驱的元素：");
      scanf("%d", &pre);
      statuss = PriorElem(arr[num], pre, pre_v);
      if (statuss == ERROR)
      {
        printf("未找到该元素\n");
      }
      else if (statuss == INFEASIBLE)
      {
        printf("线性表不存在！\n");
      }
      else
      {
        printf("前驱是：%d\n", pre_v);
      }
      getchar();
      getchar();
      break;
    case 9:
      // 获取元素后继
      int next, next_v;
      printf("请输入想获取后继的元素：");
      scanf("%d", &next);
      statuss = NextElem(arr[num], next, next_v);
      if (statuss == ERROR)
      {
        printf("未找到该元素\n");
      }
      else if (statuss == INFEASIBLE)
      {
        printf("线性表不存在！\n");
      }
      else
      {
        printf("后继是：%d\n", next_v);
      }
      getchar();
      getchar();
      break;
    case 10:
      // 插入元素
      printf("输入要插入的元素位置：");
      scanf("%d", &i);
      printf("输入要插入的元素：");
      scanf("%d", &e);
      if (ListInsert(arr[num], i, e) == OK)
      {
        printf("插入成功！\n");
      }
      else
      {
        printf("插入失败！\n");
      }
      getchar();
      getchar();
      break;
    case 11:
      // 删除元素
      printf("输入要删除的元素位置：");
      scanf("%d", &i);
      int de_v;
      if (ListDelete(arr[num], i, de_v) == OK)
      {
        printf("删除成功！删除的值为%d\n", de_v);
      }
      else
      {
        printf("删除失败！\n");
      }
      getchar();
      getchar();
      break;
    case 12:
      // 打印元素
      if (!ListTraverse(arr[num]))
        printf("线性表是空表！\n");
      getchar();
      getchar();
      break;
    case 13:
      // 逆置线性表
      statuss = reverseList(arr[num]);
      if (statuss == OK)
      {
        printf("已逆置\n");
      }
      else
      {
        printf("线性表不存在\n");
      }
      getchar();
      getchar();
      break;
    case 14:
      // 删除倒数第n个元素
      printf("输入要删除的元素序号：");
      scanf("%d", &n);
      statuss = RemoveNthFromEnd(arr[num], n);
      if (statuss == ERROR)
      {
        printf("位置序号错误\n");
      }
      else if (statuss == INFEASIBLE)
      {
        printf("线性表不存在\n");
      }
      else
      {
        printf("元素已删除\n");
      }
      getchar();
      getchar();
      break;
    case 15:
      // 线性表排序
      statuss = sortList(arr[num]);
      if (statuss == OK)
      {
        printf("排序完成\n");
      }
      else
      {
        printf("线性表不存在\n");
      }
      getchar();
      getchar();
      break;
    case 16:
      // 保存到文件
      printf("输入要保存的文件名：");
      scanf("%s", filename);
      statuss = SaveList(arr[num], filename);
      if (statuss == OK)
      {
        printf("已存入\n");
      }
      else
      {
        printf("线性表不存在\n");
      }
      getchar();
      getchar();
      break;
    case 17:
      // 从文件中读取
      printf("输入你要读取的文件名：");
      scanf("%s", filename);
      statuss = LoadList(arr[num], filename);
      if (statuss == OK)
      {
        printf("读取成功\n");
      }
      else
      {
        printf("读取失败\n");
      }
      getchar();
      getchar();
      break;
    case 18:
      // 切换线性表
      int i;
      printf("输入要切换到的线性表的序号：[0-29]");
      scanf("%d", &num);
      getchar();
      getchar();
      break;
    case 0:
      break;
    } // end of switch
  }   // end of while
  printf("欢迎下次再使用本系统！\n");
  return 0;
} // end of main()
