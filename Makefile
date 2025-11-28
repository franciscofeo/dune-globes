SHELL := /bin/bash

prob-run:
	@echo "Executing Oscillation Probability C++ program and python script without removing simulation .dat files."
	@source oscilation_probability/prob_make.sh && python3 oscilation_probability/read_prob_dat.py 

prob-run-clean:
	@echo "Executing Oscillation Probability C++ program and Python script."
	@source oscilation_probability/prob_make.sh
	@python3 oscilation_probability/read_prob_dat.py && echo "Removing simulation .dat files." && rm *.dat

corr-run:
	@echo "Executing Correlation C++ program and python script without removing simulation .dat files."
	@source correlation/correlation_make.sh && python3 correlation/plot_contour_correlation.py

corr-run-clean:
	@echo "Executing Correlation C++ program and Python script."
	@source correlation/correlation_make.sh
	@python3 correlation/plot_contour_correlation.py && echo "Removing simulation .dat files." && rm *.dat

ec-run:
	@echo "Executing Event Counter C++ program and Python script."
	@source events_counter/ec_make.sh && python3 events_counter/plot_events.py

ec-run-clean:
	@echo "Executing Event Counter C++ program and Python script."
	@source events_counter/ec_make.sh
	@python3 events_counter/plot_events.py && echo "Removing simulation .dat files." && rm *.dat
