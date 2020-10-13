#include"node.h"


using namespace std;


Node::Node(){


}

Node::Node(nodetype ntype, int hist_marking, int creation_gen): hist_marking(hist_marking), creation_gen(creation_gen){

	node_type = ntype;
	activated = false;
	double firing = 0.;

}

bool Node::activate(){


	vector<Connection*>::iterator conPtr;

	for(conPtr=in_connections.begin(); conPtr != in_connections.end(); ++conPtr){

		if(!((*conPtr)->in_node->activated)) return false;

	}

}

Node::~Node(){

	
}