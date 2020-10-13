#ifndef DEF_NODE
#define DEF_NODE


#include<iostream>
#include<string>
#include<vector>

#include"connection.h"

using namespace std;


enum nodetype {
	INPUT,
	OUTPUT,
	HIDDEN
};

class Connection;

class Node{

public:	

	Node();
	Node(nodetype ntype, int hist_marking, int creation_gen);
	~Node();


	bool activate();

	nodetype node_type;

	int hist_marking;
	int creation_gen;

	bool activated;
	double firing;


	vector<Connection*> in_connections;
	vector<Connection*> out_connections;


	
}; 

#endif
