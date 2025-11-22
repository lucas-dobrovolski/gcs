CXX = g++
CC = gcc
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra -Isource -Iexternal -Isource/ext/imgui -Isource/ext/imgui/backends -Iext/glad/include -MMD -MP
CCFLAGS = -O2 -Wall -Wextra -Isource -Iexternal -Iext/glad/include -MMD -MP
LDFLAGS = -lglfw -ldl -lX11 -lpthread

BUILD_DIR = build
SRC_DIR = source

GLAD_SRC = ext/glad/src/glad.c
GLAD_OBJ = $(BUILD_DIR)/glad.o

# Buscar todos los .cpp recursivamente dentro de source/
SRC = $(shell find $(SRC_DIR) -name '*.cpp')

# Convertir source/.../X.cpp → build/.../X.o
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

DEPS = $(OBJ:.o=.d)

APP = $(BUILD_DIR)/app

all: $(APP)

# Regla común para cualquier .cpp, con creación automática de subcarpetas
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# glad compilado aparte
$(GLAD_OBJ): $(GLAD_SRC)
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c $< -o $@

$(APP): $(OBJ) $(GLAD_OBJ)
	$(CXX) $(OBJ) $(GLAD_OBJ) -o $@ $(LDFLAGS)

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)
