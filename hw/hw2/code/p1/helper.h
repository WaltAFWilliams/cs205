// File       : helper.h
// Description: Auxiliary functions.  You do not need to modify code here.
// Copyright 2023 Harvard University. All Rights Reserved.
#ifndef HELPER_H_2LKE1DQI
#define HELPER_H_2LKE1DQI

#include <cstdio>
#include <vector>

#define HIGHRES

#ifndef HIGHRES
// low resolution
constexpr int WIDTH = 640;
constexpr int HEIGHT = 360 / 2; // half of height due to symmetry
#else
// UHD resolution
constexpr int WIDTH = 3840;
constexpr int HEIGHT = 2160 / 2; // half of height due to symmetry
#endif /* HIGHRES */

// Save matrix `image` into `image.txt` (which is then used by `plot.py`).
void save_image(const short *p)
{
    FILE *f = fopen("image.txt", "w");
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            fprintf(f, "%d ", (int)p[i * WIDTH + j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

// Save the histogram into `histogram.txt` (which is then used by `plot.py`).
void save_histogram(const std::vector<int> &histogram)
{
    FILE *f = fopen("histogram.txt", "w");
    for (int count : histogram) {
        fprintf(f, "%d\n", count);
    }
    fclose(f);
}
#endif /* HELPER_H_2LKE1DQI */
