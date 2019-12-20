#ifndef public_h
#define public_h


/*
* Function:获取单个字符ASSIC
* Description:
* Calls:
* Called By:
* Input:
* Output:
* Return:int
* Others:
*/
int getch();

/*
* Function:getPassword
* Description:隐藏键盘的输入,防止信息泄漏
* Calls:
* Called By:login_all
* Input:
* Output:
* Return:void
* Others:
*/
void getPassword(char *pcPWD);

/*
* Function:identifyCode
* Description:产生4位验证码,两个字母两个数字
* Calls:
* Called By:
* Input:
* Output:
* Return:int
* Others:
*/
int identifyCode(void);
/*
* Function:getstring
* Description:获取字符串
* Calls:
* Called By:
* Input:
* Output:
* Return:void
* Others:
*/
void getstring(char *str,int len);

#endif