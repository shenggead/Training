#include "Queue.h"
#include "SqStack.h"
#include "maze.h"
//���ݷ�����Թ�
void findRoad1(){
    //    ��������Թ�
    int row,col;
//    ��ʼλ���ڣ�1,1��
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
//        �����·���߾��ߣ�����ջ�м�¼�߹���λ��
        if (walkMaze(maze,&nowRow,&nowCol)){
            push(&sqStack,nowRow);
            push(&sqStack,nowCol);
        } else{
//         �����·��������ˣ���������·
            pop(&sqStack);
            pop(&sqStack);
//            �ж��Ƿ���ݵ�ջ����û��·��
            if(sqStackEmpty(&sqStack)){
                printf("no answer");
                break;
            }
            //          �����˵�λ��

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

//������������ҵ����·��
//ÿ���������ڽڵ㣬����¼�ڶ����У�ÿ�����нڵ���Ҫ��¼֮ǰ�ڵ��λ��
void findRoad2()
{
    //    ��������Թ�
    int row,col;
//    ��ʼλ���ڣ�1,1��
    int nowRow = 1;
    int nowCol = 1;
    int count1 = 0;
    int count2 = 1;
//    ����Ƿ��н�
    int flag = 0;
    printf("please input the row and col of maze\n");
    scanf("%d%d",&row,&col);
    int** maze = createMaze(row, col);
    maze[nowRow][nowCol] = 9;
    printfMaze(maze,row,col);
//    ����������¼������������Ľ�� �ṹ ��һ���ڵ��λ��(last)��row,col
    int answer[600] = {0};
//    �ö����������������
    SqQueue sqQueue;
    InitSqQueue(&sqQueue);
//    ��(1,1)��ʼ���������п����ߵ�·��
    inSqQueue(&sqQueue,nowRow);
    inSqQueue(&sqQueue,nowCol);
    answer[0] = -1;
    answer[1] = nowRow;
    answer[2] = nowCol;
//    �����ײ�Ϊ��
    while (!sqQueueEmpty(&sqQueue))
    {
//        ���¶��׸�ֵ
        nowRow = getHead(&sqQueue);
        nowCol = sqQueue.data[sqQueue.front + 1];
//        �����δ���ʹ�����һ���ڵ㣬�����
        if (walkMaze(maze,&nowRow,&nowCol))
        {
            inSqQueue(&sqQueue,nowRow);
            inSqQueue(&sqQueue,nowCol);
            maze[nowRow][nowCol] = 9;
//                ���¼�¼���������
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
//            �����еĽڵ㱻��¼�������׳���
            delSqQueue(&sqQueue);
            delSqQueue(&sqQueue);
            count1++;
        }
    }
    if (flag){
        //  �����·����ջ
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
//    �����·����ӡ
        while (!sqStackEmpty(&sqStackRow)){
            printf("(%d,%d),", pop(&sqStackRow), pop(&sqStackCol));
        }
    }else{
        printf("�޽�");
    }

}

int main(){
//    findRoad1();
//    system("cls");
    findRoad2();
    return 0;
}