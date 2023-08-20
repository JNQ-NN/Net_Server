include $(ROOT_DIR)/config.mk

SRC:=$(wildcard *.cpp)
SRC+=$(wildcard *.c)
INCLUDE_DIR+=include/$(wildcard *.h)
temp=$(patsubst %.c,%.o,$(SRC))
OBJ=$(patsubst %.cpp,%.o,$(temp))
OBJ_PATH=$(foreach obj_name,$(OBJ),../obj/$(obj_name))

all:$(OBJ_PATH)

../obj/%.o:%.c
	$(CC) -c $< -o $@ 
../obj/%.o:%.cpp
	$(CC) -c $< -o $@ 