#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"menu_view.h"
#include"issue.h"
#include"user_lottery_link.h"
#include"public.h"

long int str_li(char* str){
	long int num = 0;
	for (int i = 0; i < strlen(str); ++i)
	{
		if (str[i] == '-')
		{
			num *= 10;
		}else{
			num = num * 10 + *(str+i) - 48;
		}
	}
	return num * 10;
}


int comp_lot_id(u_l_link* u_l_head,int issue,char* lot_num){
	int count[3] = {0};
	//第一个位置存放中5个号码的人数,第一个位置存放中4个号码的人数,第一个位置存放中3个号码的人数
	long int num1 = 0;//开奖号码
	long int num2 = 0;//用户够买的号码
	u_l_link* p = u_l_head->next;
	while(p != u_l_head){//在用户彩票链表中查找期号相同的彩票
		if (p->user_lottery.issue == issue){
			num1 = str_li(lot_num);
			//printf("num1:%ld\n",num1);
			num2 = str_li(p->user_lottery.lot_num);
			//printf("num2:%ld\n",num2);
			//统计不同等级中奖人数
			int co = 0;
			for (int i = 0; i < 5; ++i){
				if(num1%1000==num2%1000){
					co++;
				}
				num1 /= 1000;
				num2 /= 1000;
			}
			//printf("co :%d\n",co);
			if (co == 5){
				p->user_lottery.state = 1;
				count[0]++;
			}else if(co == 4){
				p->user_lottery.state = 1;
				count[1]++;
			}else if(co == 3){
				p->user_lottery.state = 1;
				count[2]++;
			}
			//printf("%d %d %d\n",count[0],count[1],count[2]);
		}
		p = p->next;
	}
	//分配奖金
	return (3 * count[0] + 2 * count[1] + count[2]) * 2;
}


void distribute(user_link* user_head,i_l_link* issue_head,u_l_link* u_l_head,int issue){
	i_l_link* p1 = find_issue(issue_head,issue);
	int count = comp_lot_id(u_l_head,issue,p1->issue_lottery.win_id);
	u_l_link* p2 = u_l_head->next;
	while(p2 != u_l_head){
		if (p2->user_lottery.issue == issue)//在用户彩票链表中查找期号相同的彩票,进行一次统计
		{
			long int num1 = 0;
			long int num2 = 0;
			num1 = str_li(p2->user_lottery.lot_num);
			num2 = str_li(p1->issue_lottery.win_id);
			int co = 0;
			for (int i = 0; i < 5; ++i){
				if(num1%1000 == num2%1000){
					co++;
				}
				num1 /= 1000;
				num2 /= 1000;
			}
			user_link* tar = find_user(user_head,p2->user_lottery.name);
			if (co == 5){
				p2->user_lottery.win_amount = p1->issue_lottery.jackpot*3/count;
			}else if(co == 4){
				p2->user_lottery.win_amount = p1->issue_lottery.jackpot*2/count;
				
			}else if(co == 3){
				p2->user_lottery.win_amount = p1->issue_lottery.jackpot*1/count;
			}
			p1->issue_lottery.jackpot -= p2->user_lottery.win_amount;
			tar->user.money += p2->user_lottery.win_amount;
		}
		p2 = p2->next;
	} 
}


void run_lot(user_link* user_head,i_l_link* issue_head,u_l_link* u_l_head){
	unsigned int issue = 0;
	if (issue_head->next == issue_head){
		printf("\n\n\t\t不存在可开奖的期号!\n");
		sleep(1);
		system("clear");
		return;
	}
	printf("\n\n\t\t请输入期号:");
	scanf("%d",&issue);
	while(getchar()!=10);
	i_l_link* tar = find_issue(issue_head,issue);//查看期号是否存在,并返回期号结构体
	if (tar == NULL || tar->issue_lottery.sales == 0 || tar->issue_lottery.state == 1){
		printf("\n\n\t\t不存在此期或者无人购买,不能开奖\n");
		sleep(1);
		system("clear");
		return;
	}else{
		tar->issue_lottery.state = 1;//期号中开奖状态更改
		printf("\n\t\t此期的中奖号码为:%s\n",tar->issue_lottery.win_id);
		distribute(user_head,issue_head,u_l_head,tar->issue_lottery.issue);//开奖后分配奖金
		printf("\n\t\t输入回车继续");
		while(getchar() == '\n'){
			break;
		}
		system("clear");	
	}

}


void view_issue_history(i_l_link* issue_head){
	i_l_link* pa = issue_head->next;
	char temp[20] = {0};
	printf("\n\n\t期号    单价   状态       中奖号码   销售数量  奖池金额\n");
	while(pa != issue_head){
		if (pa->issue_lottery.state==1)
		{
			strcpy(temp,pa->issue_lottery.win_id);
		}else{
			strcpy(temp,"xx-xx-xx-xx-xx");
		}
		printf("\t%d\t%d\t%d\t%s\t%d\t%g\n",pa->issue_lottery.issue,pa->issue_lottery.price,pa->issue_lottery.state,temp,pa->issue_lottery.sales,pa->issue_lottery.jackpot);
		pa = pa->next;
	}
	printf("\n\t输入回车继续");
	while(getchar() == '\n'){break;}
	system("clear");
}


void enter_worker(user_link* user_head,i_l_link* issue_head,u_l_link* u_l_head){
	system("clear");
	while(1){
		print_worker_mes();
		printf("\e[?25l");
		int ch = getch();
		printf("\e[?25h");
		system("clear");
		if (ch == 49){
			run_lot(user_head,issue_head,u_l_head);//开奖
		}else if(ch == 50){
			view_issue_history(issue_head);//查看发行历史
		}else{
			break;
		}
	}
	
}
