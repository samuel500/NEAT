
#include <iostream>

#include"population.h"

using namespace std;


int main(int argc, char *argv[]){
	srand(time(0));

	int population_size = 32;

	Population population = Population(population_size, 2, 1);
	return 0;

}