#include<stdio.h>
#include <string.h>  
#include <unistd.h>  
#include<termios.h>  
#include<assert.h>  
#include<time.h> 
#include <stdlib.h>

int num[4][4];//存放16个格子的数据
//score存放分数,ifappear表示是否需要产生数字
int score,ifappear,move;
char key;//存放获取的输入


char getchch()  
{  
        char c=0;  
        struct termios org_opts, new_opts;  
        int res=0;  

        res=tcgetattr(STDIN_FILENO, &org_opts);  
        assert(res==0);  
        memcpy(&new_opts, &org_opts, sizeof(new_opts));  
        new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT     | ECHOKE | ICRNL);  
        tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);  
        c=getchar();  
        res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);  
        assert(res==0);  
        return c;  
}  

void appear(){
    int ran = 0,position[16],x=0,a,b;
    srand(time(0));
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            if(num[i][j]==0){
                position[x] = i * 10 + j;//保存空白区域的坐标
                x++;//记录空白格子的数目
            }
        }
    }
    if(x==1){
        ran = x -1;
    }else{
        ran = rand()%(x-1);
        a= position[ran] / 10;
        b = position[ran] % 10;
    }
    srand(time(0));
    if(rand()%9>2){//在一个空白区域出现2或4
        num[a][b] = 2;
    }else{
        num[a][b] = 4;
    }
}


void print_map(){
    system("clear");
    printf("\t\t*****************************************\t\t\n");
    printf("\t\t      请按方向键或W、A、S、D移动滑块\n");//输出操作提示语句
    printf("\t\t          按ESC返回至主菜单\n");
    printf("\t\t\t---------------------\n\t\t\t");
    for (int j = 0; j<4; j++)//输出4*4的表格
    {
        for (int i = 0; i<4; i++)
            if (num[j][i] == 0)//格子没有值就是空白
                printf("|    ");
            else
                printf("|%4d",num[j][i]);//有值就显示
        printf("|\n");
        printf("\t\t\t---------------------\n\t\t\t");
    }
    printf("你的成绩：%d，移动了%d步\n",score,move);//输出得分和移动步数
}


void add(int *p)
{
    int i=0, b;
    while (i<3)
    {
        if (*(p + i) != 0)
        {
            for (b = i + 1; b < 4; b++)
            {
                if(*(p + b) != 0)
                {
                    if (*(p + i) == *(p + b))
                    {
                    score = score + (*(p + i)) + (*(p + b));
                    *(p + i) = *(p + i) + *(p + b);
                    *(p + b) = 0;
                    i = b + i;
                    ++ifappear;
                    break;
                    }
                    else
                    {
                        i = b;
                        break;
                    }
                }
            }
            if (b == 4)
                i++;
        }
        else
            i++;
    }
 
}


void game_play(){
    int b[4];//存放某一行或列坐标的值
    int e = 0;
    int i,j;
    appear();
    appear();
    while(1){
        if(ifappear != 0){
            appear();
        }
        print_map();
        key = getchch();
        switch(key){
            case 'W':
            case 'w':
                ifappear = 0;
                for (j = 0; j < 4; j++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        b[i] = num[i][j];
                        num[i][j] = 0;
                    }
                    add(b);
                    e = 0;
                    for (int g = 0; g < 4; g++)
                    {
                        if (b[g] != 0)
                        {
                            num[e][j] = b[g];
                            if (g != e)
                                ++ifappear;
                            e++;
                        }
                    }
                }
                if (ifappear!=0)
                    ++move;
                break;
            case 'A':
            case 'a':
                ifappear = 0;
                for (j = 0; j < 4; j++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        b[i] = num[j][i];
                        num[j][i] = 0;
                    }
                    add(b);
                    e = 0;
                    for (int g = 0; g < 4; g++)
                    {
                        if (b[g] != 0)
                        {
                            num[j][e] = b[g];
                            if (g!=e)
                                ++ifappear;
                            e++;
                        }
                    }
                }
                if (ifappear != 0)
                    ++move;
                break;
            case 'S':
            case 's':
                ifappear = 0;
                for (j = 0; j < 4; j++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        b[i] = num[i][j];
                        num[i][j] = 0;
                    }
                    add(b);
                    e = 3;
                    for (int g = 3; g>=0; g--)
                    {
                        if (b[g] != 0)
                        {
                            num[e][j] = b[g];
                            if (g != e)
                                ++ifappear;
                            e--;
                        }
                    }
                }
                if (ifappear != 0)
                    ++move;
                break;
            case 'D':
            case 'd':
                 ifappear = 0;
                for (j = 0; j < 4; j++)
                {
                    for (i = 0; i < 4; i++)
                    {
                        b[i] = num[j][i];
                        num[j][i] = 0;
                    }
                    add(b);
                    e = 3;
                    for (int g = 3; g >=0; g--)
                    {
                        if (b[g] != 0)
                        {
                            num[j][e] = b[g];
                            if (g!=e)
                                ++ifappear;
                            e--;
                        }
                    }
                }
                if (ifappear != 0)
                    ++move;
                break;
            case 27:
                return; 
        }
    }
}


void mes(){
    system("clear");
    printf("\t\t*****************************************\t\t\n");
    printf("\t\t******************游戏规则***************\n");
    printf("\t\t*****************************************\t\t\n");
    printf("\t\t玩家可以选择W、A、S、D去移动滑块\n");
    printf("\t\t玩家选择的方向上若有相同的数字则合并\n");
    printf("\t\t合并所得的所有新生成数字相加即为该步的有效得分\n");
    printf("\t\t玩家选择的方向行或列前方有空格则出现位移\n");
    printf("\t\t每移动一步，空位随机出现一个2或4\n");
    printf("\t\t棋盘被数字填满，无法进行有效移动，判负，游戏结束\n");
    printf("\t\t棋盘上出现2048，获胜，游戏结束\n");
    printf("\t\t请按任意键返回主菜单...\n");
    getchch();
    system("clear");

}


void menu_game()
{
    while(1){
        system("clear");
        printf("\t\t*****************************************\t\t\n");  //输出游戏菜单的图形
        printf("\t\t*              1、开始游戏              *\n");
        printf("\t\t*              2、游戏规则              *\n");
        printf("\t\t*              3、退出游戏              *\n");
        printf("\t\t*****************************************\n");
        printf("\t\t请输入1或2或3:[ ]\b\b");
        char ch = getchch();
        switch (ch)
        {
        case '1':
            game_play();//游戏开始函数
            break;
        case '2':
            mes();//游戏规则函数
            break;
        case '3':
            system("clear");
            return;//关闭游戏函数
        }
    }
}


int game_start(){
    int j, i;
    for (j = 0; j < 4; j++) //对4*4进行初始赋值为0
        for (i = 0; i < 4; i++)
            num[j][i] = 0;
    ifappear = 0;//判断是否应该随机出现2或4
    score = 0;//游戏得分
    move = 0;//游戏的移动步数
    menu_game();//调用主菜单函数    

    return 0;
}