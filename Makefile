
CC=gcc
CFLAGS=-I. -g

OS_DIR=software
SRC_DIR=$(OS_DIR)/src
INC_DIR=$(OS_DIR)/common -I$(OS_DIR)/include -I$(OS_DIR)/api

OBJ=$(OS_DIR)/main.o $(SRC_DIR)/os_init.o $(SRC_DIR)/os_mem.o $(SRC_DIR)/os_scheduler.o $(SRC_DIR)/os_task.o $(SRC_DIR)/os_sleep.o

OUT_DIR=output
OUTPUT=$(OUT_DIR)/os.out

%.o: %.c
	@echo "# Building $<"
	@$(CC) -c -o $@ $< $(CFLAGS) -I$(INC_DIR)

all: build

build: $(OBJ)
	@echo "# Linking"
	@$(CC) -o $@ $^ $(CFLAGS) -I$(INC_DIR) -o $(OUTPUT)
	@echo "# Moving .o files to $(OUT_DIR)"
	@mv $(OBJ) $(OUT_DIR)

clean:
	@echo "# Cleaning $(OUT_DIR)"
	@rm $(OUT_DIR)/*

