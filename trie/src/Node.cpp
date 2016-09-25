/* Node.cpp
 *
 * Kyle Tingey
 * u0627759
 */

#include "Node.h"
#include <vector>
#include <cstddef>

 extern int refCount;

/* node constructor */
Node::Node(){
	refCount++;
  	alpha = std::vector<Node*>(26, nullptr);
  	eow = false;
}

/* node destructor */
Node::Node(){
	refCount--;
}

/* signifies end of word */
bool Node::isend(){
  	return eow;
}

/* checks if word is complete */
bool Node::isend(bool _eow){
  	eow = _eow;
  	return eow;
}

/* get alphabet character */
std::vector<Node*> Node::galpha(){
	return alpha;
}

/* set alphabet character by index */
Node* Node::salpha(int i){
  	Node* child = new Node();
  	alpha[i] = child;
  	return child;
}
