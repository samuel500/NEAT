
#include"population.h"


using namespace std;


Population::Population(int psize, int isize, int osize){

	Individual *new_individual;

	pop_size = psize;
	in_size = isize;
	out_size = osize;

	gen = 0;
	innov_num = new int;
	*innov_num = 0;



	cout << "pop size " << pop_size << endl;

	cout << "innov_num " << *innov_num << endl;

	for(int i=0; i<pop_size; i++){
		new_individual = new Individual(in_size, out_size);
		individuals.push_back(new_individual);
	}

}

Population::~Population(){
	vector<Individual*>::iterator curInd;

	for(curInd=individuals.begin(); curInd!=individuals.end(); ++curInd){
		delete *curInd;
	}
	delete innov_num;
}