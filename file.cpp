//
// Created by lenovo on 2021/9/8.
//
#include "global.h"

/*
 * 函数名称: ReadFile
 * 接受参数: SATList*&
 * 函数功能: 用文件指针fp打开用户指定的文件，并读取文件内容保存到给定参数中，读取成功返回1，失败返回0
 * 返回值: int
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
        printf("文件打开失败!\n");
        return 0;
    }
    while ((ch = getc(fp)) == 'c') {
        while ((ch = getc(fp)) != '\n')
            continue;           //弃去一整行
    }   //运行到此，已经读取了字符p
    getc(fp); getc(fp); getc(fp); getc(fp); //弃去cnf三个字母
    fscanf(fp, "%d", &boolCount);    //p后的第1个数值是布尔变元数量
    fscanf(fp, "%d", &clauseCount);  //p后的第2个数值是子句数量
    cnf = (SATList*)malloc(sizeof(SATList));
    cnf->next = NULL;
    cnf->head = (SATNode*)malloc(sizeof(SATNode));
    cnf->head->next = NULL;
    lp = cnf;
    tp = cnf->head;

    //创建数量为clauseCount的子句, i为计数器
    for (i = 0; i < clauseCount; i++, lp = lp->next, tp = lp->head)
    {
        fscanf(fp, "%d", &number);
        for (; number != 0; tp = tp->next)
        {
            tp->data = number;  //数据域赋值
            tp->next = (SATNode*)malloc(sizeof(SATNode));  //开辟新结点
            fscanf(fp, "%d", &number);
            if (number == 0) tp->next = NULL;
        }
        lp->next = (SATList*)malloc(sizeof(SATList));  //开辟新表
        lp->next->head = (SATNode*)malloc(sizeof(SATNode));
        if (i == clauseCount - 1)
        {
            lp->next = NULL;
            break;
        }
    }
    printf("读取完毕\n");
    fclose(fp);
    return 1;
}

/*
* 函数名称: WriteFile
* 接受参数: int,int,int[]
* 函数功能: 将运行结果保存至同名文件，文件拓展名为.res,保存成功返回1，失败返回0
* 返回值: int
*/
int WriteFile(int result, double time, int value[])
{
    FILE* fp;
    int i;
    for (i = 0; fileName[i] != '\0'; i++)
    {
        //修改拓展名
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
        printf("文件打开失败!\n");
        return 0;
    }
    fprintf(fp, "s %d\nv ", result);  //求解结果
    if (result == 1)
    {
        //保存解值
        for (i = 1; i <= boolCount; i++)
        {
            if (value[i] == 1) fprintf(fp, "%d ", i);
            else fprintf(fp, "%d ", -i);
        }
    }
    fprintf(fp, "\nt %lf", time * 1000);  //运行时间/毫秒
    fclose(fp);
    return 1;
}
