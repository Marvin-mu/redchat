#ifndef menu_view_h
#define menu_view_h

typedef enum ch{
	REGIST = 49,//新用户注册
	LOGIN//系统所有人登录
}ch_t;


/*
* Function:menu
* Description:打印主界面
* Calls:
* Called By:main
* Input:
* Output:
* Return:void
* Others:
*/
void menu();
/*
* Function:print_admin_mes
* Description:打印管理员界面
* Calls:
* Called By:enter_admin
* Input:
* Output:
* Return:void
* Others:
*/
void print_admin_mes();
/*
* Function:print_worekr_mes
* Description:打印公正人员界面
* Calls:
* Called By:enter_worker
* Input:
* Output:
* Return:void
* Others:
*/
void print_worker_mes();
/*
* Function:print_user_mes
* Description:打印用户界面
* Calls:
* Called By:enter_user
* Input:
* Output:
* Return:void
* Others:
*/
void print_user_mes();

#endif