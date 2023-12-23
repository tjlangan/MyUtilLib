CC:=gcc
CFLAGS:=-Wall -Wextra -std=c11 -g

SRC_DIR := ./src
TEST_DIR := ./tests
OBJ_DIR := ./obj

SRCS := $(shell find $(SRC_DIR) -name '*.c')

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:./%.o=%.o)  

TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)



all: $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@


test: $(OBJS) $(TEST_SRCS)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_SRCS) -o test_executable

clean:
	rm -rf $(OBJ_DIR) test_executable

.PHONY: all test clean