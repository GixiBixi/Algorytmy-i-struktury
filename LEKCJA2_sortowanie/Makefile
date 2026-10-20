CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

all: insertsort mergesort

insertsort: ZADANIE2.2_insertsort.cpp
	$(CXX) $(CXXFLAGS) -o insertsort ZADANIE2.2_insertsort.cpp

mergesort: ZADANIE2.5_mergesort.cpp
	$(CXX) $(CXXFLAGS) -o mergesort ZADANIE2.5_mergesort.cpp

test: all
	./insertsort
	./mergesort

clean:
	rm -f insertsort mergesort

.PHONY: all test clean