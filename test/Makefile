MAIN_TARGET_NAME = run_tests.exe
SRC_DIRS = src
INC_DIRS = cppUnit/include ../ext ../. .
CXXFLAGS = -Wall -Wextra -Werror -g -std=c++20

BIN_DIR = bin
OBJ_DIR = obj
SRC_FILES := $(shell find $(SRC_DIRS) -name "*.cpp")
OBJ_FILES := $(patsubst $(SRC_DIRS)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
DEPS := $(OBJ_FILES:.o=.d)

CPPFLAGS := $(addprefix -I,$(INC_DIRS)) -MMD -MP
LDFLAGS :=

$(BIN_DIR)/$(MAIN_TARGET_NAME): $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIRS)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/* $(BIN_DIR)/*

-include $(DEPS)