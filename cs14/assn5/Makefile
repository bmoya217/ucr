# -g    -> compile with debug information
# -Wall -> give verbose compiler warnings
FLAGS = -g -Wall -std=c++0x 
COMPILE = g++

SOURCES= main.cpp chain.cpp probe.cpp
OBJECTS= $(SOURCES:.cpp=.out)

#Targets
all: main.cpp
	$(COMPILE) $(FLAGS) -o a.out $(SOURCES)

clean:
	rm a.out