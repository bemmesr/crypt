LIB_NAME := crypt.a

SRC_DIR := src
INC_DIR := include
OBJ_DIR := build
BIN_DIR := bin

CC := gcc
CFLAGS := -I$(INC_DIR) -c

SRCS := $(wildcard $(SRC_DIR)/*.c)
SRCS := $(SRCS:$(SRC_DIR)/%=%)

OBJS := $(SRCS:%.c=%.o)

INCS := $(wildcard $(INC_DIR)/*.h)
INCS := $(INCS:$(INC_DIR)/%=%)

$(BIN_DIR)/$(LIB_NAME): $(OBJS:%=$(OBJ_DIR)/%)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS:%=$(INC_DIR)/%)
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(BIN_DIR)/*.a $(OBJ_DIR)/*.o
