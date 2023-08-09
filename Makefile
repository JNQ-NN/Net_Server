include config.mk

ROOT_DIR := $(shell pwd)

all:CHECK_DIR $(SUB_DIRS)

export ROOT_DIR
 
CHECK_DIR:                     #创建bin目录，用于存放可执行文件
	mkdir -p $(BIN_DIR)    
$(SUB_DIRS):ECHO               #遍历子目录，依次调用子目录的Makefile文件
	make -C $@         
ECHO:                          #遍历子目录
	@echo $(SUB_DIRS)

run:
	./bin/Example_Project

clean:
	make clean -C $(OBJS_DIRS)
	rm -rf $(BIN_DIR) 