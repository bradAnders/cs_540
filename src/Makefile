main.app: index/index.o parser/parser.o main.o
	g++ -std=c++11 index/index.o parser/parser.o main.o -o main.app

index.o: ./index/*
	make -C ./index 

parser.o: ./parser/*
	make -C ./parser 

main.o: main.cpp main.h
	g++ -std=c++11 -Wall -g -c main.cpp

clean:
	make -C ./index clean
	make -C ./parser clean
	rm -f *.o *.out *.exe