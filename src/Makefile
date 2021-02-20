main.exe: index/index.o lookup/lookup.o main.o
	g++ -std=c++11 index/index.o lookup/lookup.o main.o -o main

index/index.o: index/index.cpp index/index.h
	make -C ./index 

lookup/lookup.o: lookup/lookup.cpp lookup/lookup.h
	make -C ./lookup 

main.o: main.cpp main.h
	g++ -std=c++11 -c main.cpp

clean:
	make -C ./index clean
	make -C ./lookup clean
	rm -f *.o *.out *.exe