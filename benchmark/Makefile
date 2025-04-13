# Compiler and flags
CC = g++
CFLAGS = -fopenmp -Wall

# List of source files
SRC_FILES = \
	task.cpp \
	fifoTaskParser.cpp \
	benchmark.cpp

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)

# Output binary
TARGET = benchmark

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJ_FILES) $(TARGET)

# Phony targets
.PHONY: all clean