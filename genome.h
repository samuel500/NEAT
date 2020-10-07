#ifndef DEF_GENOME
#define DEF_GENOME


#include<iostream>
#include<string>
#include<vector>
#include"connection.h"
#include"node.h"

using namespace std;


class Genome{

public:	

	Genome();

	Genome(int *isize, int *osize);

	~Genome();

private:

	int *in_size;
	int *out_size;

	vector<Node*> nodes;
	vector<Connection*> connections;
	
	
};


#endif
