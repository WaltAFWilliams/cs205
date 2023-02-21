# File       : Makefile
# Description: Makefile for Julia Set problem CS205
# Copyright 2023 Harvard University. All Rights Reserved.

# TODO A: make sure you compile with support for OpenMP
CXXFLAGS = -O3 -Wall -Wextra -std=c++11 -march=native

.PHONY: clean run plot

julia_set: julia_set.cpp helper.h
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f julia_set image.txt histogram.txt image.png histogram.png

run: julia_set
	OMP_NUM_THREADS=1 ./julia_set

plot:
	python3 plot.py
