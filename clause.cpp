//
// Created by lenovo on 2021/9/8.
//
#include "global.h"
//
//函数名称: destroyClause
//         接受参数: SATList*&
//         函数功能: 销毁链表
//         返回值: int
//
void destroyClause(SATList*& cnf)
{
    SATList* lp1, * lp2;
    SATNode* tp1, * tp2;
    for (lp1 = cnf; lp1 != NULL; lp1 = lp2)
    {
        lp2 = lp1->next;
        for (tp1 = lp1->head; tp1 != NULL; tp1 = tp2)
        {
            tp2 = tp1->next;
            free(tp1);
        }
        free(lp1);
    }
    cnf = NULL;
}

/*
 * 函数名称: isUnitClause
 * 接受参数: SATNode*
 * 函数功能: 判断是否为单子句，是返回1，不是返回0
 * 返回值: int
 */
int isUnitClause(SATNode* cnf)
{
    if (cnf != NULL && cnf->next == NULL)
        return 1;
    else
        return 0;
}

/*
 * 函数名称: evaluateClause
 * 接受参数: SATList*
 * 函数功能: 评估子句的真假状态，真返回1，假返回0
 * 返回值: int
 */
int evaluateClause(SATNode* cnf,int v[])
{
    SATNode* tp = cnf;
    while (tp != NULL)
    {
        if (tp->data > 0 && v[tp->data] == 1 ||
            tp->data < 0 && v[-tp->data] == 0)
            return 1;
    }
    return 0;
}

/*
 * 函数名称: removeClause
 * 接受参数: SATList*,SATList*
 * 函数功能: 在已有的十字链表中删除指定的子句，删除成功返回1，失败返回0
 * 返回值: int
 */
int removeClause(SATList*& cnf, SATList*& root)
{
    SATList* lp = root;
    if (lp == cnf) root = root->next;  //删除为头
    else
    {
        while (lp != NULL && lp->next != cnf) lp = lp->next;
        lp->next = lp->next->next;
    }
    free(cnf);
    cnf = NULL;
    return 1;
}

/*
 * 函数名称: removeNote
 * 接受参数: SATNode*,SATNode*
 * 函数功能: 在指定的子句中删除指定的文字，删除成功返回1，失败返回0
 * 返回值: int
 */
int removeNode(SATNode*& cnf, SATNode*& head)
{
    SATNode* lp = head;
    if (lp == cnf) head = head->next;  //删除为头
    else
    {
        while (lp != NULL && lp->next != cnf) lp = lp->next;
        lp->next = lp->next->next;
    }
    free(cnf);
    cnf = NULL;
    return 1;
}

/*
 * 函数名称: addClause
 * 接受参数: SATList*,SATList*
 * 函数功能: 在已有的十字链表中添加指定的子句，添加成功返回1，失败返回0
 * 返回值: int
 */
int addClause(SATList* cnf, SATList*& root)
{
    //直接插入在表头
    if (cnf != NULL)
    {
        cnf->next = root;
        root = cnf;
        return 1;
    }
    return 0;
}

/*
 * 函数名称: emptyClause
 * 接受参数: SATList*
 * 函数功能: 判断是否含有空子句，是返回1，不是返回0
 * 返回值: int
 */
int emptyClause(SATList* cnf)
{
    SATList* lp = cnf;
    while (lp != NULL)
    {
        if (lp->head == NULL) return 1;
        lp = lp->next;
    }
    return 0;
}

/*
 * 函数名称: CopyClause
 * 接受参数: SATList*,SATList*
 * 函数功能: 将链表b的值复制到链表a中
 * 返回值: void
 */
void CopyClause(SATList*& a, SATList* b)
{
    SATList* lpa,*lpb;
    SATNode* tpa,*tpb;
    a = (SATList*)malloc(sizeof(SATList));
    a->head = (SATNode*)malloc(sizeof(SATNode));
    a->next = NULL;
    a->head->next = NULL;
    for (lpb = b, lpa = a; lpb != NULL; lpb = lpb->next, lpa = lpa->next)
    {
        for (tpb = lpb->head, tpa = lpa->head; tpb != NULL; tpb = tpb->next, tpa = tpa->next)
        {
            tpa->data = tpb->data;
            tpa->next = (SATNode*)malloc(sizeof(SATNode));
            tpa->next->next = NULL;
            if (tpb->next == NULL)
            {
                free(tpa->next);
                tpa->next = NULL;
            }
        }
        lpa->next = (SATList*)malloc(sizeof(SATList));
        lpa->next->head = (SATNode*)malloc(sizeof(SATNode));
        lpa->next->next = NULL;
        lpa->next->head->next = NULL;
        if (lpb->next == NULL)
        {
            free(lpa->next->head);
            free(lpa->next);
            lpa->next = NULL;
        }
    }
}
