#include <iostream>
#include <conio.h>

#include "Scene.h"
#include "Game.h"
#include "MainMenu.h"
#include "Defines.h"

using std::cout;
using std::endl;

CMainMenu::CMainMenu( CGame *gameArg )
{
	this->game = gameArg;
}


CMainMenu::~CMainMenu()
{
}

void CMainMenu::draw()
{
	// Print out menu
	cout << game->getGameName() << " v" << game->getMajorVersion() << "." << game->getMinorVersion() << endl;
	cout << endl;
	cout << "1.) New Game" << endl;
	cout << "2.) Load Game" << endl;
	cout << "3.) Exit" << endl;
	cout << endl;
	cout << "Enter an option: ";

	// Receive user input
	char input = _getch();

	if (input == KEY_1)
	{
		// Change state to new game
		this->game->setScene(SCENE_NEWGAME);
	}
	else if (input == KEY_2)
	{
		// Change state to load game
	}
	else if (input == KEY_3 || input == KEY_ESCAPE)
	{
		game->setExit();
	}

	return;
}