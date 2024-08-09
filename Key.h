
#ifndef KEY_H
#define KEY_H

#include <iostream>
#include <string>

using namespace std;

class Key
{
public:
    //Generates encrypted key according to the one given by Factory
	Key(const string& key);

    //Reads and adds new bet (inserted by player)
    bool addBetToUnknownWord(const char& bet);
    
    //Returns the sentence/key to guess
	void showUnknownKey() const;
    string getUnknownKey() const;
    
    //Returns the number of letters (without counting repeated letters)
    int getNumberDiffLetters() const;
    
    //Returns size of the sentence/key
	int getLengthKey() const;
    
private:
    //Key that the player must guess
	string key_to_guess;
    
    //Encrypted key (by an '*')
	string unknown_key;
    
    //Number of different letters at the same key
	int n_diff_letters;
    
    //Number of elements that the key has
	int length_key;
    
    //Checks if the new bet is the same as a previous one
	void featuresKey();

};

#endif
