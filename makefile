CXX = g++
CC = gcc
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra -Isource -Iext/glad/include -MMD -MP
CCFLAGS  = -O2 -Wall -Wextra -Iext/glad/include
LDFLAGS = -lglfw -ldl -lX11 -lpthread

BUILD_DIR = build
SRC_DIR = source

GLAD_SRC = ext/glad/src/glad.c
GLAD_OBJ = $(BUILD_DIR)/glad.o

MAIN = $(SRC_DIR)/main.cpp
MAIN_OBJ = $(BUILD_DIR)/main.o

all: $(BUILD_DIR)/app

$(MAIN_OBJ): $(MAIN)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GLAD_OBJ): $(GLAD_SRC)
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c $< -o $@

$(BUILD_DIR)/app: $(MAIN_OBJ) $(GLAD_OBJ)
	$(CXX) $(MAIN_OBJ) $(GLAD_OBJ) -o $@ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)
