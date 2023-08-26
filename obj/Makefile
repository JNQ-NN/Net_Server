include $(ROOT_DIR)/config.mk

OBJ=../main.cpp
OBJ+=$(wildcard *.o)
../bin/$(TARGET):$(OBJ)
	$(CC) $(FLAG) $(INCLUDE_DIR) $^ -o $@ ${LIB}
clean:
	rm -rf *.o