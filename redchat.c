#include<arpa/inet.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<string.h>
#include"start.h"



int main(int argc, const char* argv[])
{
	//socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		perror("socket error");
		exit(1);
	}
	//connect
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(struct sockaddr_in));
	serveraddr.sin_family = AF_INET;
	//从文件中读取ip和port配置
	char buff[30] = "";
	FILE* fp = fopen("server.conf","r");
	if(fp == NULL){
	    perror("open config.conf error");
	    exit(1);
	}
	fgets(buff, 30, fp);
	buff[strlen(buff) - 1] = '\0';
	if((strncmp(buff, "SERVER", 6)) == 0){
	    inet_pton(AF_INET, strchr(buff,'=') + 1, &serveraddr.sin_addr.s_addr);
	}else{
		perror("set ip error");
		exit(1);
	}
	memset(buff, 0, 30);
	fgets(buff, 30, fp);
	buff[strlen(buff) - 1] = '\0';
	if((strncmp(buff, "PORT", 4)) == 0){
	    serveraddr.sin_port = htons(atoi(strchr(buff,'=') + 1));
	}else{
		perror("set port error");
		exit(1);
	}
	fclose(fp);
	//serveraddr.sin_port = htons(atoi(argv[2]));
	//inet_pton(AF_INET, argv[1], &serveraddr.sin_addr.s_addr);
	if(connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr_in)) < 0){
		perror("connect error");
		close(sockfd);
		exit(1);
	}
	//do
	do_server(sockfd);
	
	return 0;
}
