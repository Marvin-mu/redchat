#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"usr_mes.h"
#include<unistd.h>
#include<fcntl.h>

usr_mes_t* usr_init()
{
	usr_mes_t* head = malloc(sizeof(usr_mes_t));
	memset(head, 0, sizeof(usr_mes_t));
	head->next = head;
	head->prev = head;
	return head;
}

usr_mes_t* find_usr(usr_mes_t* head, char* name)
{
	usr_mes_t* p = head->next;
	while(p != head){
		if(strcmp(name, p->name) == 0){//重名
			return p;
		}
		p = p->next;
	}
	return NULL;
}

void insert_usr(usr_mes_t* head, char* name, char* pswd)
{
	usr_mes_t* p = head->prev;

	usr_mes_t* node = malloc(sizeof(usr_mes_t));
	memset(node, 0, sizeof(usr_mes_t));
	strcpy(node->name,name);
	strcpy(node->pswd,pswd);

	node->next = head;
	node->prev = p;
	p->next = node;
	head->prev = node;
}
void load_usr(usr_mes_t* head)
{
	int fd = open("./usr_mes.txt",O_RDWR | O_CREAT,0666);
	
	usr_mes_t* p = head->next;
	size_t size;
	while(1){
		usr_mes_t* node = malloc(sizeof(usr_mes_t));
		memset(node, 0, sizeof(usr_mes_t));
		if((size = read(fd,node->name,sizeof(node->name))) < 0){
			perror("read error");
			free(node);
			exit(1);
		}
		if(size == 0){
			free(node);
			return;
		}
		if((size = read(fd,node->pswd,sizeof(node->pswd))) < 0){
			perror("read error");
			free(node);
			exit(1);
		}
		p->next = node;
		node->next = head;
		node->prev = p;
		head->prev = node;

		p = p->next;
	}
}
void save_usr(usr_mes_t* head)
{
	int fd = open("./usr_mes.txt",O_RDWR | O_CREAT | O_APPEND,0666);
	usr_mes_t* p = head->next;
	size_t size;
	while(p != head){
		if((size = write(fd,p->name,sizeof(p->name))) < 0){
			perror("write error");
			exit(1);
		}
		if((size = write(fd,p->pswd,sizeof(p->pswd))) < 0){
			perror("write error");
			exit(1);
		}
		p = p->next;
	}
}

void free_usr(usr_mes_t* head)
{
	usr_mes_t* p = head->next;
	while(p != head){
		p = p->next;
		free(p->prev);
	}
	free(head);
}
