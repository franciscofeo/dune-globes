#!/bin/bash
g++ -Wall -c ./correlation/deltacp_theta23_correlation.cc
g++ -Wall ./deltacp_theta23_correlation.o -lglobes -lgsl -lgslcblas -O3 -o ./deltacp_theta23_correlation
./deltacp_theta23_correlation

rm *.o
rm ./deltacp_theta23_correlation
