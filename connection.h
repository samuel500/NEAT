#ifndef DEF_CONNECTION
#define DEF_CONNECTION


#include<iostream>
#include<string>
#include<vector>

#include"node.h"
#include"utils.h"

using namespace std;


class Node;

class Connection{

public:	

	Connection();
	Connection(Node *inode, Node *onode, int hist_marking, int creation_gen);
	~Connection();

	bool operator<(const Connection& connection);

	void reset_weight();
	void perturb_weight();

	Node *in_node;
	Node *out_node;

	double weight; //between -2 and 2

	bool is_active;

	int hist_marking;
	int creation_gen;


private:


	
};


#endif
