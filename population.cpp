
#include"population.h"


using namespace std;


Population::Population(int psize, int isize, int osize){


	pop_size = psize;
	in_size = isize;
	out_size = osize;

	generation = 0;

	innov_num = new int;
	*innov_num = in_size+out_size;



	cout << "pop size " << pop_size << endl;

	cout << "innov_num " << *innov_num << endl;

	Individual *new_individual;




	cout<<1<<endl;


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