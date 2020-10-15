#include"species.h"


using namespace std;


bool nodePtr_compare(Node *a, Node *b){return (*a<*b);};
bool consPtr_compare(Connection *a, Connection *b){return (*a<*b);};

Species::Species(Individual *founding_member, double c1, double c2, double c3, double max_d): c1(c1), c2(c2), c3(c3), max_d(max_d){

	members.push_back(founding_member);
	rep = founding_member;

}


bool Species::is_compatible(Individual *candidate){



	double delta = 0.;

	double N;

	vector<Node*> rep_nodes = rep->nodes;
	vector<Node*> cand_nodes = candidate->nodes;

	vector<Connection*> rep_cons = rep->connections;
	vector<Connection*> cand_cons = candidate->connections;

	N = max(rep_nodes.size()+rep_cons.size(), cand_nodes.size()+cand_nodes.size());

	sort(rep_nodes.begin(), rep_nodes.end(), nodePtr_compare);
	sort(cand_nodes.begin(), cand_nodes.end(), nodePtr_compare);

	sort(rep_cons.begin(), rep_cons.end(), consPtr_compare);
	sort(cand_cons.begin(), cand_cons.end(), consPtr_compare);

	int end_mark = max(rep_nodes[rep_nodes.size()-1]->hist_marking, max(cand_nodes[cand_nodes.size()-1]->hist_marking, max(rep_cons[rep_cons.size()-1]->hist_marking, cand_cons[cand_cons.size()-1]->hist_marking)));

	double E, D, W, nW;
	E=D=W=nW=0.;

	int rep_n_cursor, cand_n_cursor, rep_c_cursor, cand_c_cursor;
	rep_n_cursor=cand_n_cursor = rep->inputs.size()+rep->outputs.size(); // exclude input and output nodes, otherwise = 0;
	rep_c_cursor=cand_c_cursor = 0;

	int marking_cursor = rep_n_cursor; 
	
	do{

		if((rep_n_cursor==rep_nodes.size() || cand_n_cursor==cand_nodes.size()) && (rep_c_cursor==rep_cons.size() || cand_c_cursor==cand_cons.size())) break;
		else if(rep_n_cursor==rep_nodes.size() || cand_n_cursor==cand_nodes.size()) marking_cursor = min(rep_cons[rep_c_cursor]->hist_marking, cand_cons[cand_c_cursor]->hist_marking);
		else if(rep_c_cursor==rep_cons.size() || cand_c_cursor==cand_cons.size()) marking_cursor = min(rep_nodes[rep_n_cursor]->hist_marking, cand_nodes[cand_n_cursor]->hist_marking);
		else marking_cursor = min(rep_nodes[rep_n_cursor]->hist_marking, min(cand_nodes[cand_n_cursor]->hist_marking, min(rep_cons[rep_c_cursor]->hist_marking, cand_cons[cand_c_cursor]->hist_marking)));

		if(rep_nodes[rep_n_cursor]->hist_marking==marking_cursor || cand_nodes[cand_n_cursor]->hist_marking==marking_cursor){
			if(rep_nodes[rep_n_cursor]->hist_marking != cand_nodes[cand_n_cursor]->hist_marking){
				D += 1.;
				if(rep_nodes[rep_n_cursor]->hist_marking <= cand_nodes[cand_n_cursor]->hist_marking) rep_n_cursor++;
				else cand_n_cursor++;
			}
			else{
				rep_n_cursor++;
				cand_n_cursor++;
			}
			if(rep_n_cursor==rep_nodes.size()) E += cand_nodes.size()-(double)cand_n_cursor;
			else if(cand_n_cursor==cand_nodes.size()) E += rep_nodes.size()-(double)rep_n_cursor;

		}
		else{
			if(rep_cons[rep_c_cursor]->hist_marking != cand_cons[cand_c_cursor]->hist_marking){
				D++;
				if(rep_cons[rep_c_cursor]->hist_marking <= cand_cons[cand_c_cursor]->hist_marking) rep_c_cursor++;
				else cand_c_cursor++;
			}
			else{

				W += abs((rep_cons[rep_c_cursor]->weight - cand_cons[cand_c_cursor]->weight));
				nW += 1;


				rep_c_cursor++;
				cand_c_cursor++;

			}
			if(rep_c_cursor==rep_cons.size()) E += cand_cons.size()-(double)cand_c_cursor;
			else if(cand_c_cursor==cand_cons.size()) E += rep_cons.size()-(double)rep_c_cursor;

		}
	}while(marking_cursor<end_mark);

	W = W/nW;

	delta = c1*E/N + c2*D/N +c3*W;

	if(delta>max_d)return false;
	else return true;


}



bool Species::add_member(Individual *candidate){

	if (!is_compatible(candidate)) return false;



}



Species::~Species(){


}