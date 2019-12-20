#include<stdio.h>
#include<string.h>



void menu(){
	printf("\n\n\t----------\e[31;5m欢迎使用中国福利彩票中心\e[0m----------\n\n");
	printf("\t\t      \e[45m1:注册\e[0m    \e[45m2:登录\e[0m             \n");
	printf("\n");
	printf("\t\t\t其它键退出                 \n");
	printf("\t--------------------------------------------\n\n");
}

void print_admin_mes(){
	printf("\n\n");
	printf("\t\t-------\e[31;102m欢迎进入管理员\e[0m-------\n\n");
	printf("\t\t\t\e[32m1.-发行彩票\n\n");
	printf("\t\t\t2.-按用户帐号查询\n\n");
	printf("\t\t\t3.-按用户余额排序\e[0m\n\n");
	printf("\t\t\t其它键退出\n");
}
void print_worker_mes(){
	printf("\n\n");
	printf("\t\t------\e[31;5m欢迎进入公正人员界面\e[0m------\n\n");
	printf("\t\t\t1.-开奖\n\n");
	printf("\t\t\t2.-查看发行历史\n\n");
	printf("\t\t\t其它键退出\n");
}
void print_user_mes(){
	printf("\n\n");
	printf("\t\t-------\e[44;5m欢迎进入用户界面\e[0m-------\n\n");
	printf("\t\t\t\e[96m1.-查看个人信息\n\n");
	printf("\t\t\t2.-修改个人信息\n\n");
	printf("\t\t\t3.-注销个人信息\n\n");
	printf("\t\t\t4.-充   值\n\n");
	printf("\t\t\t5.-查询中奖记录\n\n");
	printf("\t\t\t6.-买   票\n\n");
	printf("\t\t\t7.-查询购票记录\e[0m\n\n");
	printf("\t\t\t\e[91m8.-游   戏\e[0m\n\n");
	printf("\t\t\t其它键退出\n");
}
