#include"genome.h"


using namespace std;

Genome::Genome(){


}

Genome::Genome(int *isize, int *osize){

	in_size = new int;
	in_size = isize;
	out_size = new int;
	out_size = osize;

	Node *new_node;


	for(int i=0; i<(*in_size); i++){
		new_node = new Node(true, false);
		nodes.push_back(new_node);
	}
	for(int i=0; i<(*out_size); i++){
		new_node = new Node(false, true);
		nodes.push_back(new_node);
	}
	
}

Genome::~Genome(){

	
}