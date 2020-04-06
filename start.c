#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
#include"public.h"
#include"type.h"

#define LEN 1105
unsigned int exit_read = 0;//退出聊天关闭read的线程

char login(int sockfd)
{
	data_t data;
	size_t size;
	memset(&data, 0, sizeof(data_t));
	char buff[LEN] = "";
	printf("please input usrname:");fflush(stdout);
	getstring(data.usrname, 19);
	printf("please input usrpswd:");fflush(stdout);
	getstring(data.pswd, 19);
	data.type = TYPE_LOGIN;
	packaging(buff, &data);
	if ((size = write(sockfd, buff, LEN)) < 0){
		perror("write error");
		close(sockfd);
		exit(1);
	}
	printf("等待服务器返回结果.....\n");
	memset(buff, 0, LEN);
	if((size = read(sockfd, buff, LEN)) < 0){
		perror("read error");
		close(sockfd);
		exit(1);
	}else if(size == 0){
		return 'a';
	}
	return buff[0];
}

char regist(int sockfd)
{
	data_t data;
	size_t size;
	memset(&data, 0, sizeof(data_t));
	char buff[LEN] = "";
	printf("please input usrname:");fflush(stdout);
	getstring(data.usrname, 19);
	printf("please input usrpswd:");fflush(stdout);
	getstring(data.pswd, 19);
	data.type = TYPE_REG;
	packaging(buff, &data);
	if ((size = write(sockfd, buff, LEN)) < 0){
		perror("write error");
		close(sockfd);
		exit(1);
	}
	printf("等待服务器返回结果.....\n");
	memset(buff, 0, LEN);
	if((size = read(sockfd, buff, LEN)) < 0){
		perror("read error");
		close(sockfd);
		exit(1);
	}else if(size == 0){
		return 'a';
	}
	return buff[0];
}

void* alive_server(void* arg)
{
	int sockfd = *(int*)arg;
	char buff[LEN] = "";
	data_t data;
	data.type = '3';
	strcpy(data.chat_data,"alive");
	while(1){
		packaging(buff, &data);
		write(sockfd, buff, LEN);
		sleep(3);
	}
}

void send_shell(int sockfd)
{
	data_t data;
	memset(&data, 0, sizeof(data_t));
	char buff[LEN];
	size_t size;
	data.type = '4';
	printf("please input shell:");
	fflush(stdout);
	getstring(data.chat_data, 1024);
	if (data.chat_data[0] == 27){//esc强制退出
		return;
	}
	packaging(buff, &data);
	if ((size = write(sockfd, buff, LEN)) < 0){
		perror("write error");
		close(sockfd);
		exit(1);
	}
	printf("等待服务器返回结果.....\n");
	memset(buff, 0, LEN);
	if((size = read(sockfd, buff, LEN)) < 0){
		perror("read error");
		close(sockfd);
		exit(1);
	}else if(size == 0){
		return;
	}
	printf("%s",buff);
	printf("please input enter....\n");
	while(getchar() == '\n'){
		return;
	}
}

void* read_mes(void* arg)
{
	int sockfd = *(int*)arg;
	data_t data;
	memset(&data, 0, sizeof(data_t));
	char buff[LEN];
	size_t size;
	while(1){
		if((size = read(sockfd, buff, LEN)) < 0){
			perror("read error");
			close(sockfd);
			exit(1);
		}else if(size == 0){
			printf("\nno message...\n");
			return NULL;
		}
		if(exit_read){
			exit_read = 0;
			return NULL;
		}
		unpack_packet(buff, &data);
		printf("\nsend by:%s\t%s\n",data.name_send, data.chat_data);
		if(data.type == TYPE_ERROR){
			return NULL;
		}
	}
}

