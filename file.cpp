//
// Created by lenovo on 2021/9/8.
//
#include "global.h"

/*
 * ��������: ReadFile
 * ���ܲ���: SATList*&
 * ��������: ���ļ�ָ��fp���û�ָ�����ļ�������ȡ�ļ����ݱ��浽���������У���ȡ�ɹ�����1��ʧ�ܷ���0
 * ����ֵ: int
 */
int ReadFile(SATList*& cnf)
{
    FILE* fp;
    char ch;
    int number, i;
    SATList* lp;
    SATNode* tp;
    fp=fopen(fileName, "r");
    if (fp==NULL) {
        printf("�ļ���ʧ��!\n");
        return 0;
    }
    while ((ch = getc(fp)) == 'c') {
        while ((ch = getc(fp)) != '\n')
            continue;           //��ȥһ����
    }   //���е��ˣ��Ѿ���ȡ���ַ�p
    getc(fp); getc(fp); getc(fp); getc(fp); //��ȥcnf������ĸ
    fscanf(fp, "%d", &boolCount);    //p��ĵ�1����ֵ�ǲ�����Ԫ����
    fscanf(fp, "%d", &clauseCount);  //p��ĵ�2����ֵ���Ӿ�����
    cnf = (SATList*)malloc(sizeof(SATList));
    cnf->next = NULL;
    cnf->head = (SATNode*)malloc(sizeof(SATNode));
    cnf->head->next = NULL;
    lp = cnf;
    tp = cnf->head;

    //��������ΪclauseCount���Ӿ�, iΪ������
    for (i = 0; i < clauseCount; i++, lp = lp->next, tp = lp->head)
    {
        fscanf(fp, "%d", &number);
        for (; number != 0; tp = tp->next)
        {
            tp->data = number;  //������ֵ
            tp->next = (SATNode*)malloc(sizeof(SATNode));  //�����½��
            fscanf(fp, "%d", &number);
            if (number == 0) tp->next = NULL;
        }
        lp->next = (SATList*)malloc(sizeof(SATList));  //�����±�
        lp->next->head = (SATNode*)malloc(sizeof(SATNode));
        if (i == clauseCount - 1)
        {
            lp->next = NULL;
            break;
        }
    }
    printf("��ȡ���\n");
    fclose(fp);
    return 1;
}

/*
* ��������: WriteFile
* ���ܲ���: int,int,int[]
* ��������: �����н��������ͬ���ļ����ļ���չ��Ϊ.res,����ɹ�����1��ʧ�ܷ���0
* ����ֵ: int
*/
int WriteFile(int result, double time, int value[])
{
    FILE* fp;
    int i;
    for (i = 0; fileName[i] != '\0'; i++)
    {
        //�޸���չ��
        if (fileName[i] == '.' && fileName[i + 4] == '\0')
        {
            fileName[i + 1] = 'r';
            fileName[i + 2] = 'e';
            fileName[i + 3] = 's';
            break;
        }
    }
    fp=fopen(fileName, "w");
    if (fp==NULL) {
        printf("�ļ���ʧ��!\n");
        return 0;
    }
    fprintf(fp, "s %d\nv ", result);  //�����
    if (result == 1)
    {
        //�����ֵ
        for (i = 1; i <= boolCount; i++)
        {
            if (value[i] == 1) fprintf(fp, "%d ", i);
            else fprintf(fp, "%d ", -i);
        }
    }
    fprintf(fp, "\nt %lf", time * 1000);  //����ʱ��/����
    fclose(fp);
    return 1;
}
