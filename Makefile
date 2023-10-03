# Compiler and compiler flags
CXX = g++
CXXFLAGS = -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

# Source files, header files, and object files
SRCS = main.cpp KDTree.cpp Point.cpp
OBJS = $(SRCS:.cpp=.o)
HDRS = KDTree.h

# Output executable
TARGET = main

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
$(OBJS): $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -c $(SRCS)

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony target to avoid conflicts with files named "clean"
.PHONY: clean
