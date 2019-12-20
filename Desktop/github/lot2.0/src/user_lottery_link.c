#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#include"user_lottery_link.h"
#include"issue.h"
#include"regist.h"
#include"public.h"

u_l_link* init_lot(){
	u_l_link* u_l_head = malloc(sizeof(u_l_link));
	memset(u_l_head,0,sizeof(u_l_link));
	u_l_head->next = u_l_head;
	u_l_head->prev = u_l_head;
	return u_l_head;
}
/*
返回0允许购买
返回1禁止够买
*/
int find_repeat(u_l_link* u_l_head,char* name,char* temp,int issue){
	int count = 0;//记录此号码购买次数
	u_l_link* p = u_l_head->next;
	if (p == u_l_head)
	{
		return 0;//允许购买返回0
	}
	while(p != u_l_head){
		if (strcmp(p->user_lottery.name,name) == 0 && p->user_lottery.issue == issue)
		{
			u_l_link* p1 = u_l_head->next;
			while(p1 != u_l_head){
				if (strcmp(p1->user_lottery.lot_num,temp)==0)
				{
					count += p1->user_lottery.note;
				}
				p1 = p1->next;
			}
		}
		p = p->next;
	}
	if (count >= 5)
	{
		return 1;//返回1不允许购买
	}else{
		return 0;
	}
}

/*
返回值注数
*/
int insert_lot(user_link* user_head,u_l_link* u_l_head,unsigned int issue,char name[20],i_l_link* pi){
	char temp[20] = {0};
	int note = 0;
	u_l_link* new_lot = malloc(sizeof(u_l_link));
	memset(new_lot,0,sizeof(u_l_link));
	new_lot->user_lottery.lottery_id = u_l_head->prev->user_lottery.lottery_id+1;
	u_l_head->user_lottery.lottery_id++;
	new_lot->user_lottery.issue = issue;
	strcpy(new_lot->user_lottery.name,name);
	printf("\n\t\e[1;31m买票提示:此系列彩票是选五个号码,第一个号码必须为10-50,后面的号码为(10-50),中奖状态1表示开过奖,0表示为开奖,同一个号码一个用户只能购买5注\e[0m\n");
	printf("\n\t1:机选\t2:手选\n");
	int ch = getch();
	if (ch == 49)
	{
		cmp_id(temp);
		printf("\n\t产生的号码为:%s\n",temp);
	}else{
		printf("\n\t请输入你选的号码:xx-xx-xx-xx-xx\e[14D");
		getstring(temp,20);
	}
	int ret = find_repeat(u_l_head,name,temp,issue);
	if (ret == 1)
	{
		printf("\n\t此号码注数已被限制\n");
		sleep(1);
		system("clear");
		free(new_lot);
		return -1;
	}
	strcpy(new_lot->user_lottery.lot_num,temp);
	while(1){
		printf("\n\t请输入注数:\e[K");
		scanf("%d",&note);
		while(getchar() != 10);
		if (0 < note && note < 6){
			break;
		}else{
			printf("\e[4A");
			printf("\n\n\t输入错误\e[K");
			continue;
		}
	}
	user_link* tar = find_user(user_head,name);
	if (tar->user.money < note*pi->issue_lottery.price)
	{
		printf("\n\t\t金额不足,请充值\n");
		sleep(1);
		system("clear");
		free(new_lot);
		return -1;
	}else{
		tar->user.money -= note*pi->issue_lottery.price;
	}
	new_lot->user_lottery.note = note;

	u_l_link* p  = u_l_head->prev;
	p->next = new_lot;
	u_l_head->prev = new_lot;
	new_lot->prev = p;
	new_lot->next = u_l_head;
	printf("\n\t\t输入回车继续");
	while(getchar() == '\n'){
		break;
	}
	system("clear");
	return note;
}


void u_l_load(u_l_link* head){
	u_l_link* p = head;
	user_lot temp = {0};
	FILE* fp = fopen("./doc/user_lot_mes.txt","r");
	if (fp == NULL){
		return ;
	}else{
		while(1){
			fread(&temp,sizeof(user_lot),1,fp);
			if (feof(fp) == 1){
				break;
			}
			u_l_link* new_lot = malloc(sizeof(u_l_link));
			memset(new_lot,0,sizeof(u_l_link));
			new_lot->user_lottery = temp;

			p->next = new_lot;
			new_lot->next = head;
			head->prev = new_lot;
			new_lot->prev = p;

			p = p->next; 
		}
		fclose(fp);
	}
}


void u_l_save(u_l_link* u_l_head){
	u_l_link* p = u_l_head->next;
	FILE* fp = fopen("./doc/user_lot_mes.txt","w");
	if (fp == NULL){
		return;
	}else{
		while(p != u_l_head){
			fwrite(&p->user_lottery,sizeof(user_lot),1,fp);
			p = p->next;
		}
	}
	fclose(fp);
}


void free_user_lot(u_l_link* u_l_head){
	u_l_link* p = u_l_head->next;
	while(p != u_l_head){
		p = p->next;
		free(p->prev);
	}
	free(p);
}
