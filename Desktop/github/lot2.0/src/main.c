#include<stdio.h>
#include<stdlib.h>

#include"menu_view.h"
#include"regist.h"
#include"public.h"
#include"login.h"
#include"issue.h"
#include"user_lottery_link.h"


int main()
{
	int flag = 0;
	//链表的定义以及加载
	i_l_link* issue_head = init_issue();
	unsigned int issue = 1900;
	issue_head->issue_lottery.issue = issue;
	load_issue(issue_head);//加载期号链表

	u_l_link* u_l_head = init_lot();
	unsigned int lottery_id = 1000;
	u_l_head->user_lottery.lottery_id = lottery_id;
	u_l_load(u_l_head);//加载用户彩票链表

	user_link* user_head = init_user();
	load_user(user_head);//加载用户链表

	while(!flag){
		system("clear");
		menu();
		printf("\e[?25l");//隐藏光标
		int ch = getch();
		printf("\e[?25h");//显示光标
		switch(ch){
			case REGIST:
				regist_all(user_head);//进入注册功能
				break;
			case LOGIN:
				login_all(user_head,issue_head,u_l_head);//进入登录功能
				break;
			default:
				flag = 1;
				break;
		}
	}
	//链表的保存释放
	save_user(user_head);
	free_user(user_head);

	save_issue(issue_head);
	free_issue(issue_head);

	u_l_save(u_l_head);
	free_user_lot(u_l_head);
}
