#ifndef FACTORY_H
#define FACTORY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Factory
{
public:
	Factory();

    //Sets file to extract keys(sentences/words)
    void setKeyFilename(const string &key_filename);
    
    //Opens and reads the file where keys(sentences/words) are written
	bool openKeyFile();
    
    //Randomizes a number until the lenght of the vector of keys and generates the key correspondent to that number (each key correspond to one position at this vector)
    string getKey();

private:
    string key_filename;
    string key;
    
    //Vector that contains all keys (sentences/words): each index correspond to a different key
	vector<string> vector_keys;
};

#endif FACTORY_H
