#!/bin/bash
g++ -Wall -c ./events_counter/event_counter.cc
g++ -Wall ./event_counter.o -lglobes -lgsl -lgslcblas -O3 -o ./event_counter
./event_counter

rm *.o
rm ./event_counter
