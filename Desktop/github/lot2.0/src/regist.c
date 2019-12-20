#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"public.h"
#include"regist.h"


user_link* init_user(){
	user_link* head = malloc(sizeof(user_link));
	memset(head,0,sizeof(user_link));
	head->next = head;
	head->prev = head;
	return head;
}


user_link* find_user(user_link* head,char* name){
	user_link* p = head->next;
	while(p != head){
		if (strcmp(name,p->user.name) == 0){
			return p;
		}
		p = p->next;
	}
	return NULL;
}


void load_user(user_link* user_head){
	user_link* p = user_head;
	user_t temp = {0};
	FILE* fp = fopen("./doc/user_mes.txt","r");
	if (fp == NULL){
		return;
	}else{
		while(1){
			fread(&temp,sizeof(user_t),1,fp);
			if (feof(fp) == 1){
				break;
			}
			user_link* new = malloc(sizeof(user_link));
			memset(new,0,sizeof(user_link));
			new->user = temp;
			p->next = new;
			new->next = user_head;
			user_head->prev = new;
			new->prev = p;
			p = p->next; 
		}
		fclose(fp);	
	}
}


void save_user(user_link* user_head){
	user_link* p = user_head->next;
	FILE* fp = fopen("./doc/user_mes.txt","w");
	if (fp == NULL)
	{
		return;
	}else{
		while(p != user_head){
			fwrite(&p->user,sizeof(user_t),1,fp);
			p = p->next;
		}
	}
	fclose(fp);
}


void free_user(user_link* user_head){
	user_link* p = user_head->next;
	while(p != user_head){
		p = p->next;
		free(p->prev);
	}
	free(p);
}


void regist_all(user_link* user_head){
	system("clear");
	char name[20];
	char pswd1[20];
	char pswd2[20];
	int flag1 = 1;
	int flag = 1;
	while(flag){
		memset(name,0,20);
		printf("\n\t\t账户名至少3位,请输入账户名(esc强制退出):\e[K");
		getstring(name,20);
		if (strcmp(name,"admin") == 0){//不能与管理员帐号相同
			printf("\n\t\t此帐号不允许注册\e[5A");
		}else if (strcmp(name,"worker")==0){//不能与公证员帐号相同
			printf("\n\t\t此帐号不允许注册\e[5A");
		}else if(name[0] == 27){
			return;
		}else if(strlen(name) < 3){//账户名至少为3位
			printf("\n\t\t账户名少于3位\e[6A");
		}else{//用户注册
			user_link* new = malloc(sizeof(user_link));
			memset(new,0,sizeof(user_link));
			user_link* res = find_user(user_head,name);//查看账户是否存在
			if (res != NULL){
				printf("\n\t\t\t账户名已经存在");
				sleep(1);
				free(new);
			}else{
				strcpy(new->user.name,name);
				while(flag1){
					memset(pswd1,0,20);
					memset(pswd2,0,20);
					printf("\n\t\t密码至少3位,请输入注册密码:\e[K");
					getPassword(pswd1);
					printf("\n\t\t请再次确认密码(esc强制退出):\e[K");
					getPassword(pswd2);
					if(strcmp(pswd1,pswd2)==0 && strlen(pswd2) >= 3){//密码至少为3位
						strcpy(new->user.pswd,pswd2);
						user_link* p = user_head->prev;//找尾节点
						p->next = new;
						new->next = user_head;
						new->prev = p;
						user_head->prev = new;
						printf("\n\t\t注册成功\e[K\n");
						sleep(1);
						system("clear");
						flag1 = 0;
					}else if(pswd1[0] == 27 || pswd2[0] == 27){
						free(new);
						return;
					}else{
						printf("\n\t\t两次密码不一样,请重新输入!\033[6A\n");
					}
				}
			}
			flag = 0;
		}
	}
}
