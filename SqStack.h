//
// Created by 艾丹 on 2024/10/14.
//

#ifndef LUOGU_SQSTACK_H
#define LUOGU_SQSTACK_H

#endif //LUOGU_SQSTACK_H
#include <iostream>
#define ERROR           0
#define OK              1
#define INIT_SIZE       50
#define STACKINCREMENT  10
#define OVERFLOW        -1
typedef int ElemType;
typedef struct {
    ElemType *data;
    int top;
}SqStack;

//初始化栈
void Init_sqStack(SqStack* sqStack){
    sqStack->data = (ElemType*) malloc(INIT_SIZE * sizeof (ElemType));
    if (!sqStack->data){
        exit(OVERFLOW);
    }
    sqStack->top = 0;
}
//判断栈是否为空
int sqStackEmpty(SqStack* sqStack){
    if (sqStack->top == 0){
        return OK;
    } else{
        return ERROR;
    }
}
//判断栈是否为满,如果满了，则增加
int sqStackFull(SqStack* sqStack){
    if (sqStack->top >= INIT_SIZE){
        sqStack->data = (ElemType*) realloc(sqStack->data,sqStack->top + STACKINCREMENT);
        if(!sqStack->data){
            exit(OVERFLOW);//存储分配失败退出
        }
        return OK;
    } else{
        return ERROR;
    }
}

//增加栈元素
void push(SqStack* sqStack,ElemType e){
    sqStackFull(sqStack);
    sqStack->data[sqStack->top] = e;
    sqStack->top += 1;
}
//删除栈元素,并返回栈顶元素 退栈
ElemType pop(SqStack* sqStack){
    if (sqStackEmpty(sqStack)){
        return ERROR;
    }
    ElemType e = sqStack->data[sqStack->top - 1];
    sqStack->top--;
    return e;
}
//取栈顶元素
ElemType getTop(SqStack *sqStack){
    if (sqStackEmpty(sqStack)){
        return ERROR;
    }
    return sqStack->data[sqStack->top - 1];
}
//创建栈
void sqStackCreate(SqStack* sqStack){
    printf("input an arithmetic expression and end with #\n");
    ElemType e;
    do{
        scanf("%c",&e);
        push(sqStack,e);
    }while (e != '#');
}
//打印栈
void sqStackPrint(SqStack* sqStack){
    for (int i = 0; i < sqStack->top; ++i) {
        ElemType e = sqStack->data[i];
        if ( e== '(' || e == '[' || e == '{'|| e == ')'||e == ']' || e == '}'){
            printf("error");
            return;
        }
        printf("%c\n",sqStack->data[i]);
    }
    printf("ok\n");
}