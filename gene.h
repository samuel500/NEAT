#ifndef DEF_GENE
#define DEF_GENE


#include<iostream>
#include<string>
#include <vector>


using namespace std;


class Genome{

public:	

	Gene();
	~Gene();

private:

	vector<Genes*> genes;
	
	
};


#endif
