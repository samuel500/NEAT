#include"individual.h"


using namespace std;


Individual::Individual(int *isize, int *osize, int *gen, int *innnum){ //, vector<Node*> *allnodes, vector<Connection*> *allconnections){

	in_size = new int;
	in_size = isize;
	out_size = new int;
	out_size = osize;

	
	generation = new int;
	generation = gen;

	innov_num = new int;
	innov_num = innnum;


	fitness = 0.;

	// all_nodes = allnodes;
	// all_connections = allconnections;


	Node *new_node;

	for(int i=0; i<*in_size; i++){
		new_node = new Node(INPUT, i, *generation);
		
		// all_nodes->push_back(new_node);
		
		inputs.push_back(new_node);
		nodes.push_back(new_node);
	}

	for(int i=0; i<*out_size; i++){
		new_node = new Node(OUTPUT, *in_size+i, *generation);
		// all_nodes->push_back(new_node);

		outputs.push_back(new_node);
		nodes.push_back(new_node);

	}

	// mutate_add_connection();

	// mutate_add_connection();
	// mutate_add_node();

	// mutate_add_connection();
	// mutate_add_node();
	// mutate_add_connection();
	// mutate_add_node();



}


//copy constructor
Individual::Individual(const Individual& indiv){


	innov_num = new int;
	innov_num = indiv.innov_num;
	
	in_size = new int;
	in_size = indiv.in_size;
	out_size = new int;
	out_size = indiv.out_size;

		
	generation = new int;
	generation = indiv.generation;

	Node *new_node;


	vector<Node*>::const_iterator nodePtr;
	for(nodePtr=indiv.nodes.begin(); nodePtr != indiv.nodes.end(); ++nodePtr){

		new_node = new Node((*nodePtr)->node_type, (*nodePtr)->hist_marking, *generation);
		if((*nodePtr)->node_type == OUTPUT){
			outputs.push_back(new_node);
		}
		else if((*nodePtr)->node_type == INPUT){
			inputs.push_back(new_node);
		}
		nodes.push_back(new_node);

	}

	vector<Connection*>::const_iterator conPtr;
	for(conPtr=indiv.connections.begin(); conPtr != indiv.connections.end(); ++conPtr){

		int in_node_hist_marking = (*conPtr)->in_node->hist_marking;
		int out_node_hist_marking = (*conPtr)->out_node->hist_marking;

		Node *con_in_node = new Node;
		Node *con_out_node = new Node;

		bool found_in = false;
		bool found_out = false;

		for(nodePtr=nodes.begin(); nodePtr != nodes.end(); ++nodePtr){

			if((*nodePtr)->hist_marking == in_node_hist_marking){
				con_in_node = (*nodePtr);
				found_in = true;
			}
			else if((*nodePtr)->hist_marking == out_node_hist_marking){
				con_out_node = *nodePtr;
				found_out = true;
			}
			if(found_in && found_out) break;

		}

		Connection *new_connection = new Connection(con_in_node, con_out_node, (*conPtr)->hist_marking, *generation);
		new_connection->weight = (*conPtr)->weight;
		connections.push_back(new_connection);


	}

}


bool Individual::activate(vector<double> input){

	if(input.size() != inputs.size()){
		cout << "invalid input size" << endl;
		return false;
	}

	for(int i=0; i<inputs.size(); i++){
		inputs[i]->firing = input[i];
		inputs[i]->activated = true;
	}

	// messy, but it looks like it's the way to go 
	// (see FAQ: https://www.cs.ucf.edu/~kstanley/neat.html#FAQ1)
	int max_loops = 20; 
	int loops = 0;
	bool outputs_activated = false;
	while(!outputs_activated || loops<max_loops){
		outputs_activated = true;
		for(int i=*in_size; i<nodes.size(); i++){
			nodes[i]->activate();
			
			if(nodes[i]->node_type==OUTPUT && !nodes[i]->activated){
				outputs_activated = false;
			}
		}
		loops++;

	}

	if(!outputs_activated) {
		cout<<"activation pb" << endl;
		return false;
	}
	else return true;

}

