#dir
TARGET=Example_Project       #最终生成的可执行文件名
SUB_DIRS=tool                #子目录列表,会遍历子目录，依次调用子目录的Makefile
SUB_DIRS+=obj  
OBJS_DIRS=obj                #存放生成的中间.o文件目录
BIN_DIR=bin                  #存放可执行文件的目录

#complier
CC=g++                       #g++编译器