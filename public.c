#include <stdio.h>
#include<string.h>
#include<stdlib.h>

void getstring(char* str,int size)
{
	fgets(str, 1024, stdin);
	if (strlen(str) < 1024)
	{
		str[strlen(str) - 1] = '\0';
	}
}

void first_view()
{
	system("clear");
	printf("\t\t===============================\n");
	printf("\t\t=====< welcome to redchat >====\n");
	printf("\t\t======> 1.login  <=============\n");
	printf("\t\t======> 2.regist <=============\n");
	printf("\t\t======> 3.exit   <=============\n");
	printf("\t\t===============================\n");
	printf("\t\t=====input your choice:");
	fflush(stdout);
}

void second_view()
{
	system("clear");
	printf("\t\t===============================\n");
	printf("\t\t====> welcome to redchat <=====\n");
	printf("\t\t======> 1.send shell  =========\n");
	printf("\t\t======> 2.chat with someone  ==\n");
	printf("\t\t======> 3.look alive  =========\n");
	printf("\t\t======> 4.group chat  =========\n");
	printf("\t\t======> 5.exit  ===============\n");
	printf("\t\t===============================\n");
	printf("\t\t=====input your choice:");
	fflush(stdout);
}
