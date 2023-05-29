#include "define.h"
int main(void) {
  SqList LS[20];  // 顺序表数组
  int i = 0;      // 顺序表数组下标
  int length;
  int tmp_status;
  int op = 1;
  int pos = 0;          // 插入位置 or 删除位置 or 查找位置
  int elem = 0;         // 获取的元素
  int pre_or_next = 0;  // 前驱 or 后继
  char filename[20];
  while (op) {
    system("cls");
    printf("\n\n");
    printf("      Menu for Linear Table On Sequence Structure \n");
    printf("-------------------------------------------------\n");
    printf("    	  1. InitList       7. LocateElem\n");
    printf("    	  2. DestroyList    8. PriorElem\n");
    printf("    	  3. ClearList      9. NextElem \n");
    printf("    	  4. ListEmpty      10. ListInsert\n");
    printf("    	  5. ListLength     11. ListDelete\n");
    printf("    	  6. GetElem        12. ListTraverse\n");
    printf("        13. MaxSubArray   14. SubArrayNum\n");
    printf("    	  15. SortList      16. Save\n");
    printf("    	  17. Load          18. ChangeList\n");
    printf("    	  0. Exit\n");
    printf("-------------------------------------------------\n");
    printf("    请选择你的操作[0~18]:");
    scanf("%d", &op);
    switch (op) {
      case 1:
        if (InitList(LS[i]) == OK)
          printf("线性表创建成功！\n");
        else
          printf("线性表创建失败！\n");
        getchar();
        getchar();
        break;
      case 2:
        if (DestroyList(LS[i]) == OK)
          printf("线性表销毁成功！\n");
        else
          printf("不存在线性表\n");
        getchar();
        getchar();
        break;
      case 3:
        if (ClearList(LS[i]) == OK)
          printf("线性表元素已清除\n");
        else
          printf("不存在线性表\n");
        getchar();
        getchar();
        break;
      case 4:
        tmp_status = ListEmpty(LS[i]);
        if (tmp_status == TRUE)
          printf("线性表无元素\n");
        else if (tmp_status == FALSE)
          printf("线性表元素不为空\n");
        else
          printf("不存在线性表\n");
        getchar();
        getchar();
        break;
      case 5:
        length = ListLength(LS[i]);
        if (length == INFEASIBLE)
          printf("线性表为空\n");
        else
          printf("线性表长度为%d\n", length);
        getchar();
        getchar();
        break;
      case 6:
        printf("请输入要查找的位置：");
        scanf("%d", &pos);
        tmp_status = GetElem(LS[i], pos, elem);
        if (tmp_status == OK)
          printf("第%d个元素为%d\n", pos, elem);
        else if (tmp_status == ERROR)
          printf("输入位置错误\n");
        else
          printf("不存在线性表\n");
        getchar();
        getchar();
        break;
      case 7:
        printf("请输入要查找的元素：");
        scanf("%d", &elem);
        tmp_status = LocateElem(LS[i], elem);
        if (tmp_status == INFEASIBLE)
          printf("不存在线性表\n");
        else if (tmp_status == 0)
          printf("不存在该元素\n");
        else
          printf("元素%d的位置为%d\n", elem, tmp_status);
        getchar();
        getchar();
        break;
      case 8:
        printf("输入你想查找前驱元素的元素：");
        scanf("%d", &elem);
        tmp_status = PriorElem(LS[i], elem, pre_or_next);
        if (tmp_status == INFEASIBLE)
          printf("不存在线性表\n");
        else if (tmp_status == ERROR)
          printf("不存在前驱元素\n");
        else
          printf("元素%d的前驱元素为%d\n", elem, pre_or_next);
        getchar();
        getchar();
        break;
      case 9:
        printf("输入你想查找后继元素的元素：");
        scanf("%d", &elem);
        tmp_status = NextElem(LS[i], elem, pre_or_next);
        if (tmp_status == INFEASIBLE)
          printf("不存在线性表\n");
        else if (tmp_status == ERROR)
          printf("不存在后继元素\n");
        else
          printf("元素%d的后继元素为%d\n", elem, pre_or_next);
        getchar();
        getchar();
        break;
      case 10:
        printf("输入你想插入的位置：");
        scanf("%d", &pos);
        printf("\n");
        printf("输入你想插入的元素：");
        scanf("%d", &elem);
        tmp_status = ListInsert(LS[i], pos, elem);
        if (tmp_status == OK)
          printf("插入成功\n");
        else if (tmp_status == ERROR)
          printf("插入位置错误\n");
        else
          printf("不存在线性表\n");
        getchar();
        getchar();
        break;
      case 11:
        printf("输入你想删除的位置：");
        scanf("%d", &pos);
        tmp_status = ListDelete(LS[i], pos, elem);
        if (tmp_status == OK)
          printf("删除成功，删除元素为%d\n", elem);
        else if (tmp_status == ERROR)
          printf("删除位置错误\n");
        else
          printf("不存在线性表\n");
        getchar();
        getchar();
        break;
      case 12:
        // printf("\n----ListTrabverse功能待实现！\n");
        if (!ListTrabverse(LS[i])) printf("线性表是空表！\n");
        getchar();
        getchar();
        break;
      case 13:
        tmp_status = MaxSubArray(LS[i]);
        if (tmp_status == INFEASIBLE) printf("不存在线性表\n");
        getchar();
        getchar();
        break;
      case 14:
        printf("输入你想找寻的字串和：");
        scanf("%d", &elem);
        tmp_status = SubArrayNum(LS[i], elem);
        if (tmp_status == INFEASIBLE) printf("不存在线性表\n");
        getchar();
        getchar();
        break;
      case 15:
        tmp_status = SortList(LS[i]);
        if (tmp_status == INFEASIBLE) printf("不存在线性表\n");
        getchar();
        getchar();
        break;
      case 16:
        printf("输入放入的文件名：");
        scanf("%s", filename);
        tmp_status = SaveList(LS[i], filename);
        if (tmp_status == INFEASIBLE)
          printf("线性表已经有内容，不能覆盖\n");
        else
          printf("保存成功！\n");
        getchar();
        getchar();
        break;
      case 17:
        printf("输入读取的文件名：");
        scanf("%s", filename);
        tmp_status = LoadList(LS[i], filename);
        if (tmp_status == INFEASIBLE)
          printf("不存在线性表\n");
        else if (tmp_status == ERROR)
          printf("文件打开失败！\n");
        else
          printf("读取成功！\n");
        getchar();
        getchar();
        break;
      case 18:
        printf("输入你想切换的线性表(1~20):\n");
        scanf("%d", &i);
        i--;
        printf("切换成功！\n");
        getchar();
        break;
      case 0:
        break;
      default:
        printf("输入错误，请重新输入！\n");
    }  // end of switch
  }    // end of while
  printf("欢迎下次再使用本系统！\n");
  return 0;
}  // end of main()

/*--------page 23 on textbook --------------------*/