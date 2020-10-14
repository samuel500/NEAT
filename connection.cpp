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

	// hist_marking = histmarking;

	weight = randdouble(-1., 1.);

}


Connection::~Connection(){


	
}