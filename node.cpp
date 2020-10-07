#include"node.h"


using namespace std;


Node::Node(){

	is_input = false;

}

Node::Node(bool isinput, bool isoutput){

	is_input = isinput;
	is_output = isoutput;


}

Node::~Node(){

	
}