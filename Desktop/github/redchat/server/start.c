#include<stdio.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include<time.h>
#include<assert.h>
#include"online.h"
#include"usr_mes.h"
#include"type.h"

#define LEN 1105
int chat_fd[5] = {0};
static int group_len = 0;

extern usr_mes_t* usr_head;
extern online_t* online_head;

void client_mes(int fd, char* buff)
{
	data_t data;
	unpack_packet(buff, &data);
	//通过fd获得客户端的IP信息
	struct sockaddr_in clientaddr;
	memset(&clientaddr, 0, sizeof(clientaddr));
	socklen_t clientaddr_len = sizeof(clientaddr);
	if (getpeername(fd, (struct sockaddr*)&clientaddr, &clientaddr_len) < 0){
		perror("getpeername error");
		close(fd);
		return;
	}
	char ip[16] = "";
	int port = ntohs(clientaddr.sin_port);
	inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, ip, sizeof(ip));
	printf("用户名:%s\t客户端ip:%s\t端口号:%d\t fd: %d connected...\n",data.usrname, ip, port, fd);
	insert_online(online_head, ip, port, fd,data.usrname);
}

void login(int fd, char* buff)
{
	data_t data;
	size_t size;
	unpack_packet(buff, &data);
	usr_mes_t* tar = find_usr(usr_head, (void*)data.usrname);
	online_t* tar2 = find_online(online_head, data.usrname);
	if (tar == NULL || tar2 != NULL)//不存在
	{
		data.type = TYPE_ERROR;
		packaging(buff, &data);
		if ((size = write(fd, buff, LEN)) < 0){
			perror("write error");
			close(fd);
			exit(1);
		}
	}else {
		client_mes(fd, buff);
		data.type = TYPE_OK;
		packaging(buff, &data);
		if ((size = write(fd, buff, LEN)) < 0){
			perror("write error");
			close(fd);
			exit(1);
		}
	}
}

void regist(int fd, char* buff)
{
	data_t data;
	size_t size;
	unpack_packet(buff, &data);
	usr_mes_t* tar = find_usr(usr_head, data.usrname);
	if (tar == NULL)//不存在,给客户端返回ok包,提示注册成功
	{
		insert_usr(usr_head, data.usrname, data.pswd);//插入用户链表
		data.type = TYPE_OK;
		packaging(buff, &data);
		if ((size = write(fd, buff, LEN)) < 0){
			perror("write error");
			close(fd);
			exit(1);
		}
	}else {
		data.type = TYPE_ERROR;
		packaging(buff, &data);
		if ((size = write(fd, buff, LEN)) < 0){
			perror("write error");
			close(fd);
			exit(1);
		}
	}
}

void chat_with(int fd, char* buff)
{
	data_t data;
	size_t size;
	int savefd = -1;
	unpack_packet(buff, &data);
	//通过接收方的名字找出它的fd
	online_t* tarname = find_online(online_head,(void*)data.name_rec);
	if(tarname != NULL){
		savefd = tarname->fd;
	}
	//通过fd找出发送方的名字,存到数据包
	online_t* tar = find_online(online_head,(void*)&fd);
	if (tarname == NULL){
		if (strcmp(data.name_rec,"group") == 0){//客户端请求发起群聊
			for(int i = 0 ; i < group_len ; ++i){
				if (fd == chat_fd[i]){//在聊天组中
					savefd = 1;
				}
			}
			if (savefd == -1){//新用户加入聊天组
				chat_fd[group_len] = fd;
				group_len++;
			}
			strcpy(data.name_send, tar->name);
			packaging(buff, &data);
			for(int i = 0 ; i < group_len ; ++i){//给群组的每个用户发送消息
				if ((size = write(chat_fd[i], buff, LEN)) < 0){
					perror("write error");
					close(fd);
					exit(1);
				}
			}
		}else{
			data.type = TYPE_ERROR;
			strcpy(data.chat_data,"此用户不存在或者不在线...\n");
			packaging(buff, &data);
			if ((size = write(fd, buff, LEN)) < 0){
				perror("write error");
				close(fd);
				exit(1);
			}
			return;
		}
	}
	strcpy(data.name_send, tar->name);
	packaging(buff, &data);
	if ((size = write(savefd, buff, LEN)) < 0){
		perror("write error");
		close(fd);
		exit(1);
	}
}

//心跳记录
void alive(int fd, char* buff)
{
	data_t data;
	unpack_packet(buff, &data);
/*	if(t2 -t1 >= 15){
		printf("fd: %d close...\n", fd);
		remove_online(online_head, fd);
		close(fd);
	}*/
	printf("客户端:%d  is  %s\n", fd, data.chat_data);
}

void do_shell(int fd, char* buff)
{
	data_t data;
	unpack_packet(buff, &data);
	int savefd = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	system(data.chat_data);
	dup2(savefd, STDOUT_FILENO);
}

void look_online(int fd)
{
	char temp[10][LEN] = {""};
	char buff[LEN] = "";
	online_t* p = online_head->next;
	int i = 0;
	while(p != online_head){
		sprintf(temp[i], "用户名:%s\t客户端ip:%s\t端口号:%d\t fd: %d online...\n", p->name, p->ip, p->port, p->fd);
		strcat(buff, temp[i]);
		i++;
		p = p->next;
	}
	dprintf(fd,"%s",buff);
}

void do_exit(int fd)
{
	printf("%d port close...\n", fd);
	remove_online(online_head, fd);
	close(fd);
}

/*
void sig_handler(int signo){
	free_usr(usr_head);//释放堆栈
	free_online(online_head);
	pthread_exit(NULL);
}*/

void* do_server(void* arg)
{
	assert(arg);
/*	if (signal(SIGINT,sig_handler) < 0)
	{
		perror("sigint error");
		exit(1);
	}*/
	int fd = *(int*)arg;
	char buff[LEN];
	memset(&buff, 0 ,LEN);
	size_t size;
	while(1){//识别数据包类型
		memset(buff, 0, LEN);
		if((size = read(fd, buff, LEN)) < 0){
			perror("read error");
			close(fd);
			exit(1);
		}
		switch(buff[0]){
			case TYPE_LOGIN: // 登陆数据包
				login(fd,buff);
				break;
			case TYPE_REG:   // 注册数据包
				regist(fd, buff);
				break;
			case TYPE_MSG:   // 消息数据包
				chat_with(fd,buff);
				break;
			case TYPE_HEART: // 心跳数据包
				alive(fd, buff);
				break;
			case TYPE_CMD:   // 命令数据包
				do_shell(fd, buff);
				break;
			case TYPE_ONLINE:// 查看在线用户
				look_online(fd);
				break;
			case TYPE_OK:    // OK包
				break;
			case TYPE_ERROR: // 错误包
				break;
			case TYPE_EXIT: // 断开连接包
				do_exit(fd);
				break;
			default:
				break;
		}
	}
	return NULL;
}

void start_chat(int fd)
{
	int err;
	pthread_t th;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	//每个客户端线程以分离状态启动一个识别数据包的线程
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if((err = pthread_create(&th, &attr, do_server, (void*)&fd)) < 0){
		perror("pthread create error");
		close(fd);
		exit(1);
	}
	pthread_attr_destroy(&attr);
}
