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
#include"net.h"


using namespace std;


class Individual{


public:	

	Individual(int *isize, int *osize, int *innnum, vector );
	Individual(const Individual& indiv);
	~Individual();

	void mutate();
	bool mutate_add_connection();
	void mutate_add_node();
	void mutate_nudge_weight();
	void mutate_reset_weight();


private:

	Net *net;
	vector<Node*> nodes;
	vector<Node*> inputs;
	vector<Node*> outputs;
	
	vector<Connection*> connections;

	int *innov_num;
	int *in_size;
	int *out_size;

};


#endif
