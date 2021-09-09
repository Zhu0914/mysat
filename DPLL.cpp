#include "global.h"
#include <thread>
int DPLL(SATList*& cnf, int value[])
{
    SATList* tp = cnf, * lp = cnf, * sp;
    SATNode* dp;
    int* count, i, MaxWord,max, re; //count��¼ÿ�����ֳ��ִ���,MaxWord��¼����������������
    count = (int*)malloc(sizeof(int) * (boolCount * 2 + 1));
    FIND:	while (tp != NULL && isUnitClause(tp->head) == 0) tp = tp->next;  //�ҵ����еĵ��Ӿ�
    if (tp != NULL)
    {
        //���Ӿ�����
        if (tp->head->data > 0) value[tp->head->data] = 1;
        else value[-tp->head->data] = 0;
        re = tp->head->data;
        for (lp = cnf; lp != NULL; lp = sp)
        {
            sp = lp->next;

            //���Һ��к������ֵľ���
            for (dp = lp->head; dp != NULL; dp = dp->next)
            {
                if (dp->data == re)
                {
                    removeClause(lp, cnf);  //ɾ���Ӿ䣬��ʽ��
                    break;
                }
                else if (dp->data == -re)
                {
                    removeNode(dp, lp->head);  //ɾ�����֣����Ӿ�
                    break;
                }
            }
        }
        //���򻯹���򻯺�
        if (cnf == NULL)
        {
            free(count);
            return 1;
        }
        else if (emptyClause(cnf))
        {
            free(count);
            destroyClause(cnf);
            return 0;
        }
        tp = cnf;
        goto FIND;  //������
    }
    for (i = 0; i <= boolCount * 2; i++) count[i] = 0;  //��ʼ��

    //�����Ӿ��и����ֳ��ִ���
    for (lp = cnf; lp != NULL; lp = lp->next)
    {
        for (dp = lp->head; dp != NULL; dp = dp->next)
        {
            if (dp->data > 0) count[dp->data]++;
            else count[boolCount - dp->data]++;
        }
    }
    max = 0;
    //�ҵ����ִ�������������
    for (i = 2; i <= boolCount; i++)
    {
        if (max < count[i])
        {
            max = count[i];
            MaxWord = i;
        }
    }

    if (max == 0)
    {
        //��û�г���������,�ҵ����ִ������ĸ�����
        for (i = boolCount + 1; i <= boolCount * 2; i++)
        {
            if (max < count[i])
            {
                max = count[i];
                MaxWord = -i;
            }
        }
    }
    free(count);
    lp = (SATList*)malloc(sizeof(SATList));
    lp->head = (SATNode*)malloc(sizeof(SATNode));
    lp->head->data = MaxWord;
    lp->head->next = NULL;
    lp->next = NULL;
    CopyClause(tp, cnf);
    addClause(lp, tp);
    if (DPLL(tp, value) == 1) return 1;  //�ڵ�һ��֧������
    destroyClause(tp);
    lp = (SATList*)malloc(sizeof(SATList));
    lp->head = (SATNode*)malloc(sizeof(SATNode));
    lp->head->data = -MaxWord;
    lp->head->next = NULL;
    lp->next = NULL;
    addClause(lp, cnf);
    re = DPLL(cnf, value); //���ݵ�ִ�з�֧���Եĳ�̬������һ��֧
    destroyClause(cnf);
    return re;
}


