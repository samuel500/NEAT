#include"node.h"


using namespace std;


double sigmoid(double x){
	double mult = 4.9;
	return (1/(1+(exp(-(x*mult))))); // this, or larger weight?


}

Node::Node(){


}

Node::Node(nodetype ntype, int hist_marking, int creation_gen): hist_marking(hist_marking), creation_gen(creation_gen){

	node_type = ntype;
	activated = false;
	double firing = 0.;

}


Node::Node(const Node& node){


}



bool Node::activate(){

	firing = 0.;

	vector<Connection*>::iterator conPtr;

	bool any_active_input_con = false;
	bool any_active_input_node = false;
	for(conPtr=in_connections.begin(); conPtr != in_connections.end(); ++conPtr){

		if((*conPtr)->is_active){
			any_active_input_con = true;
			if(((*conPtr)->in_node->activated)){
				any_active_input_node = true;
			// 	return false;
			}
		}
	}
	if(!any_active_input_con){
		// cout << "node not activated" <<endl;
		return false; 
	}

	for(conPtr=in_connections.begin(); conPtr != in_connections.end(); ++conPtr){

		firing += (*conPtr)->in_node->firing * (*conPtr)->weight;
	}
	
	if(any_active_input_node){
		firing = sigmoid(firing);
		activated = true;

	}


	return true;
}



void Node::reset(){

	activated = false;
	firing = 0.;
}



bool Node::operator<(const Node& node){

	return (hist_marking<node.hist_marking);

}




Node::~Node(){

	
}