# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++2b -I/opt/homebrew/include -Wall -Wextra -pedantic -g
LDFLAGS = -L/opt/homebrew/lib -lfmt
LIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo

# Project files
TARGET = dice
SRCS := $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link the program
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LIBS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
