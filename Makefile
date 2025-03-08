CXX = g++
CXXFLAGS = -g -Wall -Wextra -Werror -Wpedantic -std=c++17 -O2 -MMD -MP -fexceptions -fvisibility=hidden -Wfatal-errors \
#	-fsanitize=address

SRC_DIR = src
OBJ_DIR = obj
EXEC = compiler

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS = $(OBJECTS:.o=.d)

all: $(EXEC)
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR) $(EXEC)

.PHONY: all clean
