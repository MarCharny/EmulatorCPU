CXX = g++
CXXFLAGS = -std=c++17 -O2

HEADERS = command.hpp parser.hpp registers.hpp stack.hpp state.hpp
SOURCES = command.cpp state.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: main testStack
main: main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
testStack: testStack.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: testStack
	./testStack

run: main
	./main $(ARGS)

clean:
	rm -f $(OBJECTS) main.o testStack.o $(EXECUTABLES)

.PHONY: all clean test run