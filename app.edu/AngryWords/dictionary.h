#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <vector>
#include <QString>
#include <iterator>
#include <fstream>
#include <iostream>
#include <QFile>
#include <QTextStream>


class Dictionary
{
public:
    Dictionary();

    // vector of all words
    std::vector<QString*> words;

    //reads in a text file containing strings and adds all the strings to our vector
    void getDictionary(int option);

    //sets the length of words to be added to the dictionary
    //useful for customizing difficulty
    void setWordLength(int);

    //gets a random word from the dictionary
    QString* getWord();

private:
    //length of all the words we want added to dictionary (0 = set it to random)
    int wordLength;
};

#endif // DICTIONARY_H
