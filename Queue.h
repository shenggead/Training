//
// Created by 艾丹 on 2024/10/20.
//

#ifndef LUOGU_D_H
#define LUOGU_D_H

#endif //LUOGU_D_H
#include <iostream>
#include <malloc.h> 
#define INIT_SIZE       50
#define ERROR           0
#define OK              1
#define INIT_SIZE       50
#define SIZE_INCREASE   10
#define OVERFLOW        -1
typedef int ElemType;
typedef int status;
typedef struct {
    ElemType* data;
    int front,rear;
}SqQueue;
//队列初始化
void InitSqQueue(SqQueue* sqQueue){
    sqQueue->data = (ElemType *)malloc(INIT_SIZE * sizeof (ElemType));
    if (!sqQueue->data){
        exit(OVERFLOW);
    }
    //    让data数组第一个元素保存队列长度，好判断是否满了
    sqQueue->data[0] = INIT_SIZE;
    sqQueue->rear = 1;
    sqQueue->front = 1;
}

//判断队列是否空
status sqQueueEmpty(SqQueue* sqQueue){
    if (sqQueue->front == sqQueue->rear){
        return OK;
    }
    return ERROR;
}

//判断队列是否满
status sqQueueFull(SqQueue* sqQueue){
    if (sqQueue->rear >= sqQueue->data[0]){
//        满了，继续分配内存
        sqQueue->data = (ElemType *)realloc(sqQueue->data,sqQueue->data[0] + SIZE_INCREASE);
        if (!sqQueue->data){
            exit(OVERFLOW);
        }
    }
    return OK;
}

//入队操作
void inSqQueue(SqQueue* sqQueue,ElemType e){
    sqQueueFull(sqQueue);
    sqQueue->data[sqQueue->rear] = e;
    sqQueue->rear++;
}
//出队并返回出队的元素
ElemType delSqQueue(SqQueue* sqQueue){
    if (sqQueueEmpty(sqQueue)){
        exit(OVERFLOW);
    }
    ElemType e = sqQueue->data[sqQueue->front];
    sqQueue->data[sqQueue->front] = 0;
    sqQueue->front++;
    return e;
}
//得到队首元素
ElemType getHead(SqQueue* sqQueue){
    if (sqQueueEmpty(sqQueue)){
        return ERROR;
    }
    return sqQueue->data[sqQueue->front];
}
//打印队列元素
void printfSqQueue(SqQueue* sqQueue){
    for (int i = sqQueue->front; i < sqQueue->rear; ++i) {
        printf("%d",sqQueue->data[i]);
    }
}
