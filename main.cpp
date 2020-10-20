
#include <iostream>

#include"population.h"

using namespace std;


int main(int argc, char *argv[]){
	srand(time(0));

	int population_size = 128;

	Population population = Population(population_size, 2, 1);

	for(int i=0; i<1000; ++i){
		// cout << 1 << endl;
		population.speciate();
		// cout << 2 << endl;

		population.xor_epoch();



		cout << "spe size " << population.species.size() << endl;

		population.species.clear();

		cout << "fin innov_num " << *(population.innov_num) << endl;

		cout << "elite " << population.elite->fitness << endl;

		cout << "pop size " << population.individuals.size() << endl;
	}

	return 0;

}