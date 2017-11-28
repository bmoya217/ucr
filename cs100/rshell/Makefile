# -g    -> compile with debug information
# -Wall -> give verbose compiler warnings
FLAGS = -g -Wall -Werror -ansi -pedantic 
COMPILE = g++

SOURCES= src/main.cpp

#Targets
all: 
	mkdir -p bin
	$(COMPILE) $(FLAGS) $(SOURCES) -o bin/rshell

clean: 
	rm bin/rshell
	rm -rf bin

