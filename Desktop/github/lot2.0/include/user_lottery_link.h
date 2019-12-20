
#ifndef user_lottery_link_h
#define user_lottery_link_h


#include"issue.h"
#include"regist.h"

typedef struct user_lot{
	unsigned int issue;//期号
	unsigned int lottery_id;//彩票唯一id
	char lot_num[20];//彩票号码
	char name[20];//购买者帐号
	unsigned int state;//中奖状态
	unsigned int note;//已购买彩票注数
	double win_amount;//中奖金额
}user_lot;

typedef struct user_lot_link{
	user_lot user_lottery;
	struct user_lot_link* prev;
	struct user_lot_link* next;
}u_l_link;

/*
* Function:look_user
* Description:用户彩票链表初始化
* Calls:
* Called By:
* Input:
* Output:
* Return:u_l_link*
* Others:
*/
u_l_link* init_lot();
/*
* Function:find_repeat
* Description:查看某个账户名下某一期的号码是否超过5注
* Calls:
* Called By:
* Input:
* Output:
* Return:int
* Others:
*/
int find_repeat(u_l_link* u_l_head,char* name,char* temp,int issue);
/*
* Function:insert_lot
* Description:用户购买彩票,插入链表
* Calls:
* Called By:
* Input:
* Output:
* Return:int,注数
* Others:
*/
int insert_lot(user_link* user_head,u_l_link* u_l_head,unsigned int issue,char* name,i_l_link* pi);
/*
* Function:u_l_load
* Description:加载用户彩票链表
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void u_l_load(u_l_link* head);
/*
* Function:u_l_save
* Description:保存用户彩票链表
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void u_l_save(u_l_link* head);
/*
* Function:free_user_lot
* Description:释放用户彩票链表
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void free_user_lot(u_l_link* head);

#endif