#!/bin/bash

#	@echo "1  RUN_TIME"
#	@echo "2  ITERATION"
#	@echo "3  POPULATION"
#	@echo "4  FUNC_NUM"
#   @echo "5  light absorption coefficient"
#   @echo "6  alpha_0"
#   @echo "7  beta_0"
#   @echo "8  non-dominated set"

#@@@@@@@@@@@@

#function
#1  Schaffer function N.1 (SCH)

make clean all

#gdb --args 
./monsfa.out 1 250 5 1 1.0 0.25 0.7 500

