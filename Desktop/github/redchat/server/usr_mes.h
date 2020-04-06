#ifndef _USR_MES_H_
#define _USR_MES_H_

//用户结构体
typedef struct USER{
	char name[30];
	char pswd[30];
	struct USER* prev;
	struct USER* next;
}usr_mes_t;

//================================
//函数名:user_init
//作者:marvin
//时间:2020.1.4
//功能:链表头节点
//输入参数:void
//返回值:usr_mes_t
//修改记录:
//================================
usr_mes_t* usr_init();

//================================
//函数名:find_usr
//作者:marvin
//时间:2020.1.4
//功能:遍历链表
//输入参数:
//返回值:usr_mes_t
//修改记录:
//================================
usr_mes_t* find_usr(usr_mes_t* head, char* name);

//================================
//函数名:insert_usr
//作者:marvin
//时间:2020.1.4
//功能:增加节点
//输入参数:
//返回值:void
//修改记录:
//================================
void insert_usr(usr_mes_t* head, char* name, char* pswd);

//================================
//函数名:load_usr
//作者:marvin
//时间:2020.1.7
//功能:加载链表信息
//输入参数:
//返回值:void
//修改记录:
//================================
void load_usr(usr_mes_t* head);

//================================
//函数名:save_usr
//作者:marvin
//时间:2020.1.7
//功能:保存链表信息
//输入参数:
//返回值:void
//修改记录:
//================================

void save_usr(usr_mes_t* head);
//================================
//函数名:free_usr
//作者:marvin
//时间:2020.1.4
//功能:释放堆栈空间
//输入参数:
//返回值:void
//修改记录:
//================================
void free_usr(usr_mes_t *head);

#endif
