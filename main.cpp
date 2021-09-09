#include "global.h"
using namespace std;

int main() {
    SATList* CNFList = NULL, * lp;
    SATNode* tp;
    clock_t start, finish;  //设置时间变量
    double time;
    int op = 1, i, result;
    int* value;  //保存结果
    while (op)
    {
        system("cls");	printf("\n\n");
        printf("		功能菜单 \n");
        printf("-------------------------------------------------\n");
        printf("1.读取cnf文件  2.数独游戏\n");
        printf("0.退出\n");
        printf("-------------------------------------------------\n");
        printf("	请选择你的操作[0~2]:");
        scanf("%d", &op);
        switch (op)
        {
            case 1:
                printf("输入要读取的cnf文件:");
                scanf("%s", fileName);
                ReadFile(CNFList);
                if (CNFList == NULL) printf("未导入文件\n");
                else
                {
                    printf("cnf子句如下：\n");
                    for (lp = CNFList; lp != NULL; lp = lp->next)
                    {
                        for (tp = lp->head; tp != NULL; tp = tp->next)
                        {
                            printf("%d ", tp->data);
                        }
                        printf("\n");
                    }
                }
                if (CNFList == NULL) printf("未导入文件\n");
                else
                {
                    value = (int*)malloc(sizeof(int) * (boolCount + 1));
                    for (i = 1; i <= boolCount; i++) value[i] = 1;  //初始化，均赋为1
                    start = clock();  //计时开始;
                    result = DPLL(CNFList, value);
                    finish = clock();    //结束
                    printf("求解结果：%d\n", result);
                    if (result == 1)
                    {
                        for (i = 1; i <= boolCount; i++)
                        {
                            if (value[i] == 1) printf("%d ", i);
                            else printf("%d ", -i);
                        }
                        printf("\n");
                    }
                    time = (double)(finish - start) / CLOCKS_PER_SEC;//计算运行时间
                    printf("运行时间=%lfms\n", time * 1000);//输出运行时间
                    if (WriteFile(result, time, value) == 1)
                        printf("结果已保存至同名文件.res\n");
                    else printf("结果保存失败\n");
                }
                getchar(); getchar();
                break;
            case 2:
                sudu();
            case 0:
                break;
        }
    }
    return 0;
}
