CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra -Isource -Iexternal -MMD -MP
LDFLAGS = -lglfw -ldl -lX11 -lpthread

BUILD_DIR = build
SRC_DIR = source

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))
DEPS = $(OBJ:.o=.d)

APP = $(BUILD_DIR)/app

all: $(APP)

$(BUILD_DIR):
		mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
		$(CXX) $(CXXFLAGS) -c $< -o $@

$(APP): $(OBJ)
		$(CXX) $(OBJ) -o $@ $(LDFLAGS)

-include $(DEPS)

clean:
		rm -rf $(BUILD_DIR)
