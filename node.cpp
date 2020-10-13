#include"node.h"


using namespace std;


Node::Node(){


}

Node::Node(nodetype ntype, int hist_marking, int creation_gen): hist_marking(hist_marking), creation_gen(creation_gen){

	node_type = ntype;

}

Node::~Node(){

	
}