#dir
TARGET=Net_Server            #最终生成的可执行文件名
SUB_DIRS=tool                #子目录列表,会遍历子目录，依次调用子目录的Makefile
SUB_DIRS+=net
SUB_DIRS+=net_client
SUB_DIRS+=net_server
SUB_DIRS+=net_server_http

SUB_DIRS+=obj                #obj将.o文件编译成可执行文件
OBJS_DIRS=obj                #存放生成的中间.o文件目录
BIN_DIR=bin                  #存放可执行文件的目录
INCLUDE_DIR=
LOG_DIRS=log                 #存放日志文件
#complier
CC=g++                       #g++编译器
FLAG=-Wall -g -std=c++20
LIB = -L${ROOT_DIR}/lib      #添加LIB路径，系统默认路径为/usr/local/lib/..
                             #系统默认路径，可以通过修改/etc/local/lib添加路径
LIB += -llog4cplus 
LIB += -lmysqlclient 
LIB += -lhiredis
LIB += -lredis++
LIB += -fcoroutines