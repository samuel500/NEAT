
#include"population.h"


using namespace std;


Population::Population(int pop_size, int in_size, int out_size): pop_size(pop_size), in_size(in_size), out_size(out_size){


	generation = 0;

	innov_num = new int;
	*innov_num = in_size+out_size;



	cout << "pop size " << pop_size << endl;

	cout << "innov_num " << *innov_num << endl;

	Individual *new_individual;


	for(int i=0; i<pop_size; i++){


		new_individual = new Individual(&in_size, &out_size, &generation, innov_num, &all_nodes, &all_connections);

		individuals.push_back(new_individual);

	}

	cout << "fin innov_num " << *innov_num << endl;

}

Population::~Population(){
	vector<Individual*>::iterator curInd;

	for(curInd=individuals.begin(); curInd!=individuals.end(); ++curInd){
		delete *curInd;
	}
	delete innov_num;
}