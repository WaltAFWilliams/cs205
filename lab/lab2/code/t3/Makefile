CXXFLAGS = -O3 -Wall -Wextra -fopenmp
.PHONY: clean

counter: counter.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f counter
