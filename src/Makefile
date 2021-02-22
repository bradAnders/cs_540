main.app: parser/parser.o database/database.o main.o
	g++ -std=c++11 parser/parser.o database/database.o main.o -o main.app

parser.o: ./parser/*
	make -C ./parser 

database.o: ./database/*
	make -C ./database 

main.o: main.cpp main.h
	g++ -std=c++11 -Wall -g -c main.cpp

clean:
	make -C ./parser clean
	make -C ./database clean
	rm -f *.o *.out *.exe