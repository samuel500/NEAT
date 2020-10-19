#ifndef DEF_INDIVIDUAL
#define DEF_INDIVIDUAL


#include<iostream>
#include<string>
#include<vector>
#include<random>
#include <stdlib.h>

#include"node.h"
#include"connection.h"
#include"utils.h"


using namespace std;


class Individual{


public:	

	Individual(int *isize, int *osize, int *gen, int *innnum); //, vector<Node*> *allnodes, vector<Connection*> *allconnections);
	Individual(const Individual& indiv);
	~Individual();

	bool activate(vector<double> input);

	void mutate(vector<Node*> *all_nodes, vector<Connection*> *all_connections);
	bool mutate_add_connection(vector<Node*> *allnodes, vector<Connection*> *allconnections);
	bool mutate_add_node(vector<Node*> *allnodes, vector<Connection*> *allconnections);
	void mutate_weights();
	vector<double> get_outputs();
	void reset_activations();

	double fitness;
	double adjusted_fitness;
	double est_n_offspring;

	bool operator<(const Individual& individual);


	vector<Node*> nodes;
	vector<Node*> inputs;
	vector<Node*> outputs;

	vector<Connection*> connections;
	

	// vector<Node*> *all_nodes;
	// vector<Connection*> *all_connections;


	int *innov_num;
	int *in_size;
	int *out_size;
	int *generation;


};


#endif
