
#include"population.h"


using namespace std;


bool spePtr_compare(Species *a, Species *b){return (*a<*b);};
bool indPtr_compare2(Individual *a, Individual *b){return (*a<*b);};



Population::Population(int popsize, int insize, int outsize): pop_size(popsize), in_size(insize), out_size(outsize){

	generation = 0;

	max_fitness = 0;

	innov_num = new int;
	*innov_num = in_size+out_size;


	cout << "pop size " << pop_size << endl;

	cout << "innov_num " << *innov_num << endl;

	Individual *new_individual;

	Individual *cp_ind;

	bool activated;

	for(int i=0; i<pop_size; ++i){

		activated = false;

		new_individual = new Individual(&in_size, &out_size, &generation, innov_num); //, &all_nodes, &all_connections);
		// cout << "p1" << endl;

		new_individual->mutate_add_connection(&all_nodes, &all_connections);
		new_individual->mutate_add_node(&all_nodes, &all_connections);


		vector<Connection*>::iterator conPtr;
		vector<Node*>::iterator nodePtr;
		// cout << "p2" << endl;

		for(conPtr=new_individual->connections.begin(); conPtr!=new_individual->connections.end(); ++conPtr){
			all_connections.push_back((*conPtr));
		}
		// cout << "p3" << endl;

		for(nodePtr=new_individual->nodes.begin(); nodePtr!=new_individual->nodes.end(); ++nodePtr){
			all_nodes.push_back((*nodePtr));
		}


		// testing

		vector<double> inp = {1., 0.5, 0.1}; 

		activated = new_individual->activate(inp);
		// cout << "p4" << endl;

		if(!activated) cout<<"error, individual failed to activate"<<endl;

		vector<double> out = new_individual->get_outputs();
		cout<<  "or"<<out[0]<<endl;

		new_individual->reset_activations();

		cp_ind = new Individual(*new_individual);

		activated = cp_ind->activate(inp);
		// cout << "p4" << endl;

		if(!activated) cout<<"error, individual failed to activate"<<endl;

		out = cp_ind->get_outputs();
		cout<<"cp"<<out[0]<<endl;


		individuals.push_back(new_individual);

	}


}


// void Population::clear_all_individuals(){

// 	for(indPtr=individuals.begin(), indPtr!=individuals.end(), ++indPtr){
// 		delete indPtr;
// 	}

// }


void Population::test_elite(){

	vector<vector<double>> xs {{1., 0.,0.}, {1., 0.,1.}, {1., 1.,0.}, {1., 1.,1.}};
	vector<double> ys {0., 1., 1., 0.};

	cout << "el n c " << elite->connections.size() << endl;
	cout << "el n n " << elite->nodes.size() << endl;


	double fitness=4.;
	for(int i=0; i<xs.size(); i++){
		// cout << "in " << xs[i][1] << " " << xs[i][2] << endl;
		elite->activate(xs[i]);
		vector<double> out = elite->get_outputs();
		// cout << "out " << out[0] << endl;

		fitness -= abs(out[0]-ys[i]);
	}
	fitness = pow(fitness, 2);
	cout << "fitness" << fitness << endl;

}


void Population::xor_epoch(){

	all_nodes.clear();
	all_connections.clear();

	vector<vector<double>> xs {{1., 0.,0.}, {1., 0.,1.}, {1., 1.,0.}, {1., 1.,1.}};
	vector<double> ys {0., 1., 1., 0.};

	vector<Individual*>::iterator indPtr;


	double pop_avg_fitness = 0.;

	for(indPtr=individuals.begin(); indPtr!=individuals.end(); ++indPtr){
		double fitness=4.;
		for(int i=0; i<xs.size(); i++){
			(*indPtr)->activate(xs[i]);
			vector<double> out = (*indPtr)->get_outputs();
			(*indPtr)->reset_activations();
			fitness -= abs(out[0]-ys[i]);
		}
		fitness = pow(fitness, 2);
		(*indPtr)->fitness = fitness;
	}
	// cout << "x1" << endl;

	vector<Species*>::iterator spePtr;

	sort(individuals.begin(), individuals.end(), indPtr_compare2);

	elite = individuals[individuals.size()-1];
	// cout << "x2" << endl;
	if(elite->fitness>max_fitness) max_fitness = elite->fitness;


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
	// cout << "x3" << endl;

	// give missing offspring (bc double->int) to best species
	species[species.size()-1]->n_offspring += (pop_size - temp_n_offspring);


	for(spePtr=species.begin(); spePtr!=species.end(); ++spePtr){
		if((*spePtr)->n_offspring==0) species.erase(spePtr);
	}


	vector<Individual*> new_individuals;
	vector<Individual*> descendants;

	for(spePtr=species.begin(); spePtr!=species.end(); ++spePtr){
	// cout << "x4" << endl;

		descendants = (*spePtr)->evolve(&all_nodes, &all_connections);
	// cout << "x5" << endl;

		new_individuals.insert(end(new_individuals), begin(descendants), end(descendants));
	}

	// for(indPtr=individuals.begin(); indPtr!=prev(individuals.end()); ++indPtr){
	// 	delete *indPtr;
	// }
	individuals.clear();
	individuals = new_individuals;


}



void Population::speciate(){

	vector<Individual*>::iterator curInd;
	vector<Species*>::iterator spePtr;

	bool accepted;

	for(curInd=individuals.begin(); curInd!=individuals.end(); ++curInd){
		// cout << "spe1" << endl;

		accepted = false;
		if(species.size()==0){
			Species *new_species = new Species(*curInd);
			// cout << "spe2" << endl;

			species.push_back(new_species);
		}
		else{
			// cout << "spe3" << endl;

			for(spePtr=species.begin(); spePtr!=species.end(); ++spePtr){
				// cout << "spe4" << endl;

				accepted = (*spePtr)->add_member(*curInd);
				// cout << "spe5" << endl;

				if(accepted) break;
			}
			if(!accepted){
				// cout << "spe6" << endl;

				Species *new_species = new Species(*curInd);
				species.push_back(new_species);
			}
		}
	}
}


Population::~Population(){
	// vector<Individual*>::iterator curInd;

	// for(curInd=individuals.begin(); curInd!=individuals.end(); ++curInd){
	// 	delete *curInd;
	// }
	// delete innov_num;
}