#ifndef issue_h
#define issue_h

typedef struct Issue_lottery{
	unsigned int issue;//期号
	unsigned int price;//单价
	unsigned int state;//状态
	char win_id[20];//中奖号码
	int sales;//售出总数
	double jackpot;//奖池金额
}issue_t;

typedef struct Issue_lottery_link{
	issue_t issue_lottery;
	struct Issue_lottery_link* prev;
	struct Issue_lottery_link* next;
}i_l_link;

/*
* Function:init_issue
* Description:初始化期号链表
* Calls:
* Called By:
* Input:
* Output:
* Return:i_l_link*
* Others:
*/
i_l_link* init_issue();
/*
* Function:load_issue
* Description:加载期号链表信息
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void load_issue(i_l_link*);
/*
* Function:cmp_id
* Description:随机产生中奖号码
* Calls:
* Called By:
* Input:
* Output:
* Return:char*
* Others:
*/
char* cmp_id(char* str);
/*
* Function:insert_issue
* Description:发行彩票,插入新的链表
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void insert_issue(i_l_link*);
/*
* Function:find_issue
* Description:按期号遍历期号链表
* Calls:
* Called By:
* Input:
* Output:
* Return:i_l_link*
* Others:
*/
i_l_link* find_issue(i_l_link* issue_head,int issue);
/*
* Function:save_issue
* Description:保存期号链表
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void save_issue(i_l_link*);
/*
* Function:free_issue
* Description:释放期号链表节点
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void free_issue(i_l_link* issue_head);



#endif