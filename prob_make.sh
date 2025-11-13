#!/bin/bash
g++ -Wall -c prob.cc
g++ -Wall prob.o -lglobes -lgsl -lgslcblas -O3 -o prob
./prob

rm *.o
rm ./prob
