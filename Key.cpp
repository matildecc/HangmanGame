#include <iostream>
#include <string>
#include <vector> 
#include "Key.h"

using namespace std;

Key::Key(const string &key)
{
	this->key_to_guess = key;
    
	for (int i = 0; i < (this->key_to_guess).length(); i++)                                                            
	{
		if (isalpha((this->key_to_guess).at(i)))
			(this->unknown_key).push_back('*');
		else
			(this->unknown_key).push_back(key_to_guess.at(i));
	}
	featuresKey();
}

//==============================================================//

bool  Key::addBetToUnknownWord(const char& bet)
{
	bool correct = false;

	for (int c = 0; c < (this->key_to_guess).length(); c++)
	{
		if ((this->key_to_guess).at(c) == toupper(bet) || ((this->key_to_guess).at(c) == tolower(bet)))
		{
			correct = true;
			(this->unknown_key).at(c) = (this->key_to_guess).at(c);
		}
	}

	return correct;

}

//==============================================================//

void Key::featuresKey()
{
	vector <char> already_seen;
	bool seen = false;

	for (size_t i = 0; i < key_to_guess.length(); i++)
	{
		if (isalpha((this->key_to_guess).at(i)))
		{
			for (size_t j = 0; ((j < already_seen.size()) && (seen == false)); j++)
			{
				if ((this->key_to_guess).at(i) == already_seen.at(j))
					seen = true;
			}

			if (!seen)
			{
				(this->n_diff_letters)++;
				already_seen.push_back(key_to_guess.at(i));
			}

			(this->length_key)++;
		}
	}

}

//==============================================================//

void Key::showUnknownKey() const
{
	cout << "KNOWN LETTERS :" << this->unknown_key << endl;
}

//==============================================================//

string Key::getUnknownKey()  const
{
	return (this->unknown_key);
}

//==============================================================//

int Key::getNumberDiffLetters() const
{
	return (this->n_diff_letters);
}

//==============================================================//

int Key::getLengthKey() const
{
	return (this->length_key);
}

