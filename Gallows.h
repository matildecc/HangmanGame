

#ifndef GALLOWS_H
#define GALLOWS_H

#include <iostream>
#include <string>


using namespace std;

class Gallows
{
public:
	Gallows(const string &fileBaseName, const int n_bets);
    
    //Opens the file to draw the gallow and displays a new gallow per new missed trial
	void drawGallows(bool& correct);
    
    //counts missed trials
	int getMissedTrials() const;
    
private:
    //.txt for gallows draw
	string gallows_filename;
    
    //Number of missed trials (number os incorrect bets)
	int missed_trials;
};

#endif
