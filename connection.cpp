#include"connection.h"

using namespace std;


Connection::Connection(){



}

Connection::Connection(Node *inode, Node *onode, int *innov_num){

	in_node = new Node;
	in_node = inode;

	out_node = new Node;
	out_node = onode;

	is_active = true;

	in_node->out_connections.push_back(this);
	out_node->in_connections.push_back(this);

	hist_marking = *innov_num;
	(*innov_num)++;

	weight = randdouble(-2., 2.);

}


Connection::~Connection(){


	
}