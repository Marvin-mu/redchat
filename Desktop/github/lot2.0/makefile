VERSION:=1.0#程序版本号  

SOURCE:=$(wildcard ./src/*.c)  #获取所有的.c文件  
OBJ:=$(patsubst %.c, %.o, $(SOURCE))#将.c文件转为.o文件

INCLUDES:=-Iinclude#头文件路径  

CFLAGS:=-Wall -c#编译标志位  
TARGET:=app
CC:=gcc

#产生目标文件的位置
$(TARGET): $(OBJ)       
	$(CC) $(OBJ) -o bin/$(TARGET).$(VERSION)
#生成.o文件
%.o:%.c
	$(CC) $(INCLUDES) $(CFLAGS) $< -o $@

.PHONY:clean
clean:
	-rm -rf $(OBJ)/*.o
