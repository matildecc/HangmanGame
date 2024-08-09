#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Factory.h"

using namespace std;

Factory::Factory()
{
	this->key_filename = "";
}

c
void Factory::setKeyFilename(const string &key_filename)
{
	this->key_filename = key_filename;
}

//==============================================================//

bool Factory::openKeyFile()
{
	ifstream key_file;
	string line, txt = ".txt";
	bool file_opened = true;

	key_file.open(this->key_filename + txt);

	if (key_file.is_open())
	{
		while (getline(key_file, line))
		{
			if (line.length() > 0)
			{
				this->vector_keys.push_back(line);
			}
		}
	}
	else
	{
		cerr << "Key file not found!! " << endl;
		file_opened = false;
	}

	key_file.close();

	return file_opened;
}

//==============================================================//

string Factory::getKey()
{
	int random_n;

	random_n = rand() % this->vector_keys.size();
	this->key = this->vector_keys.at(random_n);

	return (this->key);
}

