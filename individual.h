#ifndef DEF_INDIVIDUAL
#define DEF_INDIVIDUAL


#include<iostream>
#include<string>
#include<vector>
#include"genome.h"

using namespace std;


class Individual{

public:	

	Individual(int *isize, int *osize);
	~Individual();

private:

	Genome *genome;
	int *in_size;
	int *out_size;
};


#endif
