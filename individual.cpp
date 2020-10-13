

#include"individual.h"


using namespace std;


Individual::Individual(int *isize, int *osize, int *gen, int *innnum, vector<Node*> *allnodes, vector<Connection*> *allconnections){

	in_size = new int;
	in_size = isize;
	out_size = new int;
	out_size = osize;
	
	generation = new int;
	generation = gen;

	innov_num = new int;
	innov_num = innnum;



	all_nodes = allnodes;
	all_connections = allconnections;


	Node *new_node;

	for(int i=0; i<*in_size; i++){
		new_node = new Node(INPUT, i);
		
		all_nodes->push_back(new_node);
		
		inputs.push_back(new_node);
		nodes.push_back(new_node);


	}

	for(int i=0; i<*out_size; i++){
		new_node = new Node(OUTPUT, *in_size+i);
		all_nodes->push_back(new_node);

		outputs.push_back(new_node);
		nodes.push_back(new_node);

	}



	mutate_add_connection();





}



//copy constructor
Individual::Individual(const Individual& indiv){


}


//meta mutation method
void Individual::mutate(){



}


bool Individual::mutate_add_connection(){

	Node *in_node;
	Node *out_node;


	int i = 0; // counter in case no new connection is possible
	bool duplicate = false;

	vector<Connection*>::iterator conPtr;

	do{

		int in_node_id = randint(0, nodes.size()-(*out_size)-1);

		in_node = nodes[in_node_id];

		int out_node_id;

		do{

			out_node_id = randint(*in_size, nodes.size()-1);
			i++;

		}while(in_node_id==out_node_id);

		out_node = nodes[out_node_id];

		duplicate = false;

		for(conPtr=out_node->in_connections.begin(); conPtr != out_node->in_connections.end(); ++conPtr){

			if((*conPtr)->in_node==in_node) duplicate = true;

		}


	}while(i<15 && duplicate==true);

	if(duplicate==true) return false;


	int new_innov_number;

	bool found = false;


	for(conPtr=all_connections->begin(); conPtr != all_connections->end(); ++conPtr){
		// give identical mutations same hist_marking
		// could also check for mutation hist gen? 
		// (https://www.cs.ucf.edu/~kstanley/neat.html#FAQ1  - see "record of innovation" Q
		if((*conPtr)->in_node->hist_marking==in_node->hist_marking && (*conPtr)->out_node->hist_marking==out_node->hist_marking){
			new_innov_number = (*conPtr)->hist_marking;
			found = true;
			break;
		}

	}

	if(!found){
		new_innov_number = *innov_num;
		(*innov_num)++;
	}

	Connection *new_connection = new Connection(in_node, out_node, new_innov_number);

	connections.push_back(new_connection);
	(*all_connections).push_back(new_connection);


	return true;

}


void Individual::mutate_nudge_weight(){


}


void Individual::mutate_reset_weight(){


}


void Individual::mutate_add_node(){


}


Individual::~Individual(){


	vector<Node*>::iterator curNode;
	vector<Connection*>::iterator curCon;

	for(curNode=nodes.begin(); curNode!=nodes.end(); ++curNode){
		delete *curNode;
	}

	for(curCon=connections.begin(); curCon!=connections.end(); ++curCon){
		delete *curCon;
	}

}
