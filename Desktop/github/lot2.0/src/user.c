#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"menu_view.h"
#include"regist.h"
#include"issue.h"
#include"user_lottery_link.h"
#include"public.h"
#include"game_2048.h"


void look_user(user_link* user_head,char* name){
	system("clear");
	user_link* res = find_user(user_head,name);//查看账户是否存在
	if (res != NULL){
		printf("\n\n\t\t姓名:%s\n",res->user.name);//账户存在
		printf("\n\n\t\t密码:%s\n",res->user.pswd);
		printf("\n\n\t\t余额:%g\n\n",res->user.money);
	}else{
		return;
	}
}


void update_user_mes(u_l_link* u_l_head,user_link* user_head,char* name){
	int ch = 0;
	while(1){
		char newname1[20]  ={0};
		char newname2[20]  ={0};
		system("clear");
		printf("\e[?25l");//隐藏光标
		printf("\n\n\n");
		printf("\t\t1.-修在账户名\n\n\n\t\t2.-修改密码\n\n\n");
		printf("\t\t按其他任意键推出\n");
		ch = getch();
		printf("\e[?25h");//显示光标
		fflush(stdout);
		system("clear");
		user_link* res = find_user(user_head,name);//找到此用户原来的链表节点
		if (ch == 49){//修改账户名
			if (res != NULL){
				printf("\n\n\t\t请输入修改后的账户名:");
				getstring(newname1,20);
				printf("\n\n\t\t请再次确认修改后的账户名:");
				getstring(newname2,20);
				if(newname1[0] == 27 || newname2[0] == 27){
					return;
				}else if(strcmp(newname1,newname2)==0){
					user_link* p = find_user(user_head,newname2);//查看是否允许修改,是否存在同名的
					if (p == NULL && strcmp(newname2,"admin") != 0 && strcmp(newname2,"worker") != 0)//修改用户链表中的和用户彩票链表中的用户名
					{
						u_l_link* p = u_l_head->next;
						while(p != u_l_head){
							if (strcmp(p->user_lottery.name,res->user.name) == 0)
							{
								strcpy(p->user_lottery.name,newname2);
							}
							p = p->next;
						}
						strcpy(res->user.name,newname2);//修改成功
						printf("\n\n\t\t账户名修改成功!\n");
						sleep(1);
						break;
					}else{
						printf("\n\n\t\t此账户名已被使用,修改失败\n");
						sleep(1);
						system("clear");
					}
				}else{
					printf("\t\t两次输入不一致\n");
					break;
				}
			}
		}else if(ch == 50){//修改密码
			if (res != NULL){
				for(int i = 0;i<3;i++){
					char newpswd1[20] = {0};
					char newpswd2[20] = {0};
					char oldpswd[20] = {0};
					printf("\n\n\t\t请输入旧密码:\e[K");
					getPassword(oldpswd);
					if (strcmp(oldpswd,res->user.pswd)==0)
					{
						printf("\n\n\t\t请输入修改后的密码:");
						getPassword(newpswd1);
						printf("\n\n\t\t请再次输入修改后的密码:");
						getPassword(newpswd2);
						if (newpswd1[0] == 27 || newpswd2[0] == 27){
							return;
						}else if(strcmp(newpswd1,newpswd2)==0 && strlen(newpswd2) > 2){
							strcpy(res->user.pswd,newpswd2);//修改成功
							printf("\n\n\t\t密码修改成功!\n");
							sleep(1);
							return;
						}else{
							printf("\n\n\t\t两次输入不一致\n");
							system("clear");
						}
					}else{
						printf("\t\t密码错误");
						printf("\e[3A");
						continue;
					}
				}
			}
		}else{//输入不合法
			break;
		}
	}
	system("clear");
}


int cancellate_user(user_link* user_head,u_l_link* u_l_head,char* name){//注销账户
	system("clear");
	int ch = 0;
	while(1){
		printf("\n\n\n\t\t\e[44m Y 确认\e[0m    \e[41m N 取消\e[0m\n");
		printf("\e[?25l");
		ch = getch();
		printf("\e[?25h");
		if(ch == 89 ||ch == 121)
		{
			break;
		}else{
			printf("\n\n\t\t\e[40m取消注销!\e[0m\n");
			sleep(1);
			return 1;
		}
	}
	system("clear");
	user_link* res = find_user(user_head,name);
	u_l_link* ret = u_l_head;
	if (res != NULL)//执行删除
	{
		res->prev->next = res->next;//从用户链表删除
		res->next->prev = res->prev;
		free(res);
		while(ret != u_l_head){
			ret = ret->next;
			if (strcmp(name,ret->user_lottery.name)==0)
			{
				ret->prev->next = ret->next;//从用户彩票链表删除
				ret->next->prev = ret->prev;
			}
			free(ret->next);
		}
		printf("\n\t\t注销成功!\n");
		sleep(1);
		return 0;
	}else{
		printf("\n\t\t注销失败!\n");
		sleep(1);
		return 0;
	}
}


