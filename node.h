//CS 440 MP1
// @author William Koehler
// @netid wkoehle2

#ifndef NODE_H__
#define NODE_H__

using namespace std;

struct node {
	node* parent;
	pair<int, int> loc;
	int weight;
	float g, h, f;
	node() {
		parent = NULL;
		loc = make_pair(-1, -1);
		weight = -1;
		g = 0.0;
		h = 0.0;
		f = 0.0;
	}
	node(node* p, pair<int, int> l){
		parent = p;
		loc = l;
	}
	node(node* p, pair<int, int> l, int w){
		parent = p;
		loc = l;
		weight = w;
	}
	bool operator == (node * rhs) {
		return this->loc == rhs->loc;
	}
};

#endif
