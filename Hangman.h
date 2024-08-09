#ifndef HANGMAN_H
#define HANGMAN_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Factory.h"

using namespace std;

class Hangman
{
public:
	Hangman(string configuration_filename);

	bool initializeGame();

	//Starts the game
	bool runGame();

private:
	string configuration_filename, key_filename;
	int n_max_trials;
	vector<string> inital_message;
	Factory factory;

	//Displays the menu with two options: play or instructions
	void displayMenu() const;

	//Opens and reads the configuration file
	bool openConfigurationFile();

	//Shows the initial message from the configuration file
	void showInitialMessage() const;

	//Compares the number of max trials and the already missed trials and checks if the player has already guessed the key
	bool endPlay(const int n_max_trials, const int missed_trials, bool& win, const string& key_to_guess, const string& unknown_key) const;

	//Displays message if the player have won or have lost the game
	void showFinalMessage(const bool win, const time_t elapsed_time, const double score, const string& key_to_guess) const;

	//Asks player to play again
    bool playAgain() const;
};

#endif HANGMAN_H
