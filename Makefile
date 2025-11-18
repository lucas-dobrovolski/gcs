CXX = g++
CC = gcc
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra -Isource -Iexternal -Isource/ext/glad/include -MMD -MP
CCFLAGS = -O2 -Wall -Wextra -Isource -Iexternal -Isource/ext/glad/include -MMD -MP
LDFLAGS = -lglfw -ldl -lX11 -lpthread

BUILD_DIR = build
SRC_DIR = source

GLAD_SRC = source/ext/glad/src/glad.c
GLAD_OBJ = $(BUILD_DIR)/glad.o

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))
DEPS = $(OBJ:.o=.d)

APP = $(BUILD_DIR)/app


all: $(APP)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GLAD_OBJ): $(GLAD_SRC) | $(BUILD_DIR)
	$(CC) $(CCFLAGS) -c $< -o $@


$(APP): $(OBJ) $(GLAD_OBJ)
	$(CXX) $(OBJ) $(GLAD_OBJ) -o $@ $(LDFLAGS)

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)
