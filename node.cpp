#include"node.h"


using namespace std;


double sigmoid(double x){

	return (1/(1+(exp(-(x*4.9))))); // this, or larger weight?


}

Node::Node(){


}

Node::Node(nodetype ntype, int hist_marking, int creation_gen): hist_marking(hist_marking), creation_gen(creation_gen){

	node_type = ntype;
	activated = false;
	double firing = 0.;

}

bool Node::activate(){


	vector<Connection*>::iterator conPtr;

	bool any_active_input_con = false;
	for(conPtr=in_connections.begin(); conPtr != in_connections.end(); ++conPtr){

		if((*conPtr)->is_active){
			any_active_input_con = true;
			if(!((*conPtr)->in_node->activated)) return false;
		}
	}
	if(!any_active_input_con) return false; 

	for(conPtr=in_connections.begin(); conPtr != in_connections.end(); ++conPtr){

		firing += (*conPtr)->in_node->firing * (*conPtr)->weight;
		firing = sigmoid(firing);
	}

	return true;
}

void Node::reset(){

	activated = false;
	firing = 0.;
}



Node::~Node(){

	
}