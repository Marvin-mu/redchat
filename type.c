#include<string.h>
#include"type.h"

//把字符串还原为数据结构体
void unpack_packet(char* buff, data_t* data)
{
	if(buff == NULL || data == NULL){
		return;
	}
	memset(data, 0 ,sizeof(data_t));
	data->type = buff[0];
	for (int i = 0; i < 20; i++){
		data->usrname[i] = buff[i + 1];
	}
	for (int i = 0; i < 20; i++){
		data->pswd[i] = buff[i + 21];
	}
	for (int i = 0; i < 20; i++){
		data->name_rec[i] = buff[i + 41];
	}
	for (int i = 0; i < 20; i++){
		data->name_send[i] = buff[i + 61];
	}
	for (int i = 0; i < 1024; i++){
		data->chat_data[i] = buff[i + 81];
	}
}

//把数据结构体封装为字符串
void packaging(char* buff,data_t* data)
{
	if(buff == NULL || data == NULL){
		return;
	}
	memset(buff, 0, sizeof(data_t));
	buff[0] = data->type;
	for (int i = 0; i < 20; ++i){
		buff[i + 1] = data->usrname[i];
	}
	for (int i = 0; i < 20; ++i){
		buff[i + 21] = data->pswd[i];
	}
	for (int i = 0; i < 20; ++i){
		buff[i + 41] = data->name_rec[i];
	}
	for (int i = 0; i < 20; ++i){
		buff[i + 61] = data->name_send[i];
	}
	for (int i = 0; i < 1024; ++i){
		buff[i + 81] = data->chat_data[i];
	}
}