#!/bin/bash
g++ -Wall -c ./correlation/deltacp_theta13_correlation.cc
g++ -Wall ./deltacp_theta13_correlation.o -lglobes -lgsl -lgslcblas -O3 -o ./deltacp_theta13_correlation
./deltacp_theta13_correlation

rm *.o
rm ./deltacp_theta13_correlation
