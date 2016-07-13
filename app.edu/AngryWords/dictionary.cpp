#include "dictionary.h"
#include <iostream>

Dictionary::Dictionary()
{
    wordLength = 0;
}

void Dictionary::getDictionary(int option)
{
    //TODO: handle "no such file case"
    words.clear();

    //QFile file("../test.txt");
    QFile file("../dictionary.txt"); //external file versus resourse file
    file.open(QIODevice::ReadWrite);
    QTextStream in(&file);

    switch(option){
    case 1:
        wordLength = 5;
        break;
    case 2:
        wordLength = 10;
        break;
    case 3:
        wordLength = 15;
        break;
    case 0:
        wordLength = 0;
        break;
    }

    while(!in.atEnd())
    {
        QString word = in.readLine();
        if(wordLength != 0)
        {
            if( wordLength == 15 && word.size() >= 10 || word.size() <= wordLength && word.size() >= wordLength - 5 )
            {
                 words.push_back(new QString(word));
            }
        }
        else
        {
            if(word.size() <= 25)
                words.push_back(new QString(word));
        }
    }
}

QString* Dictionary::getWord()
{
    //TODO: this function should not be called if words.size() == 0
    if(words.size() > 0)
    {
        int maxIndex = words.size() -1;
        int random = rand() % maxIndex;
        QString* word = words[random];

        //remove the word after it has been chosen
        words.erase(words.begin()+random);

        return word;
    }
    else
    {
        return new QString("");
    }
}

void Dictionary::setWordLength(int length)
{
    wordLength = length;
}
