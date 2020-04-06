#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"online.h"



online_t* online_init(void)
{
	online_t* head = malloc(sizeof(online_t));
	memset(head, 0, sizeof(online_t));
	head->next = head;
	head->prev = head;
	return head;
}

void insert_online(online_t* head, char* ip, int port, int fd, char* name)
{
	online_t* node = malloc(sizeof(online_t));
	strcpy(node->ip, ip);
	node->port = port;
	node->fd = fd;
	strcpy(node->name,name);

	online_t* p = head->prev;
	p->next = node;
	node->prev = p;
	node->next = head;
	head->prev = node;
}


online_t* find_online(online_t* head, void* name)
{
	online_t* p = head->next;
	while(p != head){
		if (strcmp(p->name,(char*)name) == 0 || *(int*)name == p->fd){//此用户已经在线,
			return p;
		}
		p = p->next;
	}
	return NULL;
}


void remove_online(online_t* head, int fd)
{
	online_t* p = head->next;
	while(1){
		if (p->fd == fd)
		{
			p->prev->next = p->next;
			p->next->prev = p->prev;
			free(p);
			return;
		}
		p = p->next;
	}
}

void free_online(online_t *head)
{
	online_t* p = head->next;
	while(p != head){
		p = p->next;
		free(p->prev);
	}
	free(head);
}
