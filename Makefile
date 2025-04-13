# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -fopenmp -Wall

# Executable directory
SRC_DIR := src
BIN_DIR := bin
INCLUDES := -Iinc

# Source files
BENCH_SRC := \
	$(SRC_DIR)/task.cpp \
	$(SRC_DIR)/taskParser.cpp \
	$(SRC_DIR)/benchmark.cpp \
	$(SRC_DIR)/scheduler.cpp \
	$(SRC_DIR)/FCFSScheduler.cpp \
	$(SRC_DIR)/worker.cpp
	
GEN_SRC := $(SRC_DIR)/taskGenerator.cpp

# Executables and their targets
TARGETS := $(BIN_DIR)/benchmark $(BIN_DIR)/taskGenerator


all: $(TARGETS)

#build rules
$(BIN_DIR)/benchmark: $(BENCH_SRC) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

$(BIN_DIR)/taskGenerator: $(GEN_SRC) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Create the bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean up build artifacts
clean:
ifeq ($(OS),Windows_NT)
	@if exist $(BIN_DIR) (del /q $(BIN_DIR)\*) || echo "Nothing to clean"
else
	rm -f $(BIN_DIR)/*
endif

.PHONY: all clean