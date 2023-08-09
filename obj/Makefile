include $(ROOT_DIR)/config.mk

OBJ=../main.cpp
OBJ+=$(wildcard *.o)
../bin/$(TARGET):$(OBJ)
	$(CC) $^ -o $@

clean:
	rm -rf *.o