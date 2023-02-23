CXXFLAGS=-O3 -Wall -Wextra -std=c++11
.PHONY: clean

associativity: associativity.cpp
	$(CXX) $(CXXFLAGS) -o associativity associativity.cpp

clean:
	rm -f associativity thrashing.dat padded.dat plot.png