void top_up(user_link* user_head,char* name){//充值账户
	system("clear");
	double get_money = 0;
	user_link* res = find_user(user_head,name);
	if (res != NULL)//执行
	{ 
		while(1){
			printf("\n\n\t\t充值范围:10-10000\n");
			printf("\n\t\t请输入充值金额:(放弃充值 0):\e[K");
			scanf("%lf",&get_money);
			while(getchar()!=10);
			if (10 < get_money && get_money <= 10000)
			{
				break;
			}else if(get_money == 0){
				system("clear");
				return;
			}else{
				printf("\n\t\t不符合充值范围\n");
				printf("\e[7A");
				continue;
			}
		}
		res->user.money += get_money;
		printf("\n\t\t充值成功!\e[K\n");
		printf("\n\t\t输入回车继续");
		while(getchar() == '\n'){
			break;
		}
		system("clear");
	}else{
		return;
	}
}


i_l_link* print_buy_mes(i_l_link* issue_head){
	system("clear");
	i_l_link* p = issue_head->next;
	while(1){
		if (p->issue_lottery.state == 0 && p != issue_head)
		{
			printf("\n\n\t期号    单价   状态     销售数量    奖池金额\n");
			printf("\t%d\t %d\t %d\t    %d\t    %g\n",p->issue_lottery.issue,p->issue_lottery.price,p->issue_lottery.state,p->issue_lottery.sales,p->issue_lottery.jackpot);
			return p;//返回链表中的位置
			break;
		}else if(p == issue_head){
			printf("\n\n\t\t无票在售\n");
			break;
		}
		p = p->next;
	}
	return NULL;
}


void buy_lot(user_link* user_head,u_l_link* u_l_head,char* name,i_l_link* p){
	unsigned int issue = p->issue_lottery.issue;
	while(1){
		//调用用户彩票链表
		int note = insert_lot(user_head,u_l_head,issue,name,p);
		if (note < 0)
		{
			return;
		}else{
			p->issue_lottery.sales += note;//记录销量
			p->issue_lottery.jackpot += note* p->issue_lottery.price;//奖池累加用户购买消费的金额
			return;
		}
	}
	return;
}


void search_winning_records(char* name,u_l_link* u_l_head,i_l_link* issue_head){
	system("clear");
	int issue = 0;
	printf("\n\n\t\t请输入查询期号:");
	scanf("%d",&issue);
	while(getchar() != 10);
	u_l_link* p1 = u_l_head->next;
	i_l_link* p2 = issue_head->next;
	while(p1 != u_l_head){
		if (strcmp(p1->user_lottery.name,name)==0)//找到此用户的彩票
		{
			p2 = issue_head->next;
			while(p2 != issue_head){
				if (p1->user_lottery.issue== issue && issue==p2->issue_lottery.issue && p1->user_lottery.win_amount != 0)//期号对应
				{
					printf("\n\n\t\t期号\t彩票唯一id\t中奖金额\n");
					printf("\n\t\t%d\t  %d\t\t%g\n",p1->user_lottery.issue,p1->user_lottery.lottery_id,p1->user_lottery.win_amount);
				}
				p2 = p2->next;
			}
		}
		p1 = p1->next;
	}
	printf("\n\t\t输入回车继续");
	while(getchar() == '\n'){
		break;
	}
	system("clear");
}


void find_user_history(char* name,u_l_link* u_l_head){
	u_l_link* p = u_l_head->next;
	system("clear");
	printf("\n\n\t\t期号 彩票唯一id    彩票号码 中奖状态 购买注数 中奖金额\n");
	while(p != u_l_head){
		if (strcmp(p->user_lottery.name,name)==0)
		{
			printf("\n\t\t%d\t%d\t%s\t%d\t%d\t%g\n",p->user_lottery.issue,p->user_lottery.lottery_id,p->user_lottery.lot_num,p->user_lottery.state,p->user_lottery.note,p->user_lottery.win_amount);
		}
		p = p->next;
	}
	printf("\n\t\t输入回车继续");
	while(getchar() == '\n'){
		break;
	}
	system("clear");
}


void enter_user(u_l_link* u_l_head,i_l_link* issue_head,user_link* user_head,char* name){
	while(1){
		system("clear");
		print_user_mes();
		printf("\e[?25l");
		int ch = getch();
		printf("\e[?25h");
		if (ch == 49){//查看个人信息
			look_user(user_head,name);
			printf("\n\t\t输入回车继续");
			while(getchar() == '\n'){
				system("clear");
				break;
			}
		}else if(ch == 50){//修改个人信息
			update_user_mes(u_l_head,user_head,name);
			return;
		}else if(ch == 51){//注销个人信息
			int yn = cancellate_user(user_head,u_l_head,name);
			if (yn == 0){
				return;
			}
		}else if(ch == 52){//充   值
			top_up(user_head,name);
		}else if(ch == 53){//查询中奖记录
			search_winning_records(name,u_l_head,issue_head);
		}else if(ch == 54){//买票
			i_l_link* p = print_buy_mes(issue_head);
			if (p == NULL)
			{
				sleep(1);
				system("clear");
			}else{
				buy_lot(user_head,u_l_head,name,p);
			}
		}else if(ch == 55){//查询购票记录
			find_user_history(name,u_l_head);
		}else if(ch == 56){//游   戏
			game_start();
		}else{
			system("clear");
			break;
		}
	}
}



