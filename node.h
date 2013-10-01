#ifndef NODE_H__
#define NODE_H__

typedef struct node {
	node* parent;
	pair<int, int> loc;
	float g;
	float h;
	float f;
	node() {
		parent = NULL;
		loc = make_pair(-1, -1);
	}
	node(node* p, pair<int, int> l){
		parent = p;
		loc = l;
		g=0;
		h=0;
		f=g+h;
	}
	
    bool operator ==(const node &a) 
    {
        return (a.loc == loc);
    }
  

} node;

#endif
