#ifndef login_h
#define login_h

#include"issue.h"
#include"user_lottery_link.h"

/*
* Function:regist_all
* Description:所有人登录,每次可以输3次
* Calls:getstring,enter_admin,enter_worker,enter_user,find_user,identifyCode
* Called By:main
* Input:
* Output:
* Return:void
* Others:
*/
void login_all(user_link* user_head,i_l_link* issue_head,u_l_link* u_l_head);


#endif
