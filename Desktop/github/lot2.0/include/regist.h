#ifndef regist_h
#define regist_h



typedef struct user{
	char name[20];//用户名
	char pswd[20];//密码
	double money;//余额
}user_t;

typedef struct user_link
{
	user_t user;
	struct user_link* prev;
	struct user_link* next;
}user_link;

/*
* Function:init_user
* Description:创建用户链表节点
* Calls:
* Called By:
* Input:
* Output:
* Return:user_link*
* Others:
*/

user_link* init_user();
/*
* Function:find_user
* Description:遍历用户链表,找到此用户后返回用户用户节点
* Calls:
* Called By:
* Input:
* Output:
* Return:user_link*
* Others:
*/

user_link* find_user(user_link* head,char* name);
/*
* Function:load_user
* Description:加载用户链表
* Calls:
* Called By:
* Input:user_link* head,char* name
* Output:
* Return:void
* Others:
*/

void load_user(user_link* user_head);
/*
* Function:save_user
* Description:保存用户链表数据
* Calls:
* Called By:
* Input:
* Output:
* Return:int
* Others:
*/

void save_user(user_link* user_head);
/*
* Function:free_user
* Description:释放用户链表
* Calls:
* Called By:
* Input:
* Output:
* Return:int
* Others:
*/

void free_user(user_link* user_head);
/*
* Function:所有人注册
* Description:regist_all
* Calls:
* Called By:
* Input:
* Output:
* Return:int
* Others:
*/
void regist_all(user_link* user_head);


#endif