#ifndef _START_H_
#define _START_H_

#include"online.h"
#include"usr_mes.h"

void sig_handler(int signo);

void alive(int fd, char* buff);

//======================================
//函数名:do_server
//作者:marvin
//日期:2020.1.4
//功能:线程
//输入参数:client_addr_t
//返回值:void*
//修改记录:
//======================================
void* do_server(void* arg);

//======================================
//函数名:start_chat
//作者:marvin
//日期:2020.1.4
//功能:服务器连接上客户端后的操作入口
//输入参数:客户端的fd,客户端的addr
//返回值:void
//修改记录:
//======================================
void start_chat(int fd);



#endif
