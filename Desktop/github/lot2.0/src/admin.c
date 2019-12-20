#include<stdio.h>
#include<stdlib.h>
#include"menu_view.h"
#include"public.h"
#include"issue.h"
#include"regist.h"


void sort_money(user_link* left,user_link* right){
	if (left==right || right->next==left)
	{
		return;
	}
	user_link* l = left;
	user_link* r = right;
	user_link* key = left;
	user_t temp = {0};
	while(l!=r){
		while(l!=r){
			if (r->user.money>key->user.money)
			{
				break;
			}
			r = r->prev;
		}
		while(l!=r){
			if (l->user.money<key->user.money)
			{
				break;
			}
			l = l->next;
		}
		temp = l->user;
		l->user = r->user;
		r->user = temp;

	}
	temp = key->user;
	key->user = l->user;
	l->user = temp;
	sort_money(left,l->prev);
	sort_money(l->next,right);
	return;
}

void enter_admin(user_link* user_head,i_l_link* issue_head){
	system("clear");
	char name[20] = {0};
	while(1){
		print_admin_mes();
		int ch = getch();
		if (ch == 49)//发行彩票
		{
			i_l_link* p = issue_head->prev;
			if (p->issue_lottery.state == 1 || p == issue_head){
				insert_issue(issue_head);
				system("clear");
				printf("\n\t\t\t发行成功!\n");
			}else{
				system("clear");
				printf("\n\t\t\t未开奖,不能发行!\n");
			}
		}else if(ch == 50)//修改个人信息
		{
			system("clear");
			printf("\n\n\t\t请输入查找的账户名:");
			getstring(name,20);
			user_link* tar = find_user(user_head,name);
			if (tar != NULL)//存在此用户,打印信息
			{
				printf("\n\t\tname:%s\n",tar->user.name);
				printf("\n\t\tpswd:%s\n",tar->user.pswd);
				printf("\n\t\tmoney:%g\n",tar->user.money);
			}else{
				printf("\n\n\t\t此账户不存在\n");
			}
			printf("\n\t\t输入回车继续\n");
			while(getchar()==10){break;}
			system("clear");
		}else if(ch == 51)//按余额排序
		{
			system("clear");
			sort_money(user_head->next,user_head->prev);
			user_link* p = user_head->next;
			printf("\n\t\tname\tmoney\n");
			while(p!= user_head){
				printf("\n\n\t\t%s\t%g\n",p->user.name,p->user.money);
				p = p->next;
			}
			//system("pause");
			printf("\n\t\t输入回车继续\n");
			while(getchar()==10){break;}
			system("clear");
		}else{
			system("clear");
			break;
		}
	}

}
