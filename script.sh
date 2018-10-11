#!/bin/bash

#	@echo "1  RUN_TIME"
#	@echo "2  ITERATION"
#	@echo "3  POPULATION"
#	@echo "4  FUNC_NUM"
#	@echo "5  number of objective"
#   @echo "6  light absorption coefficient"
#   @echo "7  alpha_0"
#   @echo "8  beta_0"
#   @echo "9  non-dominated set"
#   @echo "10  real-time gnuplot 1/0" 
#   @echo "11 Crowing distance method"
#   @echo "     0 own method"
#   @echo "     1 NSGA-II"

#@@@@@@@@@@@@

#function
#1  Schaffer function N.1 (SCH)
#2  Fonseca and Fleming function (FON)
#3  Zitzler, Deb and Thiele's function N.1 (ZDT1)
#4  Zitzler, Deb and Thiele's function N.2 (ZDT2)
#5  Zitzler, Deb and Thiele's function N.3 (ZDT3)
#6  Zitzler, Deb and Thiele's function N.4 (ZDT4)
#7  Zitzler, Deb and Thiele's function N.6 (ZDT6)

make clean all

#gdb --args 
#            1   2    3 4 5  6   7    8   9 10 11
./monsfa.out 1   100 50 6 2 1.0 0.25 0.7 500 0 1

gnuplot point.gp

#evince MONSFA.pdf

