#include"individual.h"

using namespace std;

Individual::Individual(int *isize, int *osize){

	in_size = new int;
	in_size = isize;
	out_size = new int;
	out_size = osize;


	genome = new Genome(in_size, out_size);

}

Individual::~Individual(){
	delete genome;
}