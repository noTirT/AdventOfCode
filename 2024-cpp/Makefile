CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -Iinclude -O3

UTIL_SRCS := $(wildcard src/*.cpp)
UTIL_OBJS := $(UTIL_SRCS:.cpp=.o)

BIN_DIR := bin

DAYS := $(notdir $(wildcard day*))

all: $(DAYS:%=$(BIN_DIR)/%)

%:
	@daydir=day$@; \
	if [ -d $$daydir ]; then \
		$(MAKE) $(BIN_DIR)/$$daydir; \
	else \
		echo "No directory for day $$@"; \
	fi

$(BIN_DIR)/day%: day%/main.cpp $(UTIL_OBJS)
	@mkdir -p $(BIN_DIR)
	@echo "Building $@..."
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Done."

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run%: $(BIN_DIR)/day%
	@echo "Running $< ..."
	@./$< $(filter-out $@,$(MAKECMDGOALS))

clean:
	rm -rf $(BIN_DIR) src/*.o

rebuild:
	make clean
	bear -- make all

.PHONY: all clean
