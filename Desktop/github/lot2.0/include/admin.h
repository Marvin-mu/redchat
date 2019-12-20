#ifndef admin_h
#define admin_h

/*
* Function:sort_money
* Description:按用户金额排序查看
* Calls:
* Called By:enter_admin
* Input:
* Output:
* Return:void
* Others:
*/
void sort_money(user_link* left,user_link* right);
/*
* Function:enter_admin
* Description:进入管理员界面
* Calls:
* Called By:login_all
* Input:
* Output:
* Return:void
* Others:
*/
void enter_admin(user_link* user_head,i_l_link* issue_head);

#endif