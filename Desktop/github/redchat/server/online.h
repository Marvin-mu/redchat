#ifndef _ONLINE_H_
#define _ONLINE_H_

typedef struct ONLINE{
	char name[20];
	char ip[16];
	int port;
	int fd;
	struct ONLINE* prev;
	struct ONLINE* next;
}online_t;

//======================================
//函数名:online_init
//作者:marvin
//日期:2020.1.4
//功能:创建在线列表头节点
//输入参数:void
//返回值:online_t
//修改记录:
//======================================
online_t* online_init(void);

//======================================
//函数名:insert_online
//作者:marvin
//日期:2020.1.4
//功能:新增在线用户
//输入参数:head, ip, port
//返回值:void
//修改记录:
//======================================
void insert_online(online_t* head, char* ip, int port, int fd, char* name);

//======================================
//函数名:find_online
//作者:marvin
//日期:2020.1.12
//功能:查看此用户是否在线
//输入参数:head, name
//返回值:online_t*
//修改记录:
//======================================
online_t* find_online(online_t* head, void* name);

//======================================
//函数名:remove_online
//作者:marvin
//日期:2020.1.4
//功能:删除在线用户
//输入参数:head, port
//返回值:void
//修改记录:
//======================================
void remove_online(online_t* head, int fd);

//======================================
//函数名:free_online
//作者:marvin
//日期:2020.1.4
//功能:释放在线链表堆栈
//输入参数:head
//返回值:void
//修改记录:
//======================================
void free_online(online_t* head);


#endif
