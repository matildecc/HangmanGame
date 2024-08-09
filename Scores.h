#ifndef SCORES_H
#define SCORES_H

#include <iostream>
#include <string>
#include <map>
#include "Player.h"

using namespace std;

class Scores
{
public:
	Scores();
	Scores(const string &filename);

    //Information about player's score-------------------------------------------------------------------------------------------------------------------------------------
	
    //Reads best player's list and generates a map with information by best player's name and score
    void readBestScores();
    
    //Adds new best player to best player's list
	void addBestPlayer(const Player &p);
	
    //Saves new best player's score according to his/her name
    void saveBestScores() const;
    
    //Displays best player's list by name and score
	void showBestScores() const;
    
private:
    //File containing best Player's list
	string filename;
    
    //Maps best player's list by name and score
	multimap<double, string> bestScores;
};

#endif SCORES_H
