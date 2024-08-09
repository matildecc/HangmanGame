#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <map>
#include "Scores.h"
#include "Player.h"

using namespace std;

Scores::Scores()
{
	string filename = "bestplayers";
	this->filename = filename;
}

//==============================================================//

Scores::Scores(const string& filename)
{
	this->filename = filename;
}

//==============================================================//

void Scores::readBestScores()
{
	ifstream file;
	string txt = ".txt", name;
	multimap<double, string> bestScores;
	double score;

	file.open(this->filename + txt);

	while (file >> score && getline(file, name))
	{
		istringstream input_str;
		input_str.str(name);

		string clean_name, white_space = " ";

		while (input_str >> name)
		{
			clean_name += name + white_space;
		}

		bestScores.insert(pair<double, string>(score, clean_name));
	}

	if (file.fail())
		file.clear();
	file.close();

	this->bestScores = bestScores;
}

//==============================================================//

void Scores::addBestPlayer(const Player& p)
{
	this->bestScores.insert(pair<double, string>(p.getScore(), p.getName()));

	if (this->bestScores.size() > 10)
	{
		this->bestScores.erase(this->bestScores.begin());
	}
}

//==============================================================//

void Scores::saveBestScores() const
{
	ofstream file;
	string txt = ".txt", name;

	file.open(this->filename + txt);

	for (multimap<double, string>::const_reverse_iterator it = this->bestScores.rbegin(); it != this->bestScores.rend(); it++)
	{
		file << left << setw(10) << it->first << left << setw(20) << it->second << endl;
	}
	file.close();
}

//==============================================================//

void Scores::showBestScores() const
{
	if (this->bestScores.size() > 0)
	{
		cout << endl << "Best players until now:\n";

		for (multimap<double, string>::const_reverse_iterator it = this->bestScores.rbegin(); it != this->bestScores.rend(); it++)
		{
			cout << left << setw(10) << it->first << " - " << left << setw(20) << it->second << endl;
		}
		cout << endl;
	}
}
