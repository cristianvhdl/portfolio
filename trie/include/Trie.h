/*
 * Trie.h
 *
 * Kyle Tingey
 * u0627759
 */
#include "Node.h"
#include <string>
#include <vector>


class Trie {
 public:
  Trie();   // constructor
  ~Trie();  // destructor
  Trie(const Trie& node2); // copy constructor

  /* overload methods */
  Trie& operator=(Trie node2);
  
  /* insert, validate, search */
  void addWord(std::string word);
  bool isWord(std::string word);
  std::vector<std::string> allWordsWithPrefix(std::string word);

 private:
  Node* root; // private data member
  /* helper methods */
  void chelper(Node* node1, Node* node2);
  void dhelper(Node* node);  
  void awwhelper(std::string word, Node* cur, std::vector<std::string>* wl);
};
