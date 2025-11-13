SHELL := /bin/bash

run:
	@echo "Executing C++ program and python script without removing simulation .dat files."
	@source prob_make.sh && python3 read_prob_dat.py 

run-clean:
	@echo "Executing C++ program and Python script."
	@source prob_make.sh
	@python3 read_prob_dat.py && echo "Removing simulation .dat files." && rm *.dat
