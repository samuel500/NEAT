

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
		new_node = new Node(INPUT, i, *generation);
		
		all_nodes->push_back(new_node);
		
		inputs.push_back(new_node);
		nodes.push_back(new_node);


	}

	for(int i=0; i<*out_size; i++){
		new_node = new Node(OUTPUT, *in_size+i, *generation);
		all_nodes->push_back(new_node);

		outputs.push_back(new_node);
		nodes.push_back(new_node);

	}



	mutate_add_connection();
	mutate_add_connection();

	mutate_add_node();
	mutate_add_node();

	mutate_add_connection();




}



//copy constructor
Individual::Individual(const Individual& indiv){


}


bool Individual::activate(double *x){



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

			if((*conPtr)->in_node==in_node) duplicate = true; // proposed connection already exists

		}


	}while(i<15 && duplicate==true);

	if(duplicate==true) return false; // couldn't find any new possible connection


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

	Connection *new_connection = new Connection(in_node, out_node, new_innov_number, *generation);

	connections.push_back(new_connection);
	(*all_connections).push_back(new_connection);

	in_node->out_connections.push_back(new_connection);
	out_node->in_connections.push_back(new_connection);

	return true;

}


void Individual::mutate_nudge_weight(){


}


void Individual::mutate_reset_weight(){


}


bool Individual::mutate_add_node(){


	bool found_active = false;
	int rand_connection_id;
	for(int i=0; i<15; i++){
		rand_connection_id = randint(0, connections.size()-1);
		if(connections[rand_connection_id]->is_active){
			found_active = true;
			break;
		}
	}
	if(!found_active) return false;

	Connection *chosen_con = connections[rand_connection_id];
	Node *init_node = chosen_con->in_node;
	Node *end_node = chosen_con->out_node;

	chosen_con->is_active = false;


	bool found = false;
	int new_node_innov_number, new_in_connection_innov_number, new_out_connection_innov_number;


	vector<Node*>::iterator nodePtr;

	for(nodePtr=all_nodes->begin(); nodePtr != all_nodes->end(); ++nodePtr){
		// this will only find those nodes that haven't gotten any new connections since added
		// (Stanley's implementation only looks for nodes mutated in the current generation)
		if((*nodePtr)->in_connections.size()==1 && (*nodePtr)->out_connections.size()==1){

			if((*nodePtr)->in_connections[0]->in_node->hist_marking==init_node->hist_marking && (*nodePtr)->out_connections[0]->out_node->hist_marking==end_node->hist_marking){
				found = true;
				new_node_innov_number = (*nodePtr)->hist_marking;
				new_in_connection_innov_number = (*nodePtr)->in_connections[0]->hist_marking;
				new_out_connection_innov_number = (*nodePtr)->out_connections[0]->hist_marking;
			}

		}

	}

	if(!found){
		new_node_innov_number = *innov_num;
		(*innov_num)++;
		new_in_connection_innov_number = *innov_num;
		(*innov_num)++;
		new_out_connection_innov_number = *innov_num;
		(*innov_num)++;
	}


	Node *new_node = new Node(HIDDEN, new_node_innov_number, *generation);
	
	Connection *new_in_connection = new Connection(init_node, new_node, new_in_connection_innov_number, *generation);
	Connection *new_out_connection = new Connection(new_node, end_node, new_out_connection_innov_number, *generation);
	
	new_in_connection->weight = 1.0;
	new_out_connection->weight = chosen_con->weight;
	
	// new_node->in_connections.push_back(new_in_connection);
	// new_node->out_connections.push_back(new_out_connection);


	connections.push_back(new_in_connection);
	connections.push_back(new_out_connection);

	all_connections->push_back(new_in_connection);
	all_connections->push_back(new_out_connection);

	nodes.push_back(new_node);
	all_nodes->push_back(new_node);


	return true;
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