void chat_with(int sockfd,int flag)
{
	int err;
	pthread_t th;
	if((err = pthread_create(&th, NULL, read_mes, (void*)&sockfd)) < 0){
		perror("pthread create read_mes error");
		close(sockfd);
		exit(1);
	}
	data_t data;
	memset(&data, 0, sizeof(data_t));
	size_t size;
	char buff[LEN];
	if (flag){
		strcpy(data.name_rec,"group");
	}else{
		printf("input name_rec:");fflush(stdout);
		getstring(data.name_rec, 20);
	}
	data.type = TYPE_MSG;
	while(1){
		printf("please input mes(esc exit):");
		fflush(stdout);
		getstring(data.chat_data, 1024);
		if (data.chat_data[0] == 27){//esc强制退出
			strcpy(data.chat_data,"offline");
			packaging(buff, &data);
			if ((size = write(sockfd, buff, LEN)) < 0){
				perror("write error");
				close(sockfd);
				exit(1);
			}
			exit_read = 1;
			return;
		}
		packaging(buff, &data);
		if ((size = write(sockfd, buff, LEN)) < 0){
			perror("write error");
			close(sockfd);
			return;
		}
	}
	pthread_join(th,NULL);
}

void look_alive(int sockfd)
{
	data_t data;
	memset(&data, 0, sizeof(data_t));
	size_t size;
	char buff[LEN];
	data.type = '5';
	packaging(buff, &data);
	if ((size = write(sockfd, buff, LEN)) < 0){
		perror("write error");
		close(sockfd);
		return;
	}
	printf("等待服务器返回结果.....\n");
	memset(buff, 0, LEN);
	if((size = read(sockfd, buff, LEN)) < 0){
		perror("read error");
		close(sockfd);
		exit(1);
	}else if(size == 0){
		return;
	}
	printf("%s",buff);
	printf("please input enter....\n");
	while(getchar() == '\n'){
		return;
	}
}

void do_exit(int sockfd)
{
	
	data_t data;
	memset(&data, 0, sizeof(data_t));
	size_t size;
	char buff[LEN];
	data.type = '8';
	packaging(buff, &data);
	if ((size = write(sockfd, buff, LEN)) < 0){
		perror("write error");
		close(sockfd);
		return;
	}
	printf("向服务器发送断开连接成功.....\n");
}

int in_sec(int sockfd)
{
	int err;
	pthread_t th;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);//心跳机制
	if((err = pthread_create(&th, &attr, alive_server, (void*)&sockfd)) < 0){
		perror("pthread create do_judgment error");
		close(sockfd);
		exit(1);
	}
	char ch;
	int flag = 1;
	while(flag){
		second_view();
		ch = getchar();
		while(getchar()!='\n');
		switch(ch){
			case SEND_SHELL:
				send_shell(sockfd);
				break;
			case CHAT_SOMEONE:
				chat_with(sockfd,0);
				break;
			case LOOK_ALIVE:
				look_alive(sockfd);
				break;
			case GROUP_CHAT:
				chat_with(sockfd,1);
				break;
			case EXIT:
			default:
				flag = 0;
				pthread_attr_destroy(&attr);
				do_exit(sockfd);
				return 0;
		}
	}
	return 1;
}

void do_server(int sockfd)
{
	char ch;
	char res;
	while(1){
		first_view();
		ch = getchar();
		while(getchar()!='\n');
		if(ch == '1'){
			res = login(sockfd);
			if (res == TYPE_OK){
				int val = in_sec(sockfd);
				if (val == 0){
					break;
				}
			}else if (res == TYPE_ERROR){
				printf("There is no or online\n");
				continue;
			}else if (res == 'a'){
				printf("服务器关闭....\n");
				break;
			}else{
				continue;
			}
		}if (ch == '2'){
			res = regist(sockfd);
			if (res == TYPE_OK){
				printf("注册成功,现在可以使用此帐号登录redchat聊天室\n");
			}else if (res == TYPE_ERROR){
				printf("不好意思,此帐号已经被占用...\n");
				continue;
			}else if (res == 'a'){
				printf("服务器关闭....\n");
				break;
			}else{
				continue;
			}
		}else{
			break;
		}
	}
	printf("thank you....\n");
}

