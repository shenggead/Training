//
// Created by 艾丹 on 2024/10/21.
//
#include <unistd.h>
#include "stdlib.h"
#include "time.h"
#ifndef LUOGU_MAZE_H
#define LUOGU_MAZE_H
#endif //LUOGU_MAZE_H
#define WALL 1
#define ROAD 0
//通过随机数生成迷宫
int** createMaze(int row, int col){
    //    分配行长度
    int** maze = (int**) malloc((row + 2) * sizeof(int*) );
//    分配列长度
    for (int i = 0; i < col + 2; ++i)
    {
        maze[i] = (int*) malloc((row + 2) * sizeof (int));
    }
    srand((unsigned)time(nullptr));
    for (int i = 0; i < row + 2; ++i) {
        for (int j = 0; j < col + 2; ++j) {
//            设置墙
            if (j == 0 || j == col + 1 || i == 0 || i == row + 1){
                maze[i][j] = WALL;
            }else{
                maze[i][j] = rand() % 2;
            }
        }
        printf("\n");
    }
    maze[1][1] = 0;
    maze[row][col] = 0;
    return maze;
}
//八个方向
status walkMaze(int** maze,int* a,int* b) {
    int row = *a;
    int col = *b;
//    右
    if (maze[row][col + 1] == ROAD) {
        *b += 1;
    } else if (maze[row + 1][col + 1] == ROAD) {
//        右下，
        *b += 1;
        *a += 1;
    } else if (maze[row + 1][col] == ROAD) {
//       下
        *a += 1;
    }else if (maze[row + 1][col - 1] == ROAD) {
//        ，左下
        *b -= 1;
        *a += 1;
    }else if (maze[row][col - 1] == ROAD) {
//        ，左，
        *b -= 1;
    }else if (maze[row - 1][col - 1] == ROAD) {
//       左上
        *b -= 1;
        *a -= 1;
    }else if (maze[row - 1][col] == ROAD) {
//       ，上，
        *a -= 1;
    }else if (maze[row - 1][col + 1] == ROAD) {
//        上右
        *b += 1;
        *a -= 1;
    } else{
        return ERROR;
    }
    return OK;
}


//打印迷宫
void printfMaze(int** maze,int row,int col){
    for (int i = 0; i < row + 2; ++i) {
        for (int j = 0; j < col + 2; ++j) {
            printf("%2d",maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}