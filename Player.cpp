#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstddef>
#include "Player.h"

using namespace std;

Player::Player()
{
	this->name = " ";
}

//=========================================================//

void Player::askPlayerName()
{
	cout << "Player name ? ";
}

//=========================================================//

void Player::readPlayerName()
{
	string name;
	getline(cin, name);
	this->name = name;
}

//=========================================================//

void Player::setScore(const int length_key, const int n_dif_letters, const double elapsed_time, const int n_max_trials, const int missed_trials)
{
	this->score = floor((1000 * (1 + n_dif_letters / length_key) / (elapsed_time * (1 + 0.1 * missed_trials / n_max_trials))) + 0.5);
}

//=========================================================//

void Player::askBet() const
{
	cout << "BET(LETTER) ? ";
}

//=========================================================//

void Player::readBet()
{
	char bet;
	int i;
	bool valid_char;
	bool repeated;

	do
	{
		repeated = false;
		i = 0;
		cin >> bet;

		if (cin.peek() != '\n')
		{
			char ch;
			valid_char = true;
			do
			{

				if (((cin.peek() != '\n') && (cin.peek() != ' ')))
				{
					valid_char = false;                                                 //new bet is the same as a previous one: it's repeated
					cerr << endl << "You can only try one letter! Please try again!\n";
				}
				cin.get(ch);


			} while (valid_char && (ch != '\n'));
		}
		else
		{
			valid_char = true;
			cin.ignore(1);
		}

		if (valid_char)                                                                 //only letters are accepted as bets
		{
			if (!isalpha(bet))
			{
				valid_char = false;
				cerr << endl << "Invalid bet! Please try again!\n";
			}
			else
			{
				valid_char = true;
				while (!repeated && (i < this->previous_bets.size()))
				{
					if (this->previous_bets.at(i) == toupper(bet) || this->previous_bets.at(i) == tolower(bet))
					{
						repeated = true;
						cout << endl << "You already bet that letter! Try again!\n";

					}
					i++;
				}
			}
		}
		else
			cin.ignore(numeric_limits<streamsize>::max(), '\n');


	} while (!valid_char || repeated);

	this->previous_bets.push_back(bet);
}

//=========================================================//

void Player::showPreviousBets() const
{
	cout << "\n\nPREVIOUS BETS : [ ";
	for (const auto& bet : this->previous_bets)
	{
		cout << bet << " ";
	}
	cout << " ]\n";
}

//=========================================================//

string Player::getName() const
{
	return this->name;
}

//=========================================================//

double Player::getScore() const
{
	return this->score;
}

//=========================================================//

size_t Player::getPreviousBetsSize() const
{
	return this->previous_bets.size();
}

//=========================================================//

char Player::getBet() const
{
	return this->previous_bets.at(this->previous_bets.size() - 1);
}
