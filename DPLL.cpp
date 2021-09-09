#include "global.h"
#include <thread>
int DPLL(SATList*& cnf, int value[])
{
    SATList* tp = cnf, * lp = cnf, * sp;
    SATNode* dp;
    int* count, i, MaxWord,max, re; //count记录每个文字出现次数,MaxWord记录出现最多次数的文字
    count = (int*)malloc(sizeof(int) * (boolCount * 2 + 1));
    FIND:	while (tp != NULL && isUnitClause(tp->head) == 0) tp = tp->next;  //找到表中的单子句
    if (tp != NULL)
    {
        //单子句规则简化
        if (tp->head->data > 0) value[tp->head->data] = 1;
        else value[-tp->head->data] = 0;
        re = tp->head->data;
        for (lp = cnf; lp != NULL; lp = sp)
        {
            sp = lp->next;

            //查找含有核心文字的句子
            for (dp = lp->head; dp != NULL; dp = dp->next)
            {
                if (dp->data == re)
                {
                    removeClause(lp, cnf);  //删除子句，简化式子
                    break;
                }
                else if (dp->data == -re)
                {
                    removeNode(dp, lp->head);  //删除文字，简化子句
                    break;
                }
            }
        }
        //极简化规则简化后
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
        goto FIND;  //继续简化
    }
    for (i = 0; i <= boolCount * 2; i++) count[i] = 0;  //初始化

    //计算子句中各文字出现次数
    for (lp = cnf; lp != NULL; lp = lp->next)
    {
        for (dp = lp->head; dp != NULL; dp = dp->next)
        {
            if (dp->data > 0) count[dp->data]++;
            else count[boolCount - dp->data]++;
        }
    }
    max = 0;
    //找到出现次数最多的正文字
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
        //若没有出现正文字,找到出现次数最多的负文字
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
    if (DPLL(tp, value) == 1) return 1;  //在第一分支中搜索
    destroyClause(tp);
    lp = (SATList*)malloc(sizeof(SATList));
    lp->head = (SATNode*)malloc(sizeof(SATNode));
    lp->head->data = -MaxWord;
    lp->head->next = NULL;
    lp->next = NULL;
    addClause(lp, cnf);
    re = DPLL(cnf, value); //回溯到执行分支策略的初态进入另一分支
    destroyClause(cnf);
    return re;
}


