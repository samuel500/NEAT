#ifndef DEF_NODE
#define DEF_NODE


#include<iostream>
#include<string>
#include <vector>


using namespace std;


class Node{

public:	

	Node();
	Node(bool isinput, bool isoutput);
	~Node();



private:
	bool is_input;
	bool is_output;
	
}; 

#endif
