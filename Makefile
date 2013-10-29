# Makefile for the diff-cpp template library

ABOUT = Diff-cpp is a template library, to use it include the "lcs.h" header file.


all:
	@echo $(ABOUT)

check: 
	$(MAKE) -C test

clean:
	@$(MAKE) -C test clean
