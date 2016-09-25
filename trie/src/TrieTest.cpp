/*
 * Author Joshua Callahan
 * u0691598
 * CS 3505
 * A2
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fstream>
#include <istream>
#include "Trie.h"

using namespace std;

// This tester program will use Spiral and HaruPDF to draw a spiral of text onto a PDF from input
int main (int argc, char **argv)
{
	if (argc != 3) {
		cout << "Error. System Abort" << endl;
		return 1;
	}

	string wordsFileName = argv[1];
	string queriesFileName = argv[2];

	ifstream wordsFile;
	wordsFile.open(wordsFileName);
	ifstream queriesFile;
	queriesFile.open(queriesFileName);

	Trie *wordsTrie = new Trie();
	
	string line;
	while (getline(wordsFile, line)) {
		wordsTrie->addWord(line);
	}
	
	while (getline(queriesFile, line)) {
		if (wordsTrie->isWord(line)) {
			cout << line << " is found\n";
		}
		else {
			vector<string> suggestions = wordsTrie->allWordsWithPrefix(line);
			cout << line << " is not found, did you mean:\n";
			if (suggestions.empty()) { 
				cout << "   no alternatives found\n";
			}
			else {
				for (vector<string>::iterator it = suggestions.begin(); it != suggestions.end(); it++)
				{
				cout << "   " << *it << endl;
				}
			}
		}
	}

    return 0;
}



