include $(ROOT_DIR)/config.mk

OBJ=../main.cpp
OBJ+=$(wildcard *.o)
../bin/$(TARGET):$(OBJ)
	$(CC) $(INCLUDE_DIR) $^ -o $@ -llog4cplus -lmysqlclient
clean:
	rm -rf *.o