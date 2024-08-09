//=========================================================//
// Project_EDA_HANGMAN.cpp
// GROUP 04 (G04)
// MEMBERS: Daniel Corona Oliveira Costa    up201900131
//          Mariana Alves Fernandes         up201709475
//          Matilde Carvalho Costa          up201806495

#include <iostream>
#include <iomanip>
#include "Hangman.h"

using namespace std;

int main()
{
	Hangman hangman_game("Configuration");

    cout << "THE HANGMAN GAME" << endl << endl;
	if (hangman_game.initializeGame())
	{
		while (hangman_game.runGame());
	}
	
	return 0;
}

//=========================================================//