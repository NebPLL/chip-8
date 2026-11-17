.DEFAULT_GOAL := run

CC = cc
CFLAGS = -Wall -Wextra -O2 -I. -MMD -MP $(shell pkg-config --cflags raylib)
LDLIBS = $(shell pkg-config --libs raylib)

BUILD_DIR = build
SRC = $(wildcard *.c) $(wildcard commands/*.c)
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP = $(OBJ:.o=.d)
TARGET = $(BUILD_DIR)/main

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)
	@echo "Neu gebaut."

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

-include $(DEP)

.PHONY: run clean
