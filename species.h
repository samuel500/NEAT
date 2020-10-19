#ifndef DEF_SPECIES
#define DEF_SPECIES


#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include <algorithm> 

#include"individual.h"

using namespace std;


class Species{

public:	

	Species(Individual *founding_member, double c1=1., double c2=1., double c3=0.4, double max_d=3.0);
	~Species();

	bool is_compatible(Individual *candidate);
	bool add_member(Individual *candidate);

	// double get_tot_species_fitness();

	void adjust_fitness();
	double get_avg_fitness() const;
	int calc_n_offspring();


	vector<Individual*> evolve();

	bool operator<(const Species& spe);


	vector<Individual*> members;

	Individual *rep;

	double c1, c2, c3, max_d;

	int n_offspring;

	
};


#endif
