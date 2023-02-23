#!/usr/bin/env bash

module load gnuplot/5.2.6-fasrc01

gnuplot <<EOF
set term png
set output 'plot.png'
set key top right
set grid
set log y
set xlabel 'Number of arrays k'
set ylabel 'Performance [Gflop/s]'
plot 'thrashing.dat' using 2:3 w lp t 'Conflict misses', \
     'padded.dat' using 2:3 w lp t 'Padded array (no conflict misses)'

EOF
