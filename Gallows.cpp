#include <iostream>
#include <string>
#include <fstream>
#include "Gallows.h"

using namespace std;


Gallows::Gallows(const string &fileBaseName, const int n_bets)
{
	this->gallows_filename = fileBaseName + to_string(n_bets) + "_";
	this->missed_trials = 0;
}

//==============================================================//

void Gallows::drawGallows(bool &correct)
{
	if (!correct)                                                                                                              //finds out a missed trial
	{
		ifstream fig_hangman;
		string  fig, line, txt = ".txt";

		this->missed_trials++;
		fig = (this->gallows_filename)+ to_string(this->missed_trials) + txt;
		fig_hangman.open(fig);
        
        
		if (fig_hangman.is_open())
		{
			cout << endl << "-----------------" << endl;

			while (getline(fig_hangman, line))
				cout << line << endl;

			cout << endl << "-----------------" << endl;
		}
		else                                                                                                                   //error: no file found to draw figure
			cerr << "File not found!! " << endl;
	}
}

//==============================================================//

int Gallows::getMissedTrials() const
{
	return this->missed_trials;
}




