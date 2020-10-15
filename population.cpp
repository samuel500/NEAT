
#include"population.h"


using namespace std;


Population::Population(int pop_size, int in_size, int out_size): pop_size(pop_size), in_size(in_size), out_size(out_size){


	generation = 0;

	innov_num = new int;
	*innov_num = in_size+out_size;



	cout << "pop size " << pop_size << endl;

	cout << "innov_num " << *innov_num << endl;

	Individual *new_individual;

	bool activated;

	for(int i=0; i<pop_size; i++){

		activated = false;

		new_individual = new Individual(&in_size, &out_size, &generation, innov_num, &all_nodes, &all_connections);

		vector<double> inp = {1., 0.5}; 

		activated = new_individual->activate(inp);

		if(!activated) cout<<"error, individual failed to activate"<<endl;

		vector<double> out = new_individual->get_outputs();
		cout<<out[0]<<endl;

		individuals.push_back(new_individual);

	}


	cout << "fin innov_num " << *innov_num <<
	endl;

}


void Population::xor_epoch(){

	vector<vector<double>> xs {{0.,0.}, {0.,1.}, {1.,0.}, {1.,1.}};
	vector<double> ys {1., 0., 0., 1.};

	vector<Individual*>::iterator indPtr;


	for(indPtr=individuals.begin(); indPtr!=individuals.end(); indPtr++){
		double fitness=4.;
		for(int i=0; i<xs.size(); i++){
			(*indPtr)->activate(xs[i]);
			vector<double> out = (*indPtr)->get_outputs();
			fitness -= abs(out[0]-ys[i]);
		}
		fitness = pow(fitness, 2);
		(*indPtr)->fitness = fitness;
	}





}


void Population::speciate(){



}


Population::~Population(){
	vector<Individual*>::iterator curInd;

	for(curInd=individuals.begin(); curInd!=individuals.end(); ++curInd){
		delete *curInd;
	}
	delete innov_num;
}