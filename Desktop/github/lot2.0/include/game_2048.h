#ifndef game_2048_h
#define game_2048_h


/*
* Function:getchch
* Description:字符串获取,不经过缓存区
* Calls:
* Called By:
* Input:
* Output:
* Return:char
* Others:
*/
char getchch();
/*
* Function:appear
* Description:保存空白格子信息,随机出现一个2或者4
* Calls:
* Called By:game_play
* Input:
* Output:
* Return:void
* Others:
*/
void appear();
/*
* Function:print_map
* Description:打印格子
* Calls:
* Called By:game_play
* Input:
* Output:
* Return:void
* Others:
*/
void print_map();
/*
* Function:add
* Description:相同的进行加法运算并移动
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void add(int *p);
/*
* Function:mes
* Description:打印游戏规则
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void mes();
/*
* Function:menu_game
* Description:游戏开始界面
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void menu_game();
/*
* Function:game_start
* Description:游戏进入接口
* Calls:
* Called By:
* Input:
* Output:
* Return:int
* Others:
*/
int game_start();

#endif