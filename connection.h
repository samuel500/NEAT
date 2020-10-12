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
	Connection(Node *inode, Node *onode, int *innov_num);
	~Connection();

	Node *in_node;
	Node *out_node;

	double weight; //between -2 and 2

	bool is_active;

	int hist_marking;

private:


	
};


#endif
