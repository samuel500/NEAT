#include"node.h"


using namespace std;


Node::Node(){


}

Node::Node(nodetype ntype, int hist_marking):hist_marking(hist_marking){

	node_type = ntype;

}

Node::~Node(){

	
}