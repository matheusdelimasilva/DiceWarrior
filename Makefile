# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -I/opt/homebrew/include -Wall -Wextra -pedantic
LDFLAGS = -L/opt/homebrew/lib
LIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo

# Project files
TARGET = dice
SRCS = main.cpp Game.cpp
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
