# -g    -> compile with debug information
# -Wall -> give verbose compiler warnings
COMPILE = g++ -g

SOURCES= part2.cpp
OBJECTS= $(SOURCES:.cpp=.out)

#Targets
all: part2.cpp
	$(COMPILE) -o a.out $(SOURCES)

clean:
	rm a.out