#include "global.h"
using namespace std;

int main() {
    SATList* CNFList = NULL, * lp;
    SATNode* tp;
    clock_t start, finish;  //����ʱ�����
    double time;
    int op = 1, i, result;
    int* value;  //������
    while (op)
    {
        system("cls");	printf("\n\n");
        printf("		���ܲ˵� \n");
        printf("-------------------------------------------------\n");
        printf("1.��ȡcnf�ļ�  2.������Ϸ\n");
        printf("0.�˳�\n");
        printf("-------------------------------------------------\n");
        printf("	��ѡ����Ĳ���[0~2]:");
        scanf("%d", &op);
        switch (op)
        {
            case 1:
                printf("����Ҫ��ȡ��cnf�ļ�:");
                scanf("%s", fileName);
                ReadFile(CNFList);
                if (CNFList == NULL) printf("δ�����ļ�\n");
                else
                {
                    printf("cnf�Ӿ����£�\n");
                    for (lp = CNFList; lp != NULL; lp = lp->next)
                    {
                        for (tp = lp->head; tp != NULL; tp = tp->next)
                        {
                            printf("%d ", tp->data);
                        }
                        printf("\n");
                    }
                }
                if (CNFList == NULL) printf("δ�����ļ�\n");
                else
                {
                    value = (int*)malloc(sizeof(int) * (boolCount + 1));
                    for (i = 1; i <= boolCount; i++) value[i] = 1;  //��ʼ��������Ϊ1
                    start = clock();  //��ʱ��ʼ;
                    result = DPLL(CNFList, value);
                    finish = clock();    //����
                    printf("�������%d\n", result);
                    if (result == 1)
                    {
                        for (i = 1; i <= boolCount; i++)
                        {
                            if (value[i] == 1) printf("%d ", i);
                            else printf("%d ", -i);
                        }
                        printf("\n");
                    }
                    time = (double)(finish - start) / CLOCKS_PER_SEC;//��������ʱ��
                    printf("����ʱ��=%lfms\n", time * 1000);//�������ʱ��
                    if (WriteFile(result, time, value) == 1)
                        printf("����ѱ�����ͬ���ļ�.res\n");
                    else printf("�������ʧ��\n");
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
