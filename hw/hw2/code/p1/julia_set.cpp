// File       : julia_set.cpp
// Description: Code for Julia Set problem CS205
// Copyright 2023 Harvard University. All Rights Reserved.
#include "helper.h"
#include <cmath>
#include <chrono>
#include <omp.h>

constexpr int MAX_ITERATIONS = 1000;
short image[HEIGHT][WIDTH];

/*
 * Generate the Julia set.
 *
 * Fill each pixel `image[iy][ix]` with the number of iterations for the point
 * (x, y).
 */
void julia_set(void)
{
    // Some parameters of the Julia set (keep them for your final submission)
    constexpr double cx = -0.624;
    constexpr double cy = 0.435;

    auto t0 = std::chrono::steady_clock::now();

    // TODO A: parallelize this code
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            // Compute `w = z_0 = x + i y` for the given pixel (j, i).
            double x = 1.3 * (j - .5 * WIDTH) / HEIGHT;
            double y = 1.3 * i / HEIGHT; // Only one half.
            // Compute the count iterations for this pixel.
            int count = 0;
            // TODO A: implement the iteration rule here
	    for (count=0; count<1000; ++count){
		znsquared_x = x*x - y*y;
		znsquared_y = 2*x*y;
		x += znsquared_x;
		y += znsquared_y;
		zn_norm = sqrt(x*x + y*y);
		if (zn_norm > 2){

		}
	    }
            image[i][j] = count;
        }
    }
    auto t1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = t1 - t0;
    printf("Computing done in %.2lfs\n", diff.count());
}

/*
 * Compute the histogram of iteration count.
 *
 * Returns an `std::vector<int>`, where `i`-th elements represents the number
 * of pixels that had `i` iterations.
 */
std::vector<int> compute_histogram(void)
{
    std::vector<int> result(MAX_ITERATIONS + 1);

    // TODO D: Compute the histogram of iteration count.
    //         Parallelize your code with OpenMP.
    //
    //         To report your result, you can run `make plot`
    //         to plot the computed histogram.

    return result;
}

int main(void)
{
    julia_set();
    save_image(&image[0][0]);

    std::vector<int> histogram = compute_histogram();
    save_histogram(histogram);
    return 0;
}
