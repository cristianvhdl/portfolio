/*
 * Trie.cpp
 *
 * Kyle Tingey
 * u0627759
 */

#include "Trie.h"
#include <string>
#include <vector>
#include <stddef.h>
#include <iostream>

/* constructor */
Trie::Trie(){
    root = new Node();
}


/* copy constructor */
Trie::Trie(const Trie& node){
    root = new Node;
    this->chelper(node.root, this->root);
}

/* destructor */
Trie::~Trie(){
    this->dhelper(root);
}


/* overloading operator '=' */
Trie& Trie::operator=(Trie node){
    if(this != &node)
        std::swap(root,node.root);
    return *this;
}


/*
 * A method addWord that accepts a std::string and returns void. The word passed 
 * into the method should be added to the Trie. Duplicate adds should not change the
 * Trie. You may assume that the word is only made up of lower-case characters from 
 * a-z.
 */
void Trie::addWord(std::string word){
    if(word.length() == 0)
        return;
    
    Node* cur = root;
    for(int i = 0; i < word.length(); i++){
        int ni = word[i] - 97;
        if(cur->galpha()[ni])
            cur = cur->galpha()[ni];
        else
            cur = cur->salpha(ni); // create child node
    }
    cur->isend(true);
}

/*
 * isWord accepts a std::string and returns bool. The argument is a word made up 
 * of characters 'a'-'z'. If the word is found in the Trie, the method should return 
 * true, otherwise return false
 */
bool Trie::isWord(std::string word){
    if(word.length() == 0)
        return false;
    Node* cur = root;
    for(int i = 0; i < word.length(); i++){
        int ni = word[i] - 97;
        if(cur->galpha()[ni])
            cur = cur->galpha()[ni];
        else
            return false;
    }
    return cur->isend();
}


/*
 * A method allWordsWithPrefix that accepts a std::string and returns a 
 * vector<std::string> that contains all the words in the Trie that start with the 
 * passed in argument prefix string. A word that is just the prefix is acceptable. 
 * An empty prefix should return all words in the Trie.
 */
std::vector<std::string> Trie::allWordsWithPrefix(std::string word){
    std::vector<std::string> wl;
    Node* cur = root;
    for(int i = 0; i < word.length(); i++){
        int ni = word[i] - 97; // node index
        if(cur->galpha()[ni])
            cur = cur->galpha()[ni];
        else
            return std::vector<std::string>();
    }
    this->awwhelper(word, cur, &wl); 
    return wl;
}

/********** HELPER METHODS **********/

/* all words with prefix recursive helper method */
void Trie::awwhelper(std::string word, Node* cur, std::vector<std::string>* wl){
    for(int i=0; i<26; i++){
        if(cur->galpha()[i]){
            word.push_back((char)(i + 97)); 
            if(cur->galpha()[i]->isend())
                wl->push_back(word);
            this->awwhelper(word, cur->galpha()[i], wl);
            word.pop_back(); 
        }
    }
}

/* destructor recursive helper method */
void Trie::dhelper(Node* node){
    for(int i=0; i<26; i++)
        if(node->galpha()[i]){
            this->dhelper(node->galpha()[i]);
    }
    delete node;
}

/* constructor recursive helper method */
void Trie::chelper(Node* node1, Node* node2){
    for(int i=0; i<26; i++){
        if(node1->galpha()[i]){
            node2->isend(node1->isend());
            node2->salpha(i);
            this->chelper(node1->galpha()[i], node2->galpha()[i]);
        }
        else
            node2->isend(node1->isend()); 
    } 
}