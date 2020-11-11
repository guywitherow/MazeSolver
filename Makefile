.default: all

all: assign1

clean:
	rm -f red7 *.o

assign1: Breadcrumb.cpp Trail.cpp MazeSolver.cpp main.cpp
	g++ -Wall -Werror -std=c++14 -g -O0 -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O0 -c $^