
#include"population.h"


using namespace std;

bool spePtr_compare(Species *a, Species *b){return (*a<*b);};


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

		new_individual->reset();

		individuals.push_back(new_individual);

	}

	speciate();
	cout << "spe size " << species.size() << endl;

	cout << "fin innov_num " << *innov_num <<
	endl;

}


void Population::xor_epoch(){

	vector<vector<double>> xs {{0.,0.}, {0.,1.}, {1.,0.}, {1.,1.}};
	vector<double> ys {1., 0., 0., 1.};

	vector<Individual*>::iterator indPtr;

	double pop_avg_fitness = 0.;

	for(indPtr=individuals.begin(); indPtr!=individuals.end(); ++indPtr){
		double fitness=4.;
		for(int i=0; i<xs.size(); i++){
			(*indPtr)->activate(xs[i]);
			vector<double> out = (*indPtr)->get_outputs();
			fitness -= abs(out[0]-ys[i]);
		}
		fitness = pow(fitness, 2);
		(*indPtr)->fitness = fitness;
	}

	vector<Species*>::iterator spePtr;


	for(spePtr=species.begin(); spePtr!=species.end(); ++spePtr){
		(*spePtr)->adjust_fitness();

	}

	sort(species.begin(), species.end(), spePtr_compare);

	for(indPtr=individuals.begin(); indPtr!=individuals.end(); ++indPtr){
		pop_avg_fitness += (*indPtr)->adjusted_fitness;
	}

	pop_avg_fitness /= individuals.size();

	
	for(indPtr=individuals.begin(); indPtr!=individuals.end(); ++indPtr){
		(*indPtr)->est_n_offspring = (*indPtr)->adjusted_fitness / pop_avg_fitness;
	}

	int temp_n_offspring = 0;
	for(spePtr=species.begin(); spePtr!=species.end(); ++spePtr){
		temp_n_offspring += (*spePtr)->calc_n_offspring();
	}

	// give missing offspring (bc double->int) to best species
	species[species.size()-1]->n_offspring += (pop_size - temp_n_offspring);

	for(spePtr=species.begin(); spePtr!=species.end(); ++spePtr){
		(*spePtr)->evolve();
	}

}


void Population::speciate(){

	vector<Individual*>::iterator curInd;
	vector<Species*>::iterator spePtr;

	bool accepted;

	for(curInd=individuals.begin(); curInd!=individuals.end(); ++curInd){
		accepted = false;
		if(species.size()==0){
			Species *new_species = new Species(*curInd);

			species.push_back(new_species);
		}
		else{
			for(spePtr=species.begin(); spePtr!=species.end(); ++spePtr){

				accepted = (*spePtr)->add_member(*curInd);

				if(accepted) break;
			}
			if(!accepted){
				Species *new_species = new Species(*curInd);
				species.push_back(new_species);
			}

		}
	}

}


Population::~Population(){
	vector<Individual*>::iterator curInd;

	for(curInd=individuals.begin(); curInd!=individuals.end(); ++curInd){
		delete *curInd;
	}
	delete innov_num;
}