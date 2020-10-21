
output: main.o population.o species.o individual.o node.o connection.o 
	g++ main.o population.o species.o individual.o node.o connection.o -o output


main.o: main.cpp
	g++ -c main.cpp

population.o: population.cpp population.h
	g++ -c population.cpp


species.o: species.cpp species.h
	g++ -c species.cpp


individual.o: individual.cpp individual.h
	g++ -c individual.cpp

node.o: node.cpp node.h
	g++ -c node.cpp

connection.o: connection.cpp connection.h
	g++ -c connection.cpp


clean:
	rm *.o output