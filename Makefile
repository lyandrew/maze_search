## CS 440 MP1 
## @author Will Hempy
## @netid hempy2

OBJS = AStarSearch.o main.o
## DONT FORGET TO ADD DFSsearch.o GBFsearch.o ASTsearch.o above!
EXENAME = main
COMPILER = g++
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
COMPILER_OPTS = -c -g -O0 -Wfatal-errors -Werror $(WARNINGS)
LINKER = g++

.PHONY: all clean

all: $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LINKER) $(OBJS) -o $(EXENAME)

main.o: main.cpp AStarSearch.h 
	$(COMPILER) -c $(COMPILER_OPTS) main.cpp

##BFSsearch.o: BFSsearch.cpp BFSsearch.h
#	$(COMPILER) -c $(COMPILER_OPTS) BFSsearch.cpp

## DFSsearch.o: DFSsearch.cpp DFSsearch.h
#	$(COMPILER) -c $(COMPILER_OPTS) DFSsearch.cpp

## GBFsearch.o: GBFsearch.cpp GBFsearch.h
# 	$(COMPILER) -c $(COMPILER_OPTS) GBFsearch.cpp

   ASTsearch.o: AStarSearch.cpp AStarSearch.h
	$(COMPILER) -c $(COMPILER_OPTS) AStarSearch.cpp
clean:
	rm -rf *.o $(EXENAME)
tidy:
	-rm -rf doc
