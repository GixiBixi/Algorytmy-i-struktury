CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

all: test

test: test.cpp arraylist.hpp
	$(CXX) $(CXXFLAGS) -o test test.cpp

run: test
	./test

clean:
	rm -f test