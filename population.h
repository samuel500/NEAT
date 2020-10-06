#ifndef DEF_POPULATION
#define DEF_POPULATION


#include<iostream>
#include<string>
#include <vector>
#include"individual.h"


using namespace std;


class Population{

public:	

	Population(int psize, int isize, int osize);
	~Population();

private:

	vector<Individual*> individuals;
	int pop_size;
	int in_size;
	int out_size;


	
};


#endif