vector<double> Individual::get_outputs(){
	
	vector<double> out;

	vector<Node*>::iterator nodePtr;
	for(nodePtr=outputs.begin(); nodePtr != outputs.end(); ++nodePtr){

		out.push_back((*nodePtr)->firing);

	}
	return out;


}


void Individual::reset_activations(){

	vector<Node*>::iterator nodePtr;
	for(nodePtr=nodes.begin(); nodePtr != nodes.end(); ++nodePtr){

		(*nodePtr)->reset();

	}

}


//meta mutation method
void Individual::mutate(vector<Node*> *all_nodes, vector<Connection*> *all_connections){

	if(randdouble(0.,1.)<0.8){
		// cout << "mu1" <<endl;
		mutate_weights();
	}
	if(randdouble(0.,1.)<0.03){
		// cout << "mu2" <<endl;

		mutate_add_node(all_nodes, all_connections);
	}
	if(randdouble(0.,1.)<0.05){
		// cout << "mu3" <<endl;

		mutate_add_connection(all_nodes, all_connections);
	}

}


bool Individual::mutate_add_connection(vector<Node*> *all_nodes, vector<Connection*> *all_connections){

	Node *in_node;
	Node *out_node;


	int i = 0; // counter in case no new connection is possible
	bool duplicate = false;

	vector<Connection*>::iterator conPtr;


	do{

		int in_node_id = randint(0, nodes.size()-(*out_size)-1);
		// cout << "ma1" << endl;

		in_node = nodes[in_node_id];
		// cout << "ma2" << endl;

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
			// cout << "ma3" << endl;

		for(conPtr=out_node->out_connections.begin(); conPtr != out_node->out_connections.end(); ++conPtr){

			if((*conPtr)->out_node==in_node) duplicate = true; // proposed opposite connection already exists, prevents simple loops

		}


	}while(i<20 && duplicate==true);

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
	// (*all_connections).push_back(new_connection);
	// cout << "ma3" << endl;

	in_node->out_connections.push_back(new_connection);
	out_node->in_connections.push_back(new_connection);

	return true;

}


void Individual::mutate_weights(){
	vector<Connection*>::iterator conPtr;

	for(conPtr=connections.begin(); conPtr != connections.end(); ++conPtr){

		// uniform perturbation
		if(randdouble(0.,1.)>0.1){
			(*conPtr)->perturb_weight();
		}
		// assign new random value
		else{
			(*conPtr)->reset_weight();
		}
	}
}


bool Individual::mutate_add_node(vector<Node*> *all_nodes, vector<Connection*> *all_connections){

	bool found_active = false;
	int rand_connection_id;
	for(int i=0; i<15; i++){
		rand_connection_id = randint(0, connections.size()-1);
		if(connections[rand_connection_id]->is_active){
			found_active = true;
			break;
		}
	}
	if(!found_active){ 
		cout << "no active connection found"<< endl;
		return false;


	}

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


	connections.push_back(new_in_connection);
	connections.push_back(new_out_connection);

	// all_connections->push_back(new_in_connection);
	// all_connections->push_back(new_out_connection);

	nodes.insert(nodes.begin()+(nodes.size()-(*out_size)), new_node); // add before the output nodes
	// all_nodes->push_back(new_node);

	return true;
}


Individual::~Individual(){

	// vector<Node*>::iterator curNode;
	// vector<Connection*>::iterator curCon;

	// for(curNode=nodes.begin(); curNode!=nodes.end(); ++curNode){
	// 	delete *curNode;
	// }

	// for(curCon=connections.begin(); curCon!=connections.end(); ++curCon){
	// 	delete *curCon;
	// }

}


bool Individual::operator<(const Individual& individual){

	return (fitness<individual.fitness);
}
