CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -Werror -Wshadow -std=c++17 -O2

TARGET = lex

SRCS = lex.cpp
OBJS = lex.o

# Default target
all: $(TARGET)

# Build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
lex.o: lex.cpp utils.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

debug: CXXFLAGS += -DDEBUG
debug: clean all

clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
