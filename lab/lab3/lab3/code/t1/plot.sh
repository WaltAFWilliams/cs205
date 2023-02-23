#!/usr/bin/env bash

module load gnuplot/5.2.6-fasrc01

gnuplot <<EOF
set term png
set output 'plot.png'
set key top left
set grid
set xlabel 'Threads'
set ylabel 'Speedup'
plot x w l t 'Ideal', \
    'stride8byte.dat' using 2:4 w lp t '8 byte stride', \
    'stride16byte.dat' using 2:4 w lp t '16 byte stride', \
    'stride32byte.dat' using 2:4 w lp t '32 byte stride', \
    'stride64byte.dat' using 2:4 w lp t '64 byte stride', \
    'stride128byte.dat' using 2:4 w lp t '128 byte stride'
EOF
