#ifndef DEF_POPULATION
#define DEF_POPULATION


#include<iostream>
#include<string>
#include<vector>
#include"individual.h"


using namespace std;


class Population{

public:	

	Population(int pop_size, int in_size, int out_size);
	~Population();

private:

	vector<Individual*> individuals;
	vector<Node*> all_nodes;
	vector<Connection*> all_connections;
	int pop_size;
	int in_size;
	int out_size;
	int generation;
	int *innov_num;


	
};


#endif
