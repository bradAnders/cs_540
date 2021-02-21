main.app: index/index.o lookup/lookup.o main.o
	g++ -std=c++11 index/index.o lookup/lookup.o main.o -o main.app

index/index.o: ./index/*
	make -C ./index 

lookup/lookup.o: ./lookup/*
	make -C ./lookup 

main.o: main.cpp main.h
	g++ -std=c++11 -Wall -g -c main.cpp

clean:
	make -C ./index clean
	make -C ./lookup clean
	rm -f *.o *.out *.exe