CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -Iinclude -O3

# 1. Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# 2. Find all sources
# Use sort to avoid duplicates (solves your previous linking error too)
SRCS := $(sort $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/days/*.cpp))

# 3. Auto-generate object paths
# e.g., src/days/day01.cpp -> obj/days/day01.o
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# 4. Target Executable
TARGET := $(BIN_DIR)/aoc

# --- Rules ---

all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@echo "Linking $@"
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Done."

# Compile
# This magic rule creates the specific sub-directories inside obj/ automatically
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Run Helpers
run: $(TARGET)
ifdef day
	@./$(TARGET) $(day)
else
	@echo "Usage: make run day=XX"
endif

test%: $(TARGET)
	@echo "Running Day $* (Test Input)..."
	@./$(TARGET) $* --test

run%: $(TARGET)
	@echo "Running Day $* ..."
	@./$(TARGET) $*

clean:
	@echo "Cleaning up..."
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all run clean
