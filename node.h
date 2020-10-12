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
	Node(nodetype ntype);
	~Node();


	nodetype node_type;

	vector<Connection*> in_connections;
	vector<Connection*> out_connections;


	
}; 

#endif
