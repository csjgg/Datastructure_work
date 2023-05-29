#include "define.h"

// main
int main(void) {
  BiTree list[30] = {NULL};
  TElemType arr[30];
  int num = 0;
  int op = 1;
  int len;
  int i;
  int count;
  BiTree tmp;
  char filename[20];
  TElemType ttt;
  int statuss;
  while (op) {
    // system("cls");
    printf("\n\n");
    // 打印菜单
    printf("      Menu for Linear Table On List Structure \n");
    printf("-------------------------------------------------\n");
    printf("    	  1. 初始化                       7. 更改节点值\n");
    printf("    	  2. 摧毁                         8. 获取兄弟节点\n");
    printf("    	  3. 清空                         9. 插入元素\n");
    printf("    	  4. 判断是否为空                 10. 删除元素\n");
    printf("    	  5. 求深度                       11. 先序遍历\n");
    printf("    	  6. 获取元素                     12. 中序遍历\n");
    printf("    	  13. 后序遍历                    14. 层序遍历\n");
    printf("    	  15. 从根节点开始的最大路径       16. 保存到文件\n");
    printf("    	  17. 从文件读取                  18. 切换二叉树\n");
    printf("    	  19. 交换左右子树                20. 求最近公共祖先\n");
    printf("    	  0. 退出\n");
    printf("-------------------------------------------------\n");
    printf("    请选择你的操作[0~20]:");
    scanf("%d", &op);
    switch (op) {
      case 1:
        // 创建二叉树
        count = 0;
        do{
          scanf("%d %s", &arr[count].key, arr[count].others);
        }
        while (arr[count++].key != -1);
        if (CreateBiTree(list[num], arr) == OK)
          printf("二叉树创建成功！\n");
        else
          printf("二叉树已经存在或关键字相同\n");
        getchar();
        getchar();
        break;
      case 2:
        // 销毁二叉树
        if (list[num] == NULL) {
          printf("二叉树不存在\n");
          getchar();
          getchar();
          break;
        }
        if (ClearBiTree(list[num]) == OK) {
          printf("二叉树销毁成功！\n");
          list[num] = NULL;
        }
        getchar();
        getchar();
        break;
      case 3:
        // 清空二叉树
        if (list[num] == NULL) {
          printf("二叉树不存在\n");
        } else {
          ClearBiTree(list[num]->lchild);
          ClearBiTree(list[num]->rchild);
          list[num]->data.key = -1;
          printf("已清空\n");
        }
        getchar();
        getchar();
        break;
      case 4:
        // 判断二叉树是否为空
        if (list[num] == NULL) {
          printf("二叉树不存在\n");
        } else if (list[num]->data.key == -1 && list[num]->lchild == NULL &&
                   list[num]->rchild == NULL) {
          printf("二叉树为空\n");
        } else {
          printf("二叉树不为空\n");
        }
        getchar();
        getchar();
        break;
      case 5:
        // 求二叉树深度
        if (list[num] == NULL) {
          printf("二叉树不存在\n");
          getchar();
          getchar();
          break;
        }
        if ((len = BiTreeDepth(list[num]))) {
          printf("二叉树深度为%d\n", len);
        }
        getchar();
        getchar();
        break;
      case 6:
        // 获取元素
        printf("输入要获取的元素：");
        scanf("%d", &i);
        tmp = LocateNode(list[num], i);
        if (tmp == NULL) {
          printf("未找到\n");
        } else {
          printf("找到了，结点标签为%s", tmp->data.others);
        }
        getchar();
        getchar();
        break;
      case 7:
        // 更改结点值
        int elem;
        printf("请输入想更改值的节点值：");
        scanf("%d", &elem);
        printf("输入想更改成的值：");
        scanf("%d", &ttt.key);
        printf("输入更改的值的标签：");
        scanf("%s", ttt.others);
        statuss = Assign(list[num], elem, ttt);
        if (statuss == ERROR) {
          printf("未找到该元素\n");
        } else {
          printf("更改成功\n");
        }
        getchar();
        getchar();
        break;
      case 8:
        // 获取兄弟节点
        int pre;
        printf("请输入想获取兄弟节点的元素的值：");
        scanf("%d", &pre);
        tmp = GetSibling(list[num], pre);
        if (tmp == NULL) {
          printf("未找到该元素\n");
        } else {
          printf("兄弟节点的值是：%d,标签是%s\n", tmp->data.key,
                 tmp->data.others);
        }
        getchar();
        getchar();
        break;
      case 9:
        // 插入节点
        int next,LR;
        printf("请输入想插入到的元素：");
        scanf("%d", &next);
        printf("请输入插入方式LR：");
        scanf("%d",&LR);
        printf("输入想插入的值：");
        scanf("%d", &ttt.key);
        printf("输入插入的值的标签：");
        scanf("%s",ttt.others);
        statuss = InsertNode(list[num],next,LR,ttt);
        if (statuss == ERROR) {
          printf("插入失败\n");
        } else {
          printf("插入成功\n");
        }
        getchar();
        getchar();
        break;
      case 10:
        // 删除元素
        printf("输入要删除的元素：");
        scanf("%d", &i);
        statuss = DeleteNode(list[num], i);
        if (statuss == OK) {
          printf("删除成功！\n");
        } else {
          printf("删除失败！\n");
        }
        getchar();
        getchar();
        break;
      case 11:
        // 前序遍历
        PreOrderTraverse(list[num],visit);
        getchar();
        getchar();
        break;
      case 12:
        // 中序遍历
        InOrderTraverse(list[num],visit);
        getchar();
        getchar();
        break;
      case 13:
        // 后序遍历
        PostOrderTraverse(list[num],visit);
        getchar();
        getchar();
        break;
      case 14:
        // 层序遍历
        LevelOrderTraverse(list[num],visit);
        getchar();
        getchar();
        break;
      case 15:
        // 求最大路径和
        len = MaxPathSum(list[num]);
        printf("%d",len);
        getchar();
        getchar();
        break;
      case 16:
        // 保存到文件
        printf("输入要保存的文件名：");
        scanf("%s", filename);
        statuss = SaveBiTree(list[num], filename);
        if (statuss == OK) {
          printf("已存入\n");
        } else {
          printf("二叉树不存在\n");
        }
        getchar();
        getchar();
        break;
      case 17:
        // 从文件中读取
        printf("输入你要读取的文件名：");
        scanf("%s", filename);
        statuss = LoadBiTree(list[num], filename);
        if (statuss == OK) {
          printf("读取成功\n");
        } else {
          printf("读取失败\n");
        }
        getchar();
        getchar();
        break;
      case 18:
        // 切换BiTree
        printf("输入要切换到的二叉树的序号：[0-29]");
        scanf("%d", &num);
        printf("已切换到第%d个二叉树\n", num);
        list[num] = NULL;
        getchar();
        getchar();
        break;
      case 19:
        // 交换左右子树
        statuss = InvertTree(list[num]);
        if (statuss == OK) {
          printf("交换成功\n");
        } else {
          printf("交换失败\n");
        }
        getchar();
        getchar();
        break;
      case 20:
        // 求两节点的最近公共祖先
        int a, b;
        printf("输入两个元素：");
        scanf("%d %d",&a,&b);
        tmp = LowestCommonAncestor(list[num],a,b);
        if(tmp == NULL){
          printf("无公共祖先\n");
        }else{
          printf("公共祖先是%d,标签是%s",tmp->data.key,tmp->data.others);
        }
        getchar();
        getchar();
        break;
      case 0:
        break;
    }  // end of switch
  }    // end of while
  printf("欢迎下次再使用本系统！\n");
  return 0;
}  // end of main()
