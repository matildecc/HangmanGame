#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <ios>
#include <cctype>
#include <ctime>
#include "Hangman.h"
#include "Player.h"
#include "Scores.h"
#include "Key.h"
#include "Gallows.h"
#include "Factory.h"

using namespace std;

//==============================================================//

Hangman::Hangman(string configuration_filename)
{
	this->configuration_filename = configuration_filename;
}

//==============================================================//

bool Hangman::initializeGame()
{
	bool files_opened;
	
	files_opened = openConfigurationFile();
	if (files_opened)
	{
		this->factory.setKeyFilename(this->key_filename);
		files_opened = this->factory.openKeyFile();
	}

	return files_opened;
}

//==============================================================//

bool Hangman::runGame()
{
	Scores scores("bestplayers");
	Player player;
	string key_to_guess = this->factory.getKey();
	Key key(key_to_guess);
	Gallows gallows("fig", this->n_max_trials);
	bool win, bet_is_correct;
	time_t initial_time, final_time, elapsed_time;

	srand(time(NULL));

	displayMenu();
	showInitialMessage();
    
	scores.readBestScores();
	scores.showBestScores();

	player.askPlayerName();
	player.readPlayerName();

	do
	{
		player.showPreviousBets();
		key.showUnknownKey();
		player.askBet();
		player.readBet();

		if (player.getPreviousBetsSize() == 1)
			initial_time = time(NULL);                                                                          //initialization of time per round

		bet_is_correct = key.addBetToUnknownWord(player.getBet());
		gallows.drawGallows(bet_is_correct);

	} while (!endPlay(this->n_max_trials, gallows.getMissedTrials(), win, key_to_guess, key.getUnknownKey()));

	final_time = time(NULL);
	elapsed_time = final_time - initial_time;

	player.setScore(key.getLengthKey(), key.getNumberDiffLetters(), elapsed_time, this->n_max_trials, gallows.getMissedTrials());
	showFinalMessage(win, elapsed_time, player.getScore(), key_to_guess);
	scores.addBestPlayer(player);
	scores.saveBestScores();

	return (playAgain());
}

//==============================================================//

void Hangman::displayMenu() const
{
	int menuOption;
    
	cout << "PRESS:\n" << "1 - PLAY\n" << "2 - INSTRUCTIONS\n";                                                //reads player's decision
	cin >> menuOption;

	while (cin.fail() || (menuOption != 1 && menuOption != 2))                                                 //validation of player's decision
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please introduce a valid input: 1 - PLAY or 2 - INSTRUCTIONS \n";
		cin >> menuOption;
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
	if (menuOption == 2)                                                                                       //2 - INSTRUCTIONS of the HANGMAN : presentation of rules
	{
		cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << left << "\nThe purpose of this game is to invite the user to be a player : the player is supposed to guess the word/sentence behind every '*' ." << endl << "The player starts with a certain number of bets, which correspond to the same number of chances to hit the right key before the hangman is complete.\nIf the player reaches the number of chances announced, without unlocking the unknown word/sentence, the display of a terminal message appears : 'YOU HAVE LOST! WE ARE GOING TO CALL THE UNDERTAKERS :-(' . \nIf the player unlocks the unknown word/sentence before the HANGMAN is complete, the display of another terminal message appears : 'YOU ARE A WINNER. CONGRATULATIONS !'.It is also shown either the time that the player took to end the round and the score obtained.\nIn case the player scores as much points to be one one of the best players so far, both score and name of this player will be registered.\nInformation is refreshed every end the game.\n\n" << "Good Luck!\n\n";
		cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	}

}

//==============================================================//

bool Hangman::openConfigurationFile()
{
	ifstream configuration_file;                                                                                //configuration according to .txt file
	string line, txt = ".txt";
	int i = 1;
	bool file_opened = true;

	configuration_file.open(this->configuration_filename + txt);

	if (configuration_file.is_open())
	{
		while (getline(configuration_file, line))
		{
			if (i == 1)
				this->key_filename = line;
			else if (i == 3)
			{
				this->inital_message.push_back(line+"\n");
			}
			else if (line.length() > 0)
			{
				if (!isdigit(line.at(0)))
					this->inital_message.push_back(line);
				else
					this->n_max_trials = stoi(line);                                                            //number of max trials (at configuration)
			}

			i++;
		}
		configuration_file.close();
	}
	else
	{
		cerr << "Configuration file not found!! " << endl;
		file_opened = false;
	}

	return file_opened;
}

//==============================================================//

void Hangman::showInitialMessage() const
{
	for (const auto &line : this->inital_message)
	{
		cout << line << endl;
	}

	cout << "You have " << this->n_max_trials << " trials\n";
}

//==============================================================//

bool Hangman::endPlay(const int n_max_trials, const int missed_trials, bool& win, const string& key_to_guess, const string& unknown_key) const
{
	if (key_to_guess == unknown_key)                                                                               //if key is complete and is the same as the original
	{
		win = true;                                                                                                //player is a winner
		return true;
	}

	else if (missed_trials == n_max_trials)                                                                        //if missed trials reaches the limit
	{
		win = false;                                                                                               //player is a looser
		return true;
	}

	else return false;
}

//==============================================================//

void Hangman::showFinalMessage(const bool win, const time_t elapsed_time, const double score, const string& key_to_guess) const
{
	if (win)                                                                                                       //if player wins: displays score and time it lasted
	{
		cout << endl << endl << "KNOWN LETTERS : " << key_to_guess << endl;
		cout << "YOU ARE A WINNER. CONGRATULATIONS ! :-) \n";
		cout << "You took " << elapsed_time << " seconds and have obtained " << score << " points.\n";
	}
	else                                                                                                          //if player looses: displays the key supposed to find
	{
		cout << endl << endl << "The word/sentence was: " << key_to_guess << endl;
		cout << "YOU HAVE LOST ! WE ARE GOING TO CALL THE UNDERTAKERS :-(\n";
	}
}

//==============================================================//

bool Hangman::playAgain() const
{
	char y_or_n;

	cout << "\n\nDo you want to play again y/n ? ";                                                                  //asks player's decision
	cin >> y_or_n;                                                                                                   //reads player's decision

	while (cin.fail() || (tolower(y_or_n) != 'y' && tolower(y_or_n) != 'n'))                                         //validates player's decision
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please introduce a valid input: y/n \n";                                                            //asks for valid input
		cin >> y_or_n;
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	switch (y_or_n)
	{
	case 'y':                                                                                                        //new game starts
		return true;
	case 'n':
		return false;                                                                                                //end of the game
	}

}

//==============================================================//