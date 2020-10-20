
#include <iostream>

#include"population.h"

using namespace std;


int main(int argc, char *argv[]){
	srand(time(0));

	int population_size = 150;

	Population population = Population(population_size, 3, 1);

	for(int i=0; i<1000; ++i){
		cout << "gen " << i+1 << endl;
		// cout << "m1" << endl;
		population.speciate();
		// cout << "m2" << endl;

		population.xor_epoch();

		// cout << "m3" << endl;

		cout << "spe size " << population.species.size() << endl;

		population.species.clear();
		// cout << "m4" << endl;

		cout << "fin innov_num " << *(population.innov_num) << endl;

		cout << "elite " << population.elite->fitness << endl;
		population.test_elite();
		cout << "max f " << population.max_fitness << endl;

		cout << "pop size " << population.individuals.size() << endl;
		if(population.max_fitness>15.9) break;
	}

	return 0;

}