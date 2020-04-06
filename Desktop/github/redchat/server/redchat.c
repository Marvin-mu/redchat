#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<signal.h>

#include"start.h"
#include"usr_mes.h"
#include"online.h"

usr_mes_t* usr_head;
online_t* online_head;

void sig_int(int signo)
{
	if (signo == SIGINT)
	{
		save_usr(usr_head);
		printf("\n------------redchat聊天室服务器关闭------------\n");
		free_usr(usr_head);//释放堆栈
		free_online(online_head);
		exit(1);
	}
}

int main(int argc, const char* argv[])
{
	if (signal(SIGINT,sig_int) < 0)
	{
		perror("sigint error");
		exit(1);
	}
	//链表初始化
	usr_head = usr_init();
	online_head = online_init();
	
	//socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		perror("socket error");
		exit(1);
	}
	//bind
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi("11111"));
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	if(bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0){
		perror("bind error");
		close(sockfd);
		exit(1);
	}
	//listen
	if(listen(sockfd, 10) < 0){
		perror("listen error");
		close(sockfd);
		exit(1);
	}
	load_usr(usr_head);
	system("clear");
	printf("------------redchat聊天室服务器启动完成------------\n");
	//accept
	int fd = 0;
	while(1){
		fd = accept(sockfd, NULL, NULL);
		if(fd < 0){
			perror("accept error");
			continue;
		}
		start_chat(fd);
	}
	
	return 0;
}














