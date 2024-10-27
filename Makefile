LIB_NAME := crypt.a
TST_FILE := run_tests.sh

SRC_DIR := src
INC_DIR := include
OBJ_DIR := build
BIN_DIR := bin
TST_DIR := tests

CC := gcc
CFLAGS := -I.

SRCS := $(wildcard $(SRC_DIR)/*.c)
SRCS := $(SRCS:$(SRC_DIR)/%=%)

OBJS := $(SRCS:%.c=%.o)

INCS := $(wildcard $(INC_DIR)/*.h)
INCS := $(INCS:$(INC_DIR)/%=%)

TSTS := $(wildcard $(TST_DIR)/*.c)
TSTS := $(TSTS:$(TST_DIR)/%=%)

$(BIN_DIR)/$(LIB_NAME): $(OBJS:%=$(OBJ_DIR)/%)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS:%=$(INC_DIR)/%)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: tests
tests: CFLAGS += -g
tests: $(TSTS:%.c=$(BIN_DIR)/%) $(TST_FILE)

$(TST_FILE):
	echo "#!/usr/bin/bash" > $@
	echo "test_status=0" >> $@
	echo "set -x" >> $@
	printf "$(TSTS:%.c=if ! ./$(BIN_DIR)/%; then test_status=1; fi\n)" >> $@
	echo "set +x" >> $@
	echo "exit \$$test_status" >> $@
	chmod 776 $@

$(BIN_DIR)/test_%: $(TST_DIR)/test_%.c $(BIN_DIR)/$(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(BIN_DIR)/*.a $(OBJ_DIR)/*.o $(TST_FILE)

