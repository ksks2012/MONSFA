#!/bin/bash

#	@echo "1  RUN_TIME"
#	@echo "2  ITERATION"
#	@echo "3  POPULATION"
#	@echo "4  FUNC_NUM"
#   @echo "5  light absorption coefficient"
#   @echo "6  alpha_0"
#   @echo "7  beta_0"
#   @echo "8  non-dominated set"
#   @echo "9  real-time gnuplot 1/0" 
#   @echo "10 Crowing distance method"
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
./monsfa.out 1 20000 50 6 1.0 0.25 0.7 500 1 1

gnuplot point.gp

#evince MONSFA.pdf

