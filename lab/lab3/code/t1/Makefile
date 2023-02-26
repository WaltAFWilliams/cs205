CXXFLAGS = -O3 -g -Wall -Wextra -fopenmp
.PHONY: clean

false_sharing: false_sharing.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

run: false_sharing
	./false_sharing

clean:
	rm -f false_sharing stride*.dat
