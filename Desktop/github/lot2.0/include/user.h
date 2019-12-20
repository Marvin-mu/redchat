#ifndef user_h
#define user_h

#include"issue.h"
#include"user_lottery_link.h"

/*
* Function:look_user
* Description:查看用户自己的信息
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void look_user(user_link* user_head,char* name);
/*
* Function:update_user_mes
* Description:修改账户信息
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void update_user_mes(u_l_link* u_l_head,user_link* user_head,char* name);/*
* Function:cancellate_user
* Description:注销账户信息
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
int cancellate_user(user_link* user_head,u_l_link* u_l_head,char* name);
/*
* Function:top_up
* Description:账户金额充值
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void top_up(user_link* user_head,char* name);
/*
* Function:print_buy_mes
* Description:打印在售卖的彩票信息
* Calls:
* Called By:
* Input:
* Output:
* Return:i_l_link*
* Others:
*/
i_l_link* print_buy_mes(i_l_link* issue_head);
/*
* Function:buy_lot
* Description:购买彩票
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void buy_lot(user_link* user_head,u_l_link* u_l_head,char* name,i_l_link* p);
/*
* Function:search_winning_records
* Description:查询中奖记录
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void search_winning_records(char* name,u_l_link* u_l_head,i_l_link* issue_head);
/*
* Function:find_user_history
* Description:查看用户购票记录
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void find_user_history(char* name,u_l_link* u_l_head);
/*
* Function:enter_user
* Description:进入用户界面
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void enter_user(u_l_link* u_l_head,i_l_link* issue_head,user_link* user_head,char* name);

#endif