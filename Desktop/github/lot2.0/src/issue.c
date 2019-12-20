#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include"issue.h"

i_l_link* init_issue(){
	i_l_link* issue_head = malloc(sizeof(i_l_link));
	memset(issue_head,0,sizeof(i_l_link));
	issue_head->next = issue_head;
	issue_head->prev = issue_head;
	return issue_head;
}


void load_issue(i_l_link* issue_head){
	i_l_link* p = issue_head;
	issue_t temp = {0};
	FILE* fp = fopen("./doc/issue_mes.txt","r");
	if (fp == NULL){
		printf("加载失败.......\n");
		return;
	}else{
		while(1){
			fread(&temp,sizeof(issue_t),1,fp);
			if (feof(fp) == 1){
				break;
			}
			i_l_link* new_lot = malloc(sizeof(i_l_link));
			memset(new_lot,0,sizeof(i_l_link));
			new_lot->issue_lottery = temp;
			p->next = new_lot;
			new_lot->next = issue_head;
			issue_head->prev = new_lot;
			new_lot->prev = p;
			p = p->next; 
		}
		fclose(fp);	
	}
}

/*
产生5个数字中奖字符串函数
*/
char* cmp_id(char* str){
	srand(time(0));
	int data = 0;
	data = rand()%(50-10)+10;
	sprintf(str,"%d",data);
	strcat(str,"-");
	for (int i = 0; i < 4; ++i)
	{
		char temp[3];
		char temp1[3] = {"0"};
		data = rand()%(50-1)+1;
		sprintf(temp,"%d",data);
		if (strlen(temp)==1)
		{
			strcat(temp1,temp);
			strcpy(temp,temp1);
			strcat(str,temp);
			if (i<3){
				strcat(str,"-");
			}
		}else{
			strcat(str,temp);
			if (i<3){
				strcat(str,"-");
			}
		}
	}
	return str;
}


void insert_issue(i_l_link* issue_head){//发行彩票
	unsigned int price = 0;
	char win_id[30] = {0};
	i_l_link* new_issue = malloc(sizeof(i_l_link));
	memset(new_issue,0,sizeof(i_l_link));
	new_issue->issue_lottery.issue = issue_head->prev->issue_lottery.issue+11;
	issue_head->issue_lottery.issue += 11;
	printf("\n\t\t请输入此期彩票的单价:");
	scanf("%d",&price);
	while(getchar()!=10);
	new_issue->issue_lottery.price = price;
	new_issue->issue_lottery.state = 0;
	strcpy(new_issue->issue_lottery.win_id,cmp_id(win_id));//机选中奖号码
	printf("中奖号码:%s\n",new_issue->issue_lottery.win_id);
	//strcpy(new_issue->issue_lottery.win_id,"11-01-11-11-11");//手动设置中奖号码
	i_l_link* p = issue_head->prev;
	new_issue->issue_lottery.jackpot = 50000 + p->issue_lottery.jackpot;
	//头插法,寻找尾节点，然后让尾节点的next指向newstu
	p->next = new_issue;
	new_issue->next = issue_head;
	new_issue->prev = p;
	issue_head->prev = new_issue; 
}
/*
返回值:期号
*/
i_l_link* find_issue(i_l_link* issue_head,int issue){
	i_l_link* p = issue_head->next;
	while(p != issue_head){
		if (issue == p->issue_lottery.issue){
			return p;
		}
		p= p->next;
	}
	return 	NULL;
}


void save_issue(i_l_link* issue_head){
	i_l_link* p = issue_head->next;
	FILE* fp = fopen("./doc/issue_mes.txt","w");
	if (fp == NULL){
		printf("加载失败.......\n");
		return;
	}else{
		while(p != issue_head){
			fwrite(&p->issue_lottery,sizeof(issue_t),1,fp);
			p = p->next;
		}
	}
	fclose(fp);
}


void free_issue(i_l_link* issue_head){
	i_l_link* p = issue_head->next;
	while(p != issue_head){
		p = p->next;
		free(p->prev);
	}
	free(p);
}
