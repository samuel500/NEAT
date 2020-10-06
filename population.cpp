
#include"population.h"


using namespace std;


Population::Population(int psize, int isize, int osize){

	Individual *new_individual;

	pop_size = psize;
	in_size = isize;
	out_sizw = osize;
	
	cout << pop_size << endl;

	for(int i=0; i<pop_size; i++){
		new_individual = new Individual();
		individuals.push_back(new_individual);
	}

}

Population::~Population(){
	
}