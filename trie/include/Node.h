/*
 * Node.h
 *
 * Kyle Tingey
 * u0627759
 */

#include<vector>

class Node {

private:
	std::vector<Node*> alpha; // member variable
  	bool eow;  // end of word
  	
public:
  	Node(); // node constructor
  	bool isend(); // signifies complete word
  	bool isend(bool _isCompleteWord); //checks if word is complete
  	std::vector<Node*> galpha(); // get alphabet character
  	Node* salpha(int i); // set alphabet character by index
};
