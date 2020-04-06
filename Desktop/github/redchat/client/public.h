#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#define SEND_SHELL '1'
#define CHAT_SOMEONE '2'
#define LOOK_ALIVE '3'
#define GROUP_CHAT '4'
#define EXIT '5'

//================================
//函数名:getstring
//作者:marvin
//时间:2020.1.4
//功能:输入字符串
//输入参数:
//返回值:void
//修改记录:
//================================
void getstring(char* str,int size);

//================================
//函数名:first_view
//作者:marvin
//时间:2020.1.6
//功能:显示用户界面
//输入参数:
//返回值:void
//修改记录:
//================================
void first_view();

//================================
//函数名:second_view
//作者:marvin
//时间:2020.1.5
//功能:显示用户界面
//输入参数:
//返回值:void
//修改记录:
//================================
void second_view();

#endif