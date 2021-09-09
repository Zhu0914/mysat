//
// Created by lenovo on 2021/9/8.
//
#include "global.h"
//
//��������: destroyClause
//         ���ܲ���: SATList*&
//         ��������: ��������
//         ����ֵ: int
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
 * ��������: isUnitClause
 * ���ܲ���: SATNode*
 * ��������: �ж��Ƿ�Ϊ���Ӿ䣬�Ƿ���1�����Ƿ���0
 * ����ֵ: int
 */
int isUnitClause(SATNode* cnf)
{
    if (cnf != NULL && cnf->next == NULL)
        return 1;
    else
        return 0;
}

/*
 * ��������: evaluateClause
 * ���ܲ���: SATList*
 * ��������: �����Ӿ�����״̬���淵��1���ٷ���0
 * ����ֵ: int
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
 * ��������: removeClause
 * ���ܲ���: SATList*,SATList*
 * ��������: �����е�ʮ��������ɾ��ָ�����Ӿ䣬ɾ���ɹ�����1��ʧ�ܷ���0
 * ����ֵ: int
 */
int removeClause(SATList*& cnf, SATList*& root)
{
    SATList* lp = root;
    if (lp == cnf) root = root->next;  //ɾ��Ϊͷ
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
 * ��������: removeNote
 * ���ܲ���: SATNode*,SATNode*
 * ��������: ��ָ�����Ӿ���ɾ��ָ�������֣�ɾ���ɹ�����1��ʧ�ܷ���0
 * ����ֵ: int
 */
int removeNode(SATNode*& cnf, SATNode*& head)
{
    SATNode* lp = head;
    if (lp == cnf) head = head->next;  //ɾ��Ϊͷ
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
 * ��������: addClause
 * ���ܲ���: SATList*,SATList*
 * ��������: �����е�ʮ�����������ָ�����Ӿ䣬��ӳɹ�����1��ʧ�ܷ���0
 * ����ֵ: int
 */
int addClause(SATList* cnf, SATList*& root)
{
    //ֱ�Ӳ����ڱ�ͷ
    if (cnf != NULL)
    {
        cnf->next = root;
        root = cnf;
        return 1;
    }
    return 0;
}

/*
 * ��������: emptyClause
 * ���ܲ���: SATList*
 * ��������: �ж��Ƿ��п��Ӿ䣬�Ƿ���1�����Ƿ���0
 * ����ֵ: int
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
 * ��������: CopyClause
 * ���ܲ���: SATList*,SATList*
 * ��������: ������b��ֵ���Ƶ�����a��
 * ����ֵ: void
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
