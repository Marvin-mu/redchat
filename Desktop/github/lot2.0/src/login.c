#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"regist.h"
#include"issue.h"
#include"user_lottery_link.h"
#include"public.h"
#include"admin.h"
#include"worker.h"
#include"user.h"


void login_all(user_link* user_head,i_l_link* issue_head,u_l_link* u_l_head){
	char name[20] = {0};
	char pswd[20] = {0};
	int ret = 0;
	for (int i = 0; i < 3; ++i)
	{
		system("clear");
		printf("\n\t\t请输入账户名:");
		getstring(name,20);
		ret = identifyCode();
		if (strcmp(name,"admin") == 0)//进入管理员
		{
			if (ret == -1){
				return;
			}else if(ret == 1){
				printf("\n\t\t请输入密码:");
				getPassword(pswd);
				if (strcmp(pswd,"123456")==0)
				{
					enter_admin(user_head,issue_head);
					return;
				}else{
					printf("\n\t\t\t登录失败!");
				}
			}else{
				continue;
			}
		}
		else if(strcmp(name,"worker")==0)//公正员
		{
			if (ret == -1){
				return;
			}else if (ret == 1){
				printf("\n\t\t请输入密码:");
				getPassword(pswd);
				if (strcmp(pswd,"123456")==0)
				{
					enter_worker(user_head,issue_head,u_l_head);
					return;
				}else{
					printf("\n\t\t\t登录失败");
				}
			}else{
				continue;
			}
		}else{//用户
			char pswd[20] = {0};
			user_link* res = find_user(user_head,name);
			if(res != NULL){//用户账户名存在
				if (ret == -1){
					return;
				}
				else if (ret == 1)//验证码正确
				{
					printf("\n\t\t请输入密码:\e[K");
					getPassword(pswd);
					if (strcmp(pswd,res->user.pswd)==0){
						enter_user(u_l_head,issue_head,user_head,name);
						return;
					}else{
						printf("\n\t\t\t登录失败");
					}
				}else{
					continue;
				}
			}else{
				printf("\n\t\t此账户不存在\n");
				sleep(1);
			}
		}
	}
}
