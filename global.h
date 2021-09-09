//
// Created by lenovo on 2021/9/7.
//

#ifndef MYSAT_GLOBAL_H
#define MYSAT_GLOBAL_H
#include <bits/stdc++.h>
#include<windows.h>
extern int boolCount;  //布尔变元数量
extern int clauseCount;  //子句数量
extern char fileName[100]; //文件名

//十字链表结构体
typedef struct SATNode{
    int data;  //数据域
    SATNode* next;
}SATNode;
typedef struct SATList {
    SATNode* head;  //表头
    SATList* next;
}SATList;

//函数声明
int ReadFile(SATList*& cnf);
void destroyClause(SATList*& cnf);
int isUnitClause(SATNode* cnf);
int evaluateClause(SATNode* cnf, int v[]);
int removeClause(SATList*& cnf, SATList*& root);
int removeNode(SATNode*& cnf, SATNode*& head);
int addClause(SATList* cnf, SATList*& root);
int emptyClause(SATList* cnf);
int DPLL(SATList*& cnf, int value[]);
void CopyClause(SATList*& a, SATList* b);
int WriteFile(int result, double time, int value[]);
//sudu
void SetColor(unsigned short ,unsigned short );
int ge(int x,int y);
int print();
int print_y();
int dfs(int x,int y);
int work(int x);
void init();
void run();
int sudu();
#endif //MYSAT_GLOBAL_H
