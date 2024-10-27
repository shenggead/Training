#include "Queue.h"
#include "SqStack.h"
#include "maze.h"
//回溯法解决迷宫
void findRoad1(){
    //    随机生成迷宫
    int row,col;
//    初始位置在（1,1）
    int nowRow = 1;
    int nowCol = 1;
    printf("please input the row and col of maze\n");
    scanf("%d%d",&row,&col);
    int** maze = createMaze(row, col);
    maze[nowRow][nowCol] = 9;
    printfMaze(maze,row,col);
    SqStack sqStack;
    Init_sqStack(&sqStack);
    push(&sqStack,nowRow);
    push(&sqStack,nowCol);
    while (nowCol != col || nowRow != row){
//        如果有路可走就走，并在栈中记录走过的位置
        if (walkMaze(maze,&nowRow,&nowCol)){
            push(&sqStack,nowRow);
            push(&sqStack,nowCol);
        } else{
//         如果无路可走则回退，走其他的路
            pop(&sqStack);
            pop(&sqStack);
//            判断是否回溯到栈底且没有路，
            if(sqStackEmpty(&sqStack)){
                printf("no answer");
                break;
            }
            //          更新人的位置

            nowRow = sqStack.data[sqStack.top - 2];
            nowCol = getTop(&sqStack);
            walkMaze(maze,&nowRow,&nowCol);
        }
        sleep(2);

        system("cls");
//        sleep(2);
        maze[nowRow][nowCol] = 9;
        printfMaze(maze,row,col);

    }

}

//广度优先搜索找到最佳路径
//每次搜索相邻节点，并记录在队列中，每个队列节点需要记录之前节点的位置
void findRoad2()
{
    //    随机生成迷宫
    int row,col;
//    初始位置在（1,1）
    int nowRow = 1;
    int nowCol = 1;
    int count1 = 0;
    int count2 = 1;
//    标记是否有解
    int flag = 0;
    printf("please input the row and col of maze\n");
    scanf("%d%d",&row,&col);
    int** maze = createMaze(row, col);
    maze[nowRow][nowCol] = 9;
    printfMaze(maze,row,col);
//    用数组来记录广度优先搜索的结果 结构 上一个节点的位置(last)，row,col
    int answer[600] = {0};
//    用队列来广度优先搜索
    SqQueue sqQueue;
    InitSqQueue(&sqQueue);
//    从(1,1)开始，搜索所有可以走的路径
    inSqQueue(&sqQueue,nowRow);
    inSqQueue(&sqQueue,nowCol);
    answer[0] = -1;
    answer[1] = nowRow;
    answer[2] = nowCol;
//    当队首不为空
    while (!sqQueueEmpty(&sqQueue))
    {
//        将新队首赋值
        nowRow = getHead(&sqQueue);
        nowCol = sqQueue.data[sqQueue.front + 1];
//        如果有未访问过的下一个节点，则入队
        if (walkMaze(maze,&nowRow,&nowCol))
        {
            inSqQueue(&sqQueue,nowRow);
            inSqQueue(&sqQueue,nowCol);
            maze[nowRow][nowCol] = 9;
//                更新记录结果的数组
            answer[3 * count2] = count1;
            answer[3 * count2 + 1] = nowRow;
            answer[3 * count2 + 2] = nowCol;
            count2++;
            if (nowRow == row && nowCol == col)
            {
                flag++;
                break;
            }
        } else
        {
//            当所有的节点被记录，将队首出队
            delSqQueue(&sqQueue);
            delSqQueue(&sqQueue);
            count1++;
        }
    }
    if (flag){
        //  将最佳路径入栈
        SqStack sqStackRow;
        SqStack sqStackCol;
        Init_sqStack(&sqStackRow);
        Init_sqStack(&sqStackCol);
        int count3 = count2 - 1;
        while (answer[count3] != -1) {
            push(&sqStackRow,answer[count3 * 3 + 1]);
            push(&sqStackCol,answer[count3 * 3 + 2]);
            count3 = answer[count3 * 3];
        }
//    将最佳路径打印
        while (!sqStackEmpty(&sqStackRow)){
            printf("(%d,%d),", pop(&sqStackRow), pop(&sqStackCol));
        }
    }else{
        printf("无解");
    }

}

int main(){
//    findRoad1();
//    system("cls");
    findRoad2();
    return 0;
}