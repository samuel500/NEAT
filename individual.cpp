#include"individual.h"

using namespace std;

Individual::Individual(int isize, int osize){

	in_size = isize;
	out_size = osize;
	genome = new Genome;
}

Individual::~Individual(){
	delete genome;
}