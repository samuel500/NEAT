#ifndef DEF_GENOME
#define DEF_GENOME


#include<iostream>
#include<string>
#include <vector>


using namespace std;


class Genome{

public:	

	Genome();
	~Genome();

private:

	vector<Nodes*> nodes;
	vector<Connection*> connections;
	
	
};


#endif
