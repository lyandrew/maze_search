CC = g++
OPTS = -g -Wall -Werror 

all: main

main: main.cpp
	$(CC) -o $@ $^ $(OPTS)

# add other entries here

clean:
	rm -rf *.o main
