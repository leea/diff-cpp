# Makefile for the libdiff template library

#Set compiler to g++ if not already set
CXX ?= g++

CXXFLAGS +=  -Wall -pedantic -foptimize-sibling-calls 

OBJS = test_diff.o lcs.o

INCLUDE = -I ../

all: test_diff lcs
	./test_diff

lcs: lcs.o
	$(CXX) $(CXXFLAGS) $(INCLUDE) $+ -o $@	

test_diff: test_diff.o
	$(CXX) $(CXXFLAGS) $(INCLUDE) $+ -o $@

# pull in dependency info for existing .o files
-include $(OBJS:.o=.d)

# compile and generate dependency info
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) $< -o $@
	$(CXX) -MM $(CXXFLAGS) $(INCLUDE) $< > $*.d

clean:
	rm test_diff lcs $(OBJS) *.d > /dev/null


ifdef DEBUG
CXXFLAGS += -g 
else
CXXFLAGS += -O3 -DNDEBUG
endif

ifdef VERBOSE
CXXFLAGS += -DDEBUG 
endif

ifdef VERBOSE_MATRIX
CXXFLAGS += -DDEBUG_MATRIX
endif

ifdef VERBOSE_LINE
CXXFLAGS += -DDEBUG_LINE
endif

ifdef PROFILE
CXXFLAGS += -pg
endif
