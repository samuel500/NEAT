#include"connection.h"

using namespace std;


Connection::Connection(){



}

Connection::Connection(Node *inode, Node *onode, int hist_marking, int creation_gen): hist_marking(hist_marking), creation_gen(creation_gen){

	in_node = new Node;
	in_node = inode;

	out_node = new Node;
	out_node = onode;

	is_active = true;

	in_node->out_connections.push_back(this);
	out_node->in_connections.push_back(this);

	weight = randdouble(-1., 1.);

}

bool Connection::operator<(const Connection& connection){

	return (hist_marking<connection.hist_marking);

}

void Connection::reset_weight(){

	weight = randdouble(-1., 1.);

}

void Connection::perturb_weight(){

	weight += randdouble(-1., 1.);
}

Connection::~Connection(){

	delete in_node;
	delete out_node;
	
}