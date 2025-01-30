.PHONY: all clean

CXX = g++
CXX_FLAGS = -Wall -Wextra -Wshadow

BIN = XorMachine XorCompiler

all: $(BIN)

clean:
	rm -f $(BIN)

XorMachine: src/XorMachine.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $^

XorCompiler: src/XorCompiler.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $^
