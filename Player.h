#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <cstddef>

using namespace std;

class Player
{
public:
	Player();
	
    //Information about the player--------------------------------------------------------------------------------------------------------------------------------------
    
    //Asks for player's name
	void askPlayerName();
    
    //Reads player's name
	void readPlayerName();
    
    //Information about player's round----------------------------------------------------------------------------------------------------------------------------------
    
    //Calculates the score
	void setScore(const int length_key, const int n_dif_letters, const double elapsed_time, const int n_max_trials, const int missed_trials);
    
    //Asks for new bet
	void askBet() const;
    
    //Reads new bet and checks if it has already been given or if it is a letter
	void readBet();

    //Displays a vector of previous bets given by the player
	void showPreviousBets() const;
    
    //Returns the player's name
	string getName() const;
    
    //Returns the player's score
	double getScore() const;
    
    //Returns the size of the previous bets'vector given by the player
	size_t getPreviousBetsSize() const;
    
    //Returns the number of bets the player still has
    char getBet() const;

private:
    //Player's name
	string name;
    
    //Player's score
	int score;
    
    //Vector of previous bets given by the player
	vector<char> previous_bets;
};

#endif PLAYER_H
