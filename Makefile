# Define the compiler
CXX=g++

# Define the compiler flags
CXXFLAGS=-std=c++11 -Wall -Werror=vla

# Define the debugging flags
DEBUGFLAGS=-g -O0

# Define the target executable
TARGET=main
TARGET_DEBUG=main_debug
# Define the source files
SRCS=main.cpp environment.cpp frame.cpp body.cpp kinematic.cpp dynamic.cpp 

# Define the object files from the source files
OBJS=$(SRCS:.cpp=.o)
OBJS_DEBUG=$(SRCS:.cpp=_debug.o)

# Define the build rule for the target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Define the build rule for the debug target
$(TARGET_DEBUG): $(OBJS_DEBUG)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -o $(TARGET_DEBUG) $(OBJS_DEBUG)

# Define the rule for compiling the source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Define the rule for compiling the source files into debug object files
%_debug.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -c $< -o $@

# Define the clean rule
clean:
	rm -f $(TARGET) $(TARGET_DEBUG) $(OBJS) $(OBJS_DEBUG)

# Define the rule for making the target
all: $(TARGET)

# Define the rule for running the executable
run: $(TARGET)
	./$(TARGET)

# Define the rule for running the debug executable
run_gdb: $(TARGET_DEBUG)
	gdb ./$(TARGET_DEBUG)

.PHONY: clean all run run_gdb
