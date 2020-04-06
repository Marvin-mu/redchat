#ifndef _TYPE_H_
#define _TYPE_H_

typedef struct{
	char type;//数据包类型
	char usrname[20];//发送方用户名
	char pswd[20];//密码
	char name_rec[20];//接收方
	char name_send[20];//发送方
	char chat_data[1024];//聊天内容
}data_t;

#define TYPE_LOGIN '0'  // 登陆数据包
#define TYPE_REG '1'	// 注册数据包
#define TYPE_MSG '2'    // 消息数据包
#define TYPE_HEART '3'  // 心跳数据包
#define TYPE_CMD '4'  	// 命令数据包
#define	TYPE_ONLINE '5' // 查看在线用户
#define	TYPE_OK '6'     // 服务器返回OK包
#define TYPE_ERROR '7'  // 服务器返回错误包
#define TYPE_EXIT '8'   // 断开链接包

void unpack_packet(char* buff, data_t* data);

void packaging(char* buff,data_t* data);


#endif
