#ifndef worker_h
#define worker_h

/*
* Function:str_li
* Description:字符串转数字
* Calls:
* Called By:
* Input:
* Output:
* Return:long int
* Others:
*/
long int str_li(char* str);
/*
* Function:comp_lot_id
* Description:比对号码,统计中奖情况
* Calls:
* Called By:
* Input:
* Output:
* Return:int
* Others:
*/
int comp_lot_id(u_l_link* u_l_head,int issue,char* lot_num);
/*
* Function:distribute
* Description:分发奖金
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void distribute(user_link* user_head,i_l_link* issue_head,u_l_link* u_l_head,int issue);
/*
* Function:run_lot
* Description:开奖
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void run_lot(user_link* user_head,i_l_link* issue_head,u_l_link* u_l_head);
/*
* Function:view_issue_history
* Description:查看期号链表
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void view_issue_history(i_l_link* issue_head);
/*
* Function:enter_worker
* Description:进入公正人员
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void enter_worker(user_link* user_head,i_l_link* issue_head,u_l_link* u_l_head);

#endif