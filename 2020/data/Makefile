CXXOPTIONS = -Wall -Werror
main: date.o main.o 
	g++ -o main main.o date.o
date.o: date.cpp
	g++ -c date.cpp
main.o: main.cpp
	g++ $(CXXOPTIONS) -c main.cpp
run: main
	./main
clean:
	rm -rf *.o main
