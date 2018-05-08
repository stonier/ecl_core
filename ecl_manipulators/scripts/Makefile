XOPTIONS=-geometry 1024x1024 -persist -background white
FILE=./test.dat
#FILE=../resources/waykook/tasks/test.dat
ACCEL_CONSTRAINT=-a 5
PWD=$(shell pwd)

linear: data
	gnuplot ${XOPTIONS} linear.x11

tension: data
	gnuplot ${XOPTIONS} tension.x11

data: compile
	$(PWD)/../bin/test_trajectories

compile:
	@if [ ! -f ../bin/test_trajectories ]; then \
	  make -C $(PWD)/.. tests; \
	fi

clean:
	rm *.dat
	
help:
	@echo "This generates the test programs, writes some output to disk"
	@echo "and finally calls gnuplot. Valid targets include:" 
	@echo ""
	@echo "    linear : plot the linear interpolations."
	@echo "    tension: plot the tension interpolations."
	@echo ""


.PHONY: help clean compile data linear tension
